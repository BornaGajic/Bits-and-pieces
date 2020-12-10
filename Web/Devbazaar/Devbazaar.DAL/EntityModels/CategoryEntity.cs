using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.IEntityModels;

namespace Devbazaar.DAL.EntityModels
{
	public class CategoryEntity : BaseEntity, ICategoryEntity
	{
		public CategoryEntity ()
		{
			this.Tasks = new HashSet<TaskEntity>();
			this.BusinessCards = new HashSet<BusinessCardEntity>();
		}

		public string Name { get; set; }

		public virtual ICollection<TaskEntity> Tasks { get; set; }
		public virtual ICollection<BusinessCardEntity> BusinessCards { get; set; }
	}
}
