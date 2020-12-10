using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.EntityModels;

namespace Devbazaar.DAL.IEntityModels
{
	public interface ITaskEntity : IBaseEntity
	{
		string Description { get; set; }
		int LowPrice { get; set; }
		int HighPrice { get; set; }

		Guid ClientId { get; set; }
		ClientEntity Client { get; set; }

		ICollection<CategoryEntity> Categories { get; set; }
	}
}
