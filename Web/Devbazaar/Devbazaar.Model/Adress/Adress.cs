using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Model.Common;

namespace Devbazaar.Model
{
	public class Adress : IAdress
	{
		public Guid Id { get; set; }
		public string Name { get; set; }
		public string City { get; set; }
		public string Country { get; set; }
	}
}
