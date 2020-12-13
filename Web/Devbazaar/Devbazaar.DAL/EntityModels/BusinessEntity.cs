using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
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
			this.Categories = new HashSet<CategoryEntity>();
		}

		public string Description { get; set; }
		public string About { get; set; }
		public bool Available { get; set; }

		public virtual ICollection<CategoryEntity> Categories { get; set; }
		public virtual ICollection<AdressEntity> Adresses { get; set; }
		public virtual UserEntity User { get; set; }
	}
}
