using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Common.IPageData.Business;
using Devbazaar.Model.Common;

namespace Devbazaar.Common.PageData.Business
{
	public class BusinessPageReturnType : IBusinessPageReturnType
	{
		public string Username { get; set; }
		public string Email { get; set; }
		public string Description { get; set; }
		public string About { get; set; }
		public string Website { get; set; }
		public bool Available { get; set; }
		public string Country { get; set; }
		public string City { get; set; }
		public string Logo { get; set; }

		public List<ICategory> Categories { get; set; }
	}
}
