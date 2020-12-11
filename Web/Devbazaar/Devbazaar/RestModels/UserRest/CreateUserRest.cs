using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Devbazaar.IRestModels.IUserRest;

namespace Devbazaar.RestModels.UserRest
{
	public class CreateUserRest : ICreateUserRest
	{
		public string Username { get; set; }
		public string Password { get; set; }
		public string Email { get; set; }
	}
}