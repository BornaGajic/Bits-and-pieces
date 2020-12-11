﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.IEntityModels;

namespace Devbazaar.DAL.EntityModels
{
	public class ClientEntity : BaseEntity, IClientEntity
	{
		public virtual UserEntity User { get; set; }
		public ICollection<TaskEntity> Tasks { get; set; }
	}
}
