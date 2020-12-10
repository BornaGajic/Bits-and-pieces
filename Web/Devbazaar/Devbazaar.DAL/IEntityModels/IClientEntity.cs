using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.EntityModels;

namespace Devbazaar.DAL.IEntityModels
{
	public interface IClientEntity : IBaseEntity
	{
		string Username { get; set; }
		string Password { get; set; }
		string Email { get; set; }

		ICollection<TaskEntity> Tasks { get; set; }
	}
}
