using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.EntityModels;

namespace Devbazaar.Repository.Common.Repositories
{
	public interface IBusinessRepository
	{
		Task<BusinessEntity> GetByIdAsync (Guid id);
		Task<IEnumerable<BusinessEntity>> PaginatedGetAsync (int page, int count);
	}
}
