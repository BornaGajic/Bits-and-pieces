using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.IEntityModels;

namespace Devbazaar.DAL.EntityModels
{
	public class ClientEntity : BaseEntity, IClientEntity
	{
		public string Username { get; set; }
		public string Password { get; set; }
		public string Email { get; set; }

		public ICollection<TaskEntity> Tasks { get; set; }
	}
}
