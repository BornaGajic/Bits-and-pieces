import { Component, OnInit } from '@angular/core';

import { faUser, IconDefinition } from '@fortawesome/free-solid-svg-icons';

@Component({
  selector: 'app-navbar',
  templateUrl: './navbar.component.html',
  styleUrls: ['./navbar.component.scss']
})
export class NavbarComponent implements OnInit {

  faUser: IconDefinition = faUser;

  username: string = "Borna";
  isCollapsed: boolean = true;

  constructor() { }

  ngOnInit() {
  }

}
