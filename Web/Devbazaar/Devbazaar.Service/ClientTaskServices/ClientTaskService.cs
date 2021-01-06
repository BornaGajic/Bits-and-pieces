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

		public async Task<List<IClientTask>> PaginatedGetAsync (ClientTaskPage pageData, Guid? clientId = null)
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

			if (pageData.NewestDate.Value == true)
			{
				clientTasksTable = clientTasksTable.OrderByDescending(p => p.DateAdded);
			}
			else if (pageData.NewestDate.Value == false)
			{
				clientTasksTable = clientTasksTable.OrderBy(p => p.DateAdded);
			}

			if (pageData.PageNumber == 1)
			{
				clientTasksTable = clientTasksTable.Take(pageItemCount);
			}
			else
			{
				clientTasksTable = clientTasksTable.Skip((pageData.PageNumber - 1) * pageItemCount).Take(pageItemCount);
			}

			var clientTaskEntityList = await clientTasksTable.ToListAsync();

			foreach (var task in clientTaskEntityList)
			{
				var client = clientTasksTable.Where(b => b.ClientId == task.ClientId).Select(b => b.Client);
				
				var user = clientTasksTable.Where(b => b.ClientId == task.ClientId).Select(b => b.Client.User);

				task.Client = (await client.ToListAsync()).First();
				task.Client.User = (await user.ToListAsync()).First();
			}

			return Mapper.Map<List<IClientTask>>(clientTaskEntityList);
		}
	}
}
