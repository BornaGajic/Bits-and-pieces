using System;
using System.Collections.Generic;
using System.Data.Entity;
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
		public async Task<Guid> CheckExistence (string email, string password)
		{
			List<UserEntity> registeredUser =  await (from user in TableAsNoTracking
													  where user.Email == email && user.Password == password
													  select user).ToListAsync();

			return registeredUser.Count > 0 ? registeredUser.First().Id : Guid.Empty;
		}
	}
}
