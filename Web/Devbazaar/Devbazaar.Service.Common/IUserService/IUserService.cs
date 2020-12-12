using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Model.Common.IUser;
using static Devbazaar.Utility.Utility;

namespace Devbazaar.Service.Common.IUserService
{
	public interface IUserService
	{
		Task<string> CreateAsync (IUser user, TypeOfUser tou);
		Task<string> LoginAsync (IUser user);
		Task<bool> UpdateAsync (IUser user);
		Task<bool> DeleteAsync (IUser user);
	}
}
