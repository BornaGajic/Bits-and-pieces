﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Devbazaar.Common.PageData.Business
{
	public class BusinessPage : Page
	{
		// filter
		public bool? Availability { get; set; }
		public string City { get; set; } = string.Empty;
		public string Country { get; set; } = string.Empty;

		// sort
		public bool? NameAsc { get; set; }
	}
}
