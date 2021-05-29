import { Directive, ElementRef, OnInit } from '@angular/core';

@Directive({
  selector: '[appRemoveComponentTag]'
})
export class RemoveComponentTag implements OnInit {

  constructor(private el: ElementRef) { }

  ngOnInit() {
    let nativeElement: HTMLElement = this.el.nativeElement;
    let parentElement: HTMLElement | null = nativeElement.parentElement;

    while(nativeElement.firstChild)
      parentElement?.insertBefore(nativeElement.firstChild, nativeElement);

    parentElement?.removeChild(nativeElement);
  }

}
