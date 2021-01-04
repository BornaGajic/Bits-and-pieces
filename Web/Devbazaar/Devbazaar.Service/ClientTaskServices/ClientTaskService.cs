using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Model.Common;
using Devbazaar.Service.Common.IClientTaskServices;

namespace Devbazaar.Service.ClientTaskServices
{
	public class ClientTaskService : IClientTaskService
	{
		public async Task<bool> CreateAsync (IClientTask newTask) => throw new NotImplementedException();
		public async Task<bool> UpdateAsync (IClientTask updatedTask) => throw new NotImplementedException();
		public async Task<bool> DeleteAsync (IClientTask task) => throw new NotImplementedException();
	}
}
