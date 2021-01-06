using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using Devbazaar.IRestModels.IUserRest;

namespace Devbazaar.RestModels.UserRest
{
	public class UpdateUserRest : IUpdateUserRest
	{
		public string Username { get; set; } = null;

		[EmailAddress]
		public string Email { get; set; } = null;

		public string Password { get; set; } = null;
	}
}