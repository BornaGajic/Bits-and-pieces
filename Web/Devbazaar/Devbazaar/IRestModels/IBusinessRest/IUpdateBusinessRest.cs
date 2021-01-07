﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Devbazaar.IRestModels.IBusinessRest
{
	public interface IUpdateBusinessRest
	{
		string Description { get; set; }
		string About { get; set; }
		string Website { get; set; }
		bool? Available { get; set; }
		string Country { get; set; }
		string City { get; set; }
		string Logo { get; set; }
	}
}
