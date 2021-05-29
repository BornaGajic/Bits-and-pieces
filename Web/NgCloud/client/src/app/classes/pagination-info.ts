export class PaginationInfo
{
    constructor (
        public itemsPerPage: number,
        public currentPage: number,
        public totalItems: number
    )
    {
        
    }
};