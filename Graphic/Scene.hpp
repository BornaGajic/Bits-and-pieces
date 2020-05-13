#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <algorithm>
#include <limits>
#include <math.h>

#include "Shapes.hpp"

using namespace std;

typedef vector<Object*> Objects;
typedef vector<Light> Lights;
typedef vector<Vec_3_f> Image;

float clip(float n, float lower, float upper) 
{
  return std::max(lower, std::min(n, upper));
}

// reflected ray
Vec_3_f reflect (const Vec_3_f& d, const Vec_3_f n)
{
    return d - (n * (2 * (d * n)));
}

Vec_3_f refract (const Vec_3_f& d, const Vec_3_f& n, const float& ior)
{
    
    float cosd = clip(1.f, -1.f, d * n);
    float Ni = 1, Nt = ior; 

    Vec_3_f N = n; 
    if (cosd < 0)
    { 
        cosd = -cosd;
    } 
    else
    { 
        N = -n;
        swap(Ni, Nt);
    } 
    float eta = Ni / Nt; 
    float k = 1 - eta * eta * (1 - cosd * cosd); 

    if (k < 0)
        return Vec_3_f{};
    else
        return (d * eta) + (N * (eta * cosd - sqrtf(k)));
}

void fresnel(const Vec_3_f &I, const Vec_3_f &N, const float &ior, float &kr) 
{ 
    float cosi = clip(-1.f, 1.f, I * N); 
    float etai = 1, etat = ior; 
    
    if (cosi > 0) { swap(etai, etat); } 
    
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi)); 
    
    if (sint >= 1) kr = 1;
    else 
    { 
        float cost = sqrtf(std::max(0.f, 1 - sint * sint)); 
        cosi = fabsf(cosi); 
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
        kr = (Rs * Rs + Rp * Rp) / 2; 
    }
} 

// shoots a ray in a pixel and decides whether it hit an object or a background (no object is hit)
// if an object was hit, take the (x,y,z) coordinatese of the most forward one; and calculate a normal in that dot.
// if dist is < 1000, no object got hit.
bool scene_intersect (const Vec_3_f &orig, const Vec_3_f &dir, const Objects &objs, Vec_3_f &hit, Vec_3_f &N, Material &material)
{
    float dist = numeric_limits<float>::max();
    float obj_dist = dist;

    for (auto obj : objs)
    {
        if (obj->ray_intersect(orig, dir, obj_dist) && obj_dist < dist)
        {
            dist = obj_dist;
            hit = orig + dir * obj_dist;                                                        //  point of intersection with a ray
            N = obj->normal(hit);
            material = obj->material;
        }
    }

    return dist < 1000;
}

// Paint the pixel in Material color of the object, and apply lighting
// orig is rays point of origin and its direction dir
// Shadow:
// Draw shadow if there's another object between current point and light origin.
// Find point of intersection between a ray (in the direction of light) and some object.
// if there's none paint the pixel in material color.
Vec_3_f cast_ray (const Vec_3_f &orig, const Vec_3_f &dir, const Objects &objs, Lights &lights, const uint32_t depth = 0)
{
    Vec_3_f point, N;
    Material material;
    
    if (depth > 10)
        return Vec_3_f{0.2, 0.7, 0.8};
    else if (!scene_intersect(orig, dir, objs, point, N, material))                              // point, N and material are mutators
        return Vec_3_f{0.2, 0.7, 0.8};                                                          // no object got hit, paint the pixel with background color
        
    float diffuse_light_intensity = 0;
    bool return_with_shadow = false;
    Vec_3_f reflective_color {};
    Vec_3_f refractive_color {};
    Vec_3_f reflective_refractive_color {};

    if (material.is_reflective && material.is_refractive)
    {   
        float kr;
        fresnel(dir, N, material.get_ior(), kr);
        
        bool outside = (dir * N) < 0;
        Vec_3_f bias = N; 
        
        if (kr < 1) 
        { 
            Vec_3_f refractionDirection = refract(dir, N, material.get_ior()).normalize(); 
            
            Vec_3_f refractionRayOrig = outside ? point - bias : point + bias;

            refractive_color = cast_ray(refractionRayOrig, refractionDirection, objs, lights, depth + 1); 
        } 
 
        Vec_3_f reflectionDirection = reflect(dir, N).normalize(); 
        Vec_3_f reflectionRayOrig = outside ? point + bias : point - bias; 
        Vec_3_f reflective_color = cast_ray(reflectionRayOrig, reflectionDirection, objs, lights, depth + 1); 
 
        reflective_refractive_color = reflective_refractive_color + reflective_color * kr + refractive_color * (1 - kr); 
    }
    else if (material.is_reflective)
    {
        Vec_3_f R = reflect(dir, N);
        reflective_color = reflective_color + cast_ray(point + N, R, objs, lights, depth + 1) * 0.8;
    }

    Vec_3_f pixel_color {};
    
    for (auto light : lights)
    {
        Vec_3_f light_dir = (light.position - point).normalize();
        diffuse_light_intensity += light.intensity * max(0.f, light_dir * N);

        bool object_intersected = false;
        for (auto obj : objs)
        {
            if (obj->ray_intersect(point, light_dir, diffuse_light_intensity))
            {
                object_intersected = true;
                return_with_shadow = true;
                break;
            }
        }

        if (!object_intersected)
        {
            Vec_3_f h = (light_dir + (-dir)) * pow((light_dir + (-dir)).norm(), -1);
            pixel_color = pixel_color + material.diffuse_color * light.intensity * max(0.f, light_dir * N) 
                          + light_dir * light.intensity * pow(max(0.f, h * N), 10);                 
        }
        else
        {
            Vec_3_f h = (light_dir + (-dir)) * pow((light_dir + (-dir)).norm(), -1);
            pixel_color = pixel_color + Vec_3_f{0.08f, 0.08f, 0.08f} * 1 * max(0.f, light_dir * N)
                          + Vec_3_f{0.08f, 0.08f, 0.08f} * 1 * pow(max(0.f, h * N), 10);
        }
    }

    if (return_with_shadow)
        return pixel_color + reflective_color + reflective_refractive_color;
        
    return material.diffuse_color * diffuse_light_intensity + reflective_color + reflective_refractive_color;
}   

// In a nutshell: cast_ray in every pixel, and write it to ppm file
// Raycasting alghoritm
void render (const Objects objs, Lights &lights)
{
    const int dirr_err = mkdir("image", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    const int width = 1024;
    const int height = 768;
    const int fov = M_PI / 2.0;

    Image framebuffer{width * height};

    #pragma omp parallel for
    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            float x = (2 * (i + 0.5)/(float)width  - 1) * tan(fov / 2.) * width / (float)height;
            float y = -(2 * (j + 0.5)/(float)height - 1) * tan(fov / 2.);

            Vec_3_f dir = Vec_3_f{x, y, -1}.normalize();
            framebuffer[i + j * width] = cast_ray(Vec_3_f{0, 0, 0}, dir, objs, lights); 
        }
    }
    
    ofstream ofs;

    ofs.open("image/scena.ppm");
    ofs << "P6\n" << width << " " << height << "\n255\n";

    for (size_t i = 0; i < height * width; i++)
        for (size_t j = 0; j < 3; j++)
            ofs << (char)(255 * max(0.f, min(1.f, framebuffer[i][j])));

    ofs.close();
}


#endif