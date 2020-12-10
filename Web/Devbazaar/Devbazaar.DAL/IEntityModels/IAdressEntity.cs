using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.EntityModels;

namespace Devbazaar.DAL.IEntityModels
{
	public interface IAdressEntity : IBaseEntity
	{
		string Name { get; set; }
		string City { get; set; }
		string Country { get; set; }

		ICollection<BusinessEntity> Businesses { get; set; }
	}
}
