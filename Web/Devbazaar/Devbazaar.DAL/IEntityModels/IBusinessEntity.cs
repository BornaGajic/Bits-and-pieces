﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.EntityModels;

namespace Devbazaar.DAL.IEntityModels
{
	public interface IBusinessEntity : IBaseEntity
	{
		string Description { get; set; }
		string About { get; set; }
		string Website { get; set; }
		bool Available { get; set; }
		string Country { get; set; }
		string City { get; set; }
		byte[] Logo { get; set; }

		UserEntity User { get; set; }
		ICollection<TaskEntity> Tasks { get; set; }
		ICollection<CategoryEntity> Categories { get; set; }
	}
}
