using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using System.Web.Http;
using AutoMapper;
using Devbazaar.Model.Common.IUser;
using Devbazaar.RestModels.UserRest;
using Devbazaar.Service.Common.IUserService;
using Microsoft.AspNet.Identity;
using static Devbazaar.Utility.Utility;
using IUser = Devbazaar.Model.Common.IUser.IUser;

namespace Devbazaar.Controllers
{
    [RoutePrefix("Devbazaar/User")]
    public class UserController : ApiController
    {
        protected IUserService LoginService { get; set; }
        protected IMapper Mapper { get; set; }

        public UserController (IUserService loginService, IMapper mapper)
        {
             LoginService = loginService;
             Mapper = mapper;
        }

        [AllowAnonymous]
        [HttpPost]
        [Route("Register")]
        public async Task<HttpResponseMessage> CreateAsync ([FromBody] CreateUserRest newUser, [FromUri] TypeOfUser tou)
        {
            var user = Mapper.Map<IUser>(newUser);

            string token;
            try
            {
                token = await LoginService.CreateAsync(user, tou);

                if (token == "User already exists")
                {
                    return Request.CreateResponse(HttpStatusCode.Conflict, token);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);

                return new HttpResponseMessage(HttpStatusCode.BadRequest);
            } 

            return Request.CreateResponse(HttpStatusCode.OK, token);
        }

        [AllowAnonymous]
        [HttpGet]
        [Route("Login")]
        public async Task<HttpResponseMessage> LoginAsync ([FromBody] LoginRest loginData)
        {
            var user = Mapper.Map<IUser>(loginData);

            try
            {
                string token = await LoginService.LoginAsync(user);

                return string.IsNullOrEmpty(token) ? Request.CreateResponse(HttpStatusCode.NotFound) : Request.CreateResponse(HttpStatusCode.OK, token);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                
                return Request.CreateResponse(HttpStatusCode.BadRequest, e.Message);
            }
        }

        [Authorize]
        [HttpPut]
        [Route("Update")]
        public async Task<HttpResponseMessage> UpdateAsync ([FromBody] UpdateUserRest updateData, [FromUri] TypeOfUser tou)
        {
            var user = Mapper.Map<IUser>(updateData);
            string token = await LoginService.UpdateAsync(user, tou);

            if (!string.IsNullOrEmpty(token))
            {
                return Request.CreateResponse(HttpStatusCode.OK, token);
            }
            else
            {
                return Request.CreateResponse(HttpStatusCode.BadRequest, string.Empty);
            }
        }

        [Authorize]
        [HttpDelete]
        [Route("Delete")]
        public async Task<HttpResponseMessage> DeleteAsync ([FromBody] DeleteUserRest deleteUser)
        {
            var user = Mapper.Map<IUser>(deleteUser);

            try
            {
                await LoginService.DeleteAsync(user);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);

                return Request.CreateResponse(HttpStatusCode.BadRequest, e.Message);
            }

            return new HttpResponseMessage(HttpStatusCode.OK);
        }
    }
}
