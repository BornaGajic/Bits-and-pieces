using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Devbazaar.Model.Common
{
	public interface IBusinessCard
	{
		Guid Id { get; set; }
		string Description { get; set; }
		string About { get; set; }
		bool Available { get; set; }
	}
}
