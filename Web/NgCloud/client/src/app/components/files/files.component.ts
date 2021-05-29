import { Component, ElementRef, Input, OnInit, Renderer2, SimpleChange } from '@angular/core';

import { FileMetadata } from '../../classes/file-metadata';

import { faDownload, faTimes, IconDefinition } from "@fortawesome/free-solid-svg-icons";
import { Router } from '@angular/router';
import { FilesService } from 'src/app/services/files.service';
import { PaginationInfo } from 'src/app/classes/pagination-info';
import { last } from 'rxjs/operators';
import { CombineLatestOperator } from 'rxjs/internal/observable/combineLatest';

@Component({
  selector: 'app-files',
  templateUrl: './files.component.html',
  styleUrls: ['./files.component.scss']
})
export class FilesComponent implements OnInit {
  faDownload: IconDefinition = faDownload;
  faTimes: IconDefinition = faTimes;

  selectedItemsPerPage: number = this.filesService.paginationInfo.value.itemsPerPage;

  constructor(
    public router: Router,
	  public filesService: FilesService,
	  private renderer: Renderer2
  ) { 
    
  }

  ngOnInit()
  {
	  this.loadPage();
    
    this.filesService.paginationInfo.subscribe((newValue: PaginationInfo) => {
        let pageNumberList = document.getElementById("pageNumberList");

        if (newValue.totalItems != 0)
        {
          let totalItems: number = newValue.totalItems;
          let itemsPerPage: number = newValue.itemsPerPage;
          let totalItemDiff = totalItems / itemsPerPage;
          
          let pageNumbers: number =  Math.ceil(totalItemDiff);
          let lastNumber: number = parseInt(pageNumberList?.lastChild?.previousSibling?.textContent ?? "0");
          lastNumber = isNaN(lastNumber) ? 0 : lastNumber;

          if (pageNumbers - lastNumber >= 0)
          {  
            while (lastNumber != pageNumbers)
            {
              this.addNewPageNumberElement((lastNumber + 1).toString());
              lastNumber += 1;
            }
          }
          else
          {
            for (let i = 1; i <= Math.abs(pageNumbers - lastNumber); i++)
            {
              let lastChild = pageNumberList?.children[pageNumberList?.children.length - 1 - i]
              this.renderer.removeChild(pageNumberList, lastChild);
            }
          }
        }
        else if (pageNumberList!.children.length < 3) // it will not be undefined
        {
          this.addNewPageNumberElement("1");
        }
    });
  }

  logChange()
  {
    return JSON.stringify(this.filesService.paginationInfo.value);
  }

  goToNewFile () 
  {
    this.router.navigate(["files/new-file"]);
  } 

  setItemsPerPage ()
  {
    this.filesService.paginationInfo.value.itemsPerPage = this.selectedItemsPerPage;
    this.filesService.paginationInfo.value.currentPage = 1;

    this.filesService.paginationInfo.next(this.filesService.paginationInfo.value);
    
    this.loadPage();
  }

  remove (fileMetadata: FileMetadata) 
  {
	  this.filesService.removeFile(fileMetadata).subscribe();
  }

  loadPage ()
  {
    this.filesService.getFiles()
      .subscribe((result: any) => {
        let pageInfo: PaginationInfo = this.filesService.paginationInfo.value;
        pageInfo.totalItems = result.totalItems;

        console.log(result);

        this.filesService.files.next(result.files);
        this.filesService.paginationInfo.next(pageInfo);
    });
  }

  addNewPageNumberElement (pageNumber: string) : void
  {
    let pageNumberList: any = document.getElementById("pageNumberList");

	  let newPageNumber: HTMLElement = this.renderer.createElement("li");
	  this.renderer.setAttribute(newPageNumber, "class", "page-item");
    
    let linkToNewPage: HTMLElement = this.renderer.createElement("a");
    this.renderer.setAttribute(linkToNewPage, "class", "page-link");
    this.renderer.setProperty(linkToNewPage, "innerText", pageNumber);
    this.renderer.listen(linkToNewPage, "click", () => { this.onNewPageClick(pageNumber) });

    this.renderer.appendChild(newPageNumber, linkToNewPage);
    
    try
    {
      this.renderer.insertBefore(pageNumberList, newPageNumber, pageNumberList.lastChild);
    }
    catch (e)
    {
      console.log(e);
      return;
    }
  }

  onNewPageClick (pageNumber: string)
  {
    let lastPage = this.filesService.paginationInfo.value.currentPage;
    let newPage = this.filesService.paginationInfo.value;

    switch (pageNumber) {
      case "previous":
        newPage.currentPage -= 1;  
        break;
      case "next":
        newPage.currentPage += 1;
        break
      default:
        newPage.currentPage = parseInt(pageNumber);
        break;
    }

    let totalItemsDiff = Math.ceil(this.filesService.paginationInfo.value.totalItems / this.filesService.paginationInfo.value.itemsPerPage);
    if (newPage.currentPage <= 0 || newPage.currentPage > totalItemsDiff)
    {
      newPage.currentPage = lastPage;
      return;
    }

    this.filesService.paginationInfo.next(newPage); 

    this.loadPage();
  }
}
