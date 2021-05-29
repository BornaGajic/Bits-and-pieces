import { Route } from '@angular/compiler/src/core';
import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, Validators } from '@angular/forms';
import { Router } from '@angular/router';
import { FileMetadata } from 'src/app/classes/file-metadata';
import { FilesService } from 'src/app/services/files.service';

@Component({
  selector: 'app-new-file',
  templateUrl: './new-file.component.html',
  styleUrls: ['./new-file.component.scss']
})
export class NewFileComponent implements OnInit {

  constructor(
    public router: Router,
    public filesService: FilesService
  ) { }


  form: FormGroup = new FormGroup({
    "name": new FormControl("", [Validators.required]),
    "size": new FormControl(Math.random() * 10),
    "added": new FormControl("")
  });

  ngOnInit(): void {
  }

  goToAllFiles() {
    this.router.navigate(["../"])
  }

  upload() {
    let fileMetadata: FileMetadata = this.form.value;
    fileMetadata.added = (new Date()).toISOString();
    this.filesService.postFile(fileMetadata)
      .subscribe((fileMetadata: FileMetadata) => {
        this.router.navigate(["../"])
      });
    
  }

}
