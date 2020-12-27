using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.EntityModels;
using Devbazaar.Model.Common;

namespace Devbazaar.Service.Common.IBusinessServices
{
	public interface IBusinessService
	{
		Task<int> CreateAsync (IBusiness newBusiness, List<ICategory> categories, Guid userId);
		Task<int> UpdateAsync (IBusiness updatedBusiness);
		Task<List<IBusiness>> PaginatedGetAsync (int page);
	}
}
