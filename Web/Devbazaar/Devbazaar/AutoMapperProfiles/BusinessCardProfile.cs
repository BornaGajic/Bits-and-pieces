using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using AutoMapper;
using Devbazaar.DAL.EntityModels;
using Devbazaar.Model;
using Devbazaar.Model.Common;
using Devbazaar.RestModels.BusinessCardRest;

namespace Devbazaar.AutoMapperProfiles
{
	public class BusinessCardProfile : Profile
	{
		public BusinessCardProfile ()
		{
			CreateMap<CreateBusinessCardRest, IBusinessCard>();
			CreateMap<IBusinessCard, BusinessCardEntity>();
			CreateMap<ICategory, CategoryEntity>();

			CreateMap<UpdateBusinessCardRest, IBusinessCard>();
		}
	}
}