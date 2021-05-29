import { BrowserModule } from '@angular/platform-browser';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { NgModule } from '@angular/core';

import { AppComponent } from './app.component';

import { CollapseModule } from 'ngx-bootstrap/collapse';
import { NavbarComponent } from './components/navbar/navbar.component';
import { FilesComponent } from './components/files/files.component';
import { RemoveComponentTag } from './directives/remove-component-tag.directive';
import { FontAwesomeModule } from "@fortawesome/angular-fontawesome";
import { ExtensionPipe } from './pipes/extension.pipe';
import { ProfileComponent } from './components/profile/profile.component';
import { AppRoutingModule } from './app-routing.module';

import { HttpClientModule } from "@angular/common/http";
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { NewFileComponent } from './components/new-file/new-file.component';

@NgModule({
  declarations: [
    AppComponent,
    NavbarComponent,
    FilesComponent,
    RemoveComponentTag,
    ExtensionPipe,
    ProfileComponent,
    NewFileComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    ReactiveFormsModule,
    BrowserAnimationsModule,
    CollapseModule.forRoot(),
    FontAwesomeModule,
    AppRoutingModule,
    HttpClientModule,

  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
