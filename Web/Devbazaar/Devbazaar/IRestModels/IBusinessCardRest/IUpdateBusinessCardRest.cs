using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Devbazaar.IRestModels.IBusinessCardRest
{
	public interface IUpdateBusinessCardRest
	{
		string Description { get; set; }
		string About { get; set; }
		bool Available { get; set; }
	}
}
