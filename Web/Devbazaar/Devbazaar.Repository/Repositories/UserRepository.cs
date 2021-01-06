using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.Context;
using Devbazaar.DAL.EntityModels;
using Devbazaar.Repository.Common.Repositories;
using static Devbazaar.Utility.Utility;

namespace Devbazaar.Repository.Repositories
{
	public class UserRepository : BaseRepository<UserEntity>, IUserRepository
	{
		public UserRepository (DevbazaarDbContext context) : base(context)
		{
		}

		public async Task<Guid> CheckExistence (string email, string username)
		{
			var x = from user in TableAsNoTracking where user.Email == email && user.Username == username select user;
			
			var registeredUser =  await (x).ToListAsync();

			{}

			if (registeredUser != null)
				return registeredUser.Count > 0 ? registeredUser.First().Id : Guid.Empty;
			else
				return Guid.Empty;
		}
	}
}
