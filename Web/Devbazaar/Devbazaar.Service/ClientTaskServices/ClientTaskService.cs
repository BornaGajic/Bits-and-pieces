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

		public async Task<bool> UpdateAsync (IClientTask updatedTask)
		{
			try
			{
				await UnitOfWork.UpdateAsync<TaskEntity>(Mapper.Map<TaskEntity>(updatedTask));
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
	}
}
