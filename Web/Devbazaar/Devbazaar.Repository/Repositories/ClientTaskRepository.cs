using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.EntityModels;
using Devbazaar.Repository.Common.Repositories;
using Devbazaar.DAL.Context;

namespace Devbazaar.Repository.Repositories
{
	public class ClientTaskRepository : BaseRepository<TaskEntity>, IClientTaskRepository
	{
		public ClientTaskRepository (DevbazaarDbContext context) : base(context)
		{
		}

		public async Task<TaskEntity> GetByIdAsync (Guid id)
		{
			var clientTaskList = from clientTask in Table where clientTask.Id == id select clientTask;

			return await Task.Run(() => { return clientTaskList.First(); })  ?? null;
		}
	}
}
