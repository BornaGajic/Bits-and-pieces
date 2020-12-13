using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Devbazaar.IRestModels.IBusinessRest;

namespace Devbazaar.RestModels.BusinessRest
{
	public class UpdateBusinessRest : IUpdateBusinessCardRest
	{
		public string Description { get; set; }
		public string About { get; set; }
		public bool Available { get; set; }
	}
}