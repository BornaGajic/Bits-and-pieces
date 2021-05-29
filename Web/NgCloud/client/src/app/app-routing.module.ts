import { Route, RouterLink, RouterModule } from "@angular/router";
import { NgModule } from "@angular/core";
import { FilesComponent } from "./components/files/files.component";
import { NewFileComponent } from "./components/new-file/new-file.component";
import { ProfileComponent } from "./components/profile/profile.component";

const routes: Route[] =  [
    { path: "", pathMatch: "full", redirectTo: "files" },
    { path: "files", component: FilesComponent },
    { path: "files/new-file", component: NewFileComponent },
    { path: "profile", component: ProfileComponent },
    { path: "**", redirectTo: "files" },
]


@NgModule({
    imports: [
        RouterModule.forRoot(routes)
    ],
    exports: [
        RouterModule
    ]
})
export class AppRoutingModule {}