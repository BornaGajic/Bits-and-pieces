using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.Context;
using Devbazaar.DAL.EntityModels;
using Devbazaar.Repository.Common.Repositories;

namespace Devbazaar.Repository.Repositories
{
	public class UserRepository : BaseRepository<UserEntity>, IUserRepository
	{
		public UserRepository (DevbazaarDbContext context) : base(context)
		{
		}
	}
}
