using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Devbazaar.Model.Common
{
	public interface IAdress
	{
		Guid Id { get; set; }
		string Name { get; set; }
		string City { get; set; }
		string Country { get; set; }
	}
}
