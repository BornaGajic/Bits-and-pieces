﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using Devbazaar.IRestModels.IClientTaskRest;

namespace Devbazaar.RestModels.UserTaskRest
{
	public class CreateUserTaskRest : ICreateClientTaskRest
	{
		[Required]
		public string Description { get; set; }
		public int LowPrice { get; set; }
		public int HighPrice { get; set; }
	}
}