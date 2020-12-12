using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL;

namespace Devbazaar.Repository.Common.Repositories
{
	public interface IUserRepository
	{
		Task<Guid> CheckExistence (string email, string username);
	}
}
