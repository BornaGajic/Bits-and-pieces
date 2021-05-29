import { HttpClient, HttpParams } from '@angular/common/http';
import { ElementRef, Injectable } from '@angular/core';
import { ɵangular_packages_core_testing_testing_c } from '@angular/core/testing';
import { BehaviorSubject, Observable, pipe, Subject } from 'rxjs';
import { subscribeOn, tap } from 'rxjs/operators';

import { FileMetadata } from '../classes/file-metadata';
import { PaginationInfo } from '../classes/pagination-info';


@Injectable({
  providedIn: 'root'
})
export class FilesService {
  private readonly filesRoute: string = "/api/files/";
  public files: BehaviorSubject<FileMetadata[]> = new BehaviorSubject<FileMetadata[]>([]);
  public paginationInfo: BehaviorSubject<PaginationInfo> = new BehaviorSubject<PaginationInfo>({
    itemsPerPage: 5,
    currentPage: 1,
    totalItems: 0
  });

  constructor(private http: HttpClient) {
  }

  getFiles(): Observable<any> {
    return this.http.get<any>(this.filesRoute, {
      params: {
        "currentPage": this.paginationInfo.value.currentPage.toString(),
        "itemsPerPage": this.paginationInfo.value.itemsPerPage.toString(),
      }
    });
  }

  postFile(file: FileMetadata): Observable<FileMetadata> {
    return this.http.post<FileMetadata>(this.filesRoute, file)
      .pipe(
        tap((fileMetadata: FileMetadata) => {
          let pageInfo: PaginationInfo = this.paginationInfo.value;

          pageInfo.totalItems = this.paginationInfo.value.totalItems + 1;

          if (this.files.value.length < this.paginationInfo.value.itemsPerPage)
          {
            this.files.value.push(fileMetadata);
            this.files.next(this.files.value);
          }

          this.paginationInfo.next(pageInfo);
        })
      );
  }

  removeFile(file: FileMetadata): Observable<FileMetadata> {
    return this.http.delete<any>(`${this.filesRoute}${file._id}`)
      .pipe(
        tap((response: any) => {
          
          let filesArr: FileMetadata[] = this.files.value;
          let pageInfo: PaginationInfo = this.paginationInfo.value;
          
          pageInfo.totalItems = this.paginationInfo.value.totalItems - 1;

          filesArr = filesArr.filter( (myFile: FileMetadata) => myFile._id != file._id );

          console.log(filesArr);

          this.http.get<FileMetadata>(`${this.filesRoute}/nextDocument`, {
            params: {
              currentPage: this.paginationInfo.value.currentPage.toString(),
              itemsPerPage: this.paginationInfo.value.itemsPerPage.toString()
            }
          }).subscribe((result: any) => {
            if (result.nextDocument != null)
            {
              filesArr.push(result.nextDocument);
            }
            
            this.files.next(filesArr);
        });

          this.paginationInfo.next(pageInfo);
        }) 
      );
  }
}
