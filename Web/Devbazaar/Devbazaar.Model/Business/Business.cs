using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Model.Common;

namespace Devbazaar.Model
{
	public class Business : Devbazaar.Model.User.User, IBusiness
	{
		public string Description { get; set; }
		public string About { get; set; }
		public bool Available { get; set; }
	}
}
