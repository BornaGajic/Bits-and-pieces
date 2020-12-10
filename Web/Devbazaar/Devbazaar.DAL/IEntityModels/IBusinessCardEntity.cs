using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.EntityModels;

namespace Devbazaar.DAL.IEntityModels
{
	public interface IBusinessCardEntity : IBaseEntity
	{
		string Description { get; set; }
		string About { get; set; }
		bool Available { get; set; }

		[ForeignKey("Business")]
		Guid BusinessId { get; set; }

		BusinessEntity BusinessEntity { get; set; }
		ICollection<CategoryEntity> Categories { get; set; }
	}
}
