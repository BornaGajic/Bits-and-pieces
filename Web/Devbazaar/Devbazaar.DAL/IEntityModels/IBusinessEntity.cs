using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.EntityModels;

namespace Devbazaar.DAL.IEntityModels
{
	public interface IBusinessEntity : IBaseEntity
	{
		ICollection<AdressEntity> Adresses { get; set; }
		BusinessCardEntity BusinessCard { get; set; }
		UserEntity User { get; set; }
	}
}
