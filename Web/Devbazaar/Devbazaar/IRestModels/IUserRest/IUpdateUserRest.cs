﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Devbazaar.IRestModels.IUserRest
{
	public interface IUpdateUserRest
	{
		string Username { get; set; }
		string Email { get; set; }
		string Password { get; set; }
	}
}
