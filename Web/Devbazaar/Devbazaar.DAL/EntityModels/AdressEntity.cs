using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.IEntityModels;

namespace Devbazaar.DAL.EntityModels
{
	public class AdressEntity : BaseEntity, IAdressEntity
	{
		public AdressEntity ()
		{
			this.Businesses = new HashSet<BusinessEntity>();
		}

		public string Name { get; set; }
		public string City { get; set; }
		public string Country { get; set; }

		public virtual ICollection<BusinessEntity> Businesses { get; set; }
	}
}
