using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using Devbazaar.IRestModels.IBusinessRest;
using Devbazaar.Model;
using Devbazaar.Model.Common;

namespace Devbazaar.RestModels.BusinessRest
{
	public class CreateBusinessRest : ICreateBusinessCardRest
	{
		public string Description { get; set; }
		public string About { get; set; }
		[Required]
		public bool Available { get; set; }
		[Required]
		public List<Category> Categories { get; set; }
	}
}