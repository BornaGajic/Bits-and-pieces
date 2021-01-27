﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Devbazaar.Common.DTO.Business
{
	public class BusinessReturnTypeDTO
	{
		public Guid Id { get; set; }
		public string Username { get; set; }
		public string Email { get; set; }
		public string Description { get; set; }
		public string About { get; set; }
		public string Website { get; set; }
		public bool Available { get; set; }
		public string Country { get; set; }
		public string City { get; set; }
		public int PostalCode { get; set; }
	}
}
