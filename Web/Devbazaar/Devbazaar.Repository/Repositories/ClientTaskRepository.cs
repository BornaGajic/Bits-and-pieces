using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.EntityModels;
using Devbazaar.Repository.Common.Repositories;
using Devbazaar.DAL.Context;
using AutoMapper;
using Devbazaar.Common.IPageData.ClientTask;
using Devbazaar.Common.PageData.ClientTask;

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

		public async Task<TaskEntity> UpdateAsync (Dictionary<string, object> item, Guid clientTaskId)
		{
			TaskEntity entity;
			try
			{
				 entity = await (from task in Table where task.Id == clientTaskId select task).SingleAsync();

				foreach (var prop in typeof(TaskEntity).GetProperties())
				{
					if (item.ContainsKey(prop.Name))
					{
						prop.SetValue(entity, item[prop.Name]);
					}
				}
			}
			catch (Exception e)
			{
				Console.WriteLine(e.Message);

				return null;
			}

			return entity;
		}

		public async Task<List<IClientTaskReturnType>> PaginatedGetAsync (ClientTaskPage pageData, Guid? clientId = null, Guid? businessId = null)
		{
			var clientTasksTable = Table;
			var pageItemCount = Utility.Utility.PageItemLimit;

			if (clientId != null)
			{
				clientTasksTable = from clientTask in clientTasksTable where clientTask.ClientId == clientId select clientTask;
			}
			else if (businessId != null)
			{
				clientTasksTable = from clientTask in clientTasksTable where clientTask.BusinessId == businessId select clientTask;
			}

			ApplyPageSeasoning(pageData, clientTasksTable);

			clientTasksTable = pageData.PageNumber == 1 ? clientTasksTable.Take(pageItemCount) 
														: clientTasksTable.Skip((pageData.PageNumber - 1) * pageItemCount).Take(pageItemCount);

			var clientTaskEntityList = await clientTasksTable.ToListAsync();

			var clientTaskReturnTypes = new List<IClientTaskReturnType>();

			// testiraj jel trebam dohvatiti clienta/usera ili EF to napravi automatski

			foreach (var task in clientTaskEntityList)
			{
				//var client = clientTasksTable.Where(b => b.ClientId == task.ClientId).Select(b => b.Client);
				
				//var user = clientTasksTable.Where(b => b.ClientId == task.ClientId).Select(b => b.Client.User);

				//task.Client = await client.SingleAsync();
				//task.Client.User = await user.SingleAsync();

				clientTaskReturnTypes.Add(
					new ClientTaskReturnType ()
					{
						Description = task.Description,
						LowPrice = task.LowPrice,
						HighPrice = task.HighPrice,
						Username = task.Client.User.Username,
						Email = task.Client.User.Email,
						DateAdded = task.DateAdded,
						ClientId = task.ClientId,
						ClientTaskId = task.Id
					}
				);
			}

			return clientTaskReturnTypes;
		}

		private void ApplyPageSeasoning (ClientTaskPage pageData, IQueryable<TaskEntity> clientTasksTable)
		{
			// filter
			clientTasksTable = from clientTask in clientTasksTable 
							   where clientTask.LowPrice >= pageData.LowPrice &&
									 clientTask.HighPrice <= pageData.HighPrice   
							   select clientTask;
			
			// sort
			if (pageData.OldestDate.HasValue)
			{
				clientTasksTable = clientTasksTable.OrderBy(p => DbFunctions.CreateTime(p.DateAdded.Hour, p.DateAdded.Minute, p.DateAdded.Second))
												   .ThenBy(p => DbFunctions.CreateDateTime(p.DateAdded.Year, p.DateAdded.Month, null, null, null, null));
			}
			else
			{
				clientTasksTable = clientTasksTable.OrderByDescending(p => DbFunctions.CreateTime(p.DateAdded.Hour, p.DateAdded.Minute, p.DateAdded.Second))
												   .ThenByDescending(p => DbFunctions.CreateDateTime(p.DateAdded.Year, p.DateAdded.Month, null, null, null, null));
			}
		}
	}
}
