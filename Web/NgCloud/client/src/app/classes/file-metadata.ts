export class FileMetadata {
    constructor(
        public name: string,
        public added: string,
        public size: number,
        public _id?: any
    ) {
        this.size = 0
    }
}
