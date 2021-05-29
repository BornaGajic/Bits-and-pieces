import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'extension'
})
export class ExtensionPipe implements PipeTransform {

  availableExtensions: string[] = ["doc", "jpg", "mp3", "pdf", "ppt", "txt", "xls"];

  transform(value: string, ...args: unknown[]): string {
    let s: string[] = value.split(".")
    let path: string = s[s.length - 1];
    if (path[path.length - 1] == "x")
      path = path.substring(0, path.length - 1);
  
    if (!this.availableExtensions.includes(path))
      path = "file";

    return `../assets/images/${path}.png`;
  }

}
