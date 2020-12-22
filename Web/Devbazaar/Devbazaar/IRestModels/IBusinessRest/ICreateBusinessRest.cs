using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Model;
using Devbazaar.Model.Common;

namespace Devbazaar.IRestModels.IBusinessRest
{
	public interface ICreateBusinessRest
	{
		string Description { get; set; }
		string About { get; set; }
		bool Available { get; set; }
		string Country { get; set; }
		string City { get; set; }
		List<Category> Categories { get; set; }
	}
}
