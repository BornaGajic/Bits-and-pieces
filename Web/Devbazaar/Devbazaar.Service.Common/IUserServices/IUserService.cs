using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Model.Common.IUser;
using static Devbazaar.Utility.Utility;

namespace Devbazaar.Service.Common.IUserServices
{
	public interface IUserService
	{
		Task<string> CreateAsync (IUser user, TypeOfUser tou);
		Task<string> LoginAsync (IUser user);
		Task<string> UpdateAsync (IUser user, TypeOfUser tou);
		Task<bool> DeleteAsync (IUser user);
	}
}
