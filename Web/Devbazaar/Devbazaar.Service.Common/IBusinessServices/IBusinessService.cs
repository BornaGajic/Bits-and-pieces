using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Common.IPageData.Business;
using Devbazaar.Common.IPageData.ClientTask;
using Devbazaar.Common.PageData.Business;
using Devbazaar.Common.PageData.ClientTask;
using Devbazaar.DAL.EntityModels;
using Devbazaar.Model.Common;

namespace Devbazaar.Service.Common.IBusinessServices
{
	public interface IBusinessService
	{
		Task<int> CreateAsync (IBusiness newBusiness, List<ICategory> categories, Guid userId);
		Task<int> UpdateAsync (Dictionary<string, object> item, Guid businessId);
		Task<List<IBusinessPageReturnType>> PaginatedGetAsync (BusinessPage pageData, Guid? userId = null);
		Task<List<IClientTaskReturnType>> AcquiredTasks (ClientTaskPage pageData, Guid businessId);
	}
}
