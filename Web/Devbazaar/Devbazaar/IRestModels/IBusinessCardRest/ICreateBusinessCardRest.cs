using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Model;
using Devbazaar.Model.Common;

namespace Devbazaar.IRestModels.IBusinessCardRest
{
	public interface ICreateBusinessCardRest
	{
		Guid BusinessId { get; set; }
		string Description { get; set; }
		string About { get; set; }
		bool Available { get; set; }
		List<ICategory> Categories { get; set; }
	}
}
