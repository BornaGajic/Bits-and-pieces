using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.IEntityModels;

namespace Devbazaar.DAL.EntityModels
{
	public class BusinessEntity : BaseEntity, IBusinessEntity
	{
		public BusinessEntity ()
		{
			this.Adresses = new HashSet<AdressEntity>();
		}

		public string Name { get; set; }
		public string Password { get; set; }
		public string Email { get; set; }

		public virtual ICollection<AdressEntity> Adresses { get; set; }
		public virtual BusinessCardEntity BusinessCard { get; set; }
	}
}
