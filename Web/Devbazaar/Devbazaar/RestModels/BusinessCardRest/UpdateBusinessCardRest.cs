using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Devbazaar.IRestModels.IBusinessCardRest;

namespace Devbazaar.RestModels.BusinessCardRest
{
	public class UpdateBusinessCardRest : IUpdateBusinessCardRest
	{
		public string Description { get; set; }
		public string About { get; set; }
		public bool Available { get; set; }
	}
}