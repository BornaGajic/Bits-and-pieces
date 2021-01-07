using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Model.Common;

namespace Devbazaar.Common.IPageData.Business
{
	public interface IBusinessPageReturnType
	{
		string Username { get; set; }
		string Email { get; set; }
		string Description { get; set; }
		string About { get; set; }
		string Website { get; set; }
		bool Available { get; set; }
		string Country { get; set; }
		string City { get; set; }
		string Logo { get; set; }

		List<ICategory> Categories { get; set; }
	}
}
