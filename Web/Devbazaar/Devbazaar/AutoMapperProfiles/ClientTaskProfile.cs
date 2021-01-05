using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using AutoMapper;
using Devbazaar.DAL.EntityModels;
using Devbazaar.IRestModels.IClientTaskRest;
using Devbazaar.Model.Common;

namespace Devbazaar.AutoMapperProfiles
{
	public class ClientTaskProfile : Profile
	{
		public ClientTaskProfile ()
		{
			CreateMap<ICreateClientTaskRest, IClientTask>();
			CreateMap<IUpdateClientTaskRest, IClientTask>();
			CreateMap<IClientTask, TaskEntity>();
			
		}
	}
}