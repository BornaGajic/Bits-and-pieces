using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Model.Common;
using Devbazaar.Service.Common.IClientTaskServices;
using AutoMapper;
using Devbazaar.Repository.Common;
using Devbazaar.DAL.EntityModels;
using System.Data.Entity;
using Devbazaar.Common.PageData.ClientTask;
using Devbazaar.Common.IPageData.ClientTask;

namespace Devbazaar.Service.ClientTaskServices
{
	public class ClientTaskService : IClientTaskService
	{
		IUnitOfWork UnitOfWork { get; set; }		
		IMapper Mapper { get; set; }

		public ClientTaskService (IMapper mapper, IUnitOfWork unitOfWork)
		{
			UnitOfWork = unitOfWork;
			Mapper = mapper;
		}

		public async Task<bool> CreateAsync (IClientTask newTask)
		{
			newTask.Id = Guid.NewGuid();

			try
			{
				await UnitOfWork.AddAsync<TaskEntity>(Mapper.Map<TaskEntity>(newTask));
			}
			catch (Exception e)
			{
				Console.WriteLine(e.Message);
				return false;
			}

			await UnitOfWork.CommitAsync<TaskEntity>();
			
			return true;
		}

		public async Task<bool> UpdateAsync (Dictionary<string, object> item, Guid clientTaskId)
		{
			try
			{
				var entity = await (from task in UnitOfWork.ClientTaskRepository.TableAsNoTracking where task.Id == clientTaskId select task).SingleAsync();

				foreach (var prop in typeof(BusinessEntity).GetProperties())
				{
					if (item.ContainsKey(prop.Name))
					{
						prop.SetValue(entity, item[prop.Name]);
					}
				}

				await UnitOfWork.UpdateAsync<TaskEntity>(entity);
			}
			catch (Exception e)
			{
				Console.WriteLine(e.Message);

				return false;
			}

			await UnitOfWork.CommitAsync<TaskEntity>();

			return true;
		}

		public async Task<bool> DeleteAsync (Guid taskId)
		{
			try
			{
				var clientTaskEntity = await UnitOfWork.ClientTaskRepository.GetByIdAsync(taskId);

				await UnitOfWork.DeleteAsync<TaskEntity>(Mapper.Map<TaskEntity>(clientTaskEntity));
			}
			catch (Exception e)
			{
				Console.WriteLine(e.Message);

				return false;
			}

			await UnitOfWork.CommitAsync<TaskEntity>();

			return true;
		}

		public async Task<List<IClientTaskReturnType>> PaginatedGetAsync (ClientTaskPage pageData, Guid? clientId = null)
		{
			var clientTasksTable = UnitOfWork.ClientTaskRepository.Table;
			var pageItemCount = Utility.Utility.PageItemLimit;

			if (clientId != null)
			{
				clientTasksTable = from clientTask in clientTasksTable where clientTask.ClientId == clientId select clientTask;
			}

			// filter
			clientTasksTable = from clientTask in clientTasksTable 
							   where clientTask.LowPrice >= pageData.LowPrice &&
									 clientTask.HighPrice <= pageData.HighPrice   
							   select clientTask;
			
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
			
			clientTasksTable = pageData.PageNumber == 1 ? clientTasksTable.Take(pageItemCount) 
														: clientTasksTable.Skip((pageData.PageNumber - 1) * pageItemCount).Take(pageItemCount);

			var clientTaskEntityList = await clientTasksTable.ToListAsync();

			var clientTaskReturnTypes = new List<IClientTaskReturnType>();

			foreach (var task in clientTaskEntityList)
			{
				var client = clientTasksTable.Where(b => b.ClientId == task.ClientId).Select(b => b.Client);
				
				var user = clientTasksTable.Where(b => b.ClientId == task.ClientId).Select(b => b.Client.User);

				task.Client = (await client.ToListAsync()).First();
				task.Client.User = (await user.ToListAsync()).First();

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

			return Mapper.Map<List<IClientTaskReturnType>>(clientTaskReturnTypes);
		}
	}
}
