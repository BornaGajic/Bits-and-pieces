using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using AutoMapper;
using Devbazaar.DAL.EntityModels;
using Devbazaar.Model;
using Devbazaar.Model.Common;
using Devbazaar.RestModels.BusinessRest;

namespace Devbazaar.AutoMapperProfiles
{
	public class BusinessProfile : Profile
	{
		public BusinessProfile ()
		{
			CreateMap<CreateBusinessRest, IBusiness>();
			CreateMap<IBusiness, BusinessEntity>();
			CreateMap<ICategory, CategoryEntity>();

			CreateMap<UpdateBusinessRest, IBusiness>();
		}
	}
}