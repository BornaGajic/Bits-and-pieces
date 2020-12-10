using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Devbazaar.IRestModels.IBusinessCardRest;
using Devbazaar.Model;
using Devbazaar.Model.Common;

namespace Devbazaar.RestModels.BusinessCardRest
{
	public class CreateBusinessCardRest : ICreateBusinessCardRest
	{
		public Guid BusinessId { get; set; }
		public string Description { get; set; }
		public string About { get; set; }
		public bool Available { get; set; }
		public List<ICategory> Categories { get; set; }
	}
}