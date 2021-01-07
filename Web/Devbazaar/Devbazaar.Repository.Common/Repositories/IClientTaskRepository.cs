using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Common.IPageData.ClientTask;
using Devbazaar.Common.PageData.ClientTask;
using Devbazaar.DAL.EntityModels;

namespace Devbazaar.Repository.Common.Repositories
{
	public interface IClientTaskRepository : IBaseRepository<TaskEntity> 
	{
		Task<TaskEntity> GetByIdAsync (Guid id);
		Task<List<IClientTaskReturnType>> PaginatedGetAsync (ClientTaskPage pageData, Guid? clientId = null, Guid? businessId = null);
	}
}
