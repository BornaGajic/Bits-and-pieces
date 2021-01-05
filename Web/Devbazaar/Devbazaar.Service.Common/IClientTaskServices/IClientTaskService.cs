using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Model.Common;

namespace Devbazaar.Service.Common.IClientTaskServices
{
	public interface IClientTaskService
	{
		Task<bool> CreateAsync (IClientTask newTask);
		Task<bool> UpdateAsync (IClientTask updatedTask);
		Task<bool> DeleteAsync (Guid taskId);
	}
}
