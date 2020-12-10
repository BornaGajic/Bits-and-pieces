using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Service.Common.IBusinessCardServices;
using Devbazaar.Repository.Common;
using Devbazaar.Model.Common;
using AutoMapper;
using Devbazaar.DAL.EntityModels;

namespace Devbazaar.Service.BusinessCardServices
{
	public class BusinessCardService : IBusinessCardService
	{
		public IUnitOfWork UnitOfWork { get; set; }
		public IMapper Mapper { get; set; }

		public BusinessCardService (IUnitOfWork unitOfWork, IMapper mapper)
		{
			UnitOfWork = unitOfWork;
			Mapper = mapper;
		}

		 public async Task<int> CreateAsync (IBusinessCard newBusinessCard, List<ICategory> categories, Guid businessId)
		 {
			newBusinessCard.Id = Guid.NewGuid();
			var businessCardEntity = Mapper.Map<BusinessCardEntity>(newBusinessCard);
			
			businessCardEntity.BusinessId = businessId;

			// trebam novi repo za CategoryBusinessCard
			//var categoryEntity = Mapper.Map<List<CategoryEntity>>(categories);
			//businessCardEntity.Categories = categoryEntity;

			await UnitOfWork.AddAsync<BusinessCardEntity>(businessCardEntity);

			await UnitOfWork.CommitAsync<BusinessCardEntity>();

			return await Task.FromResult(1); 
		 }

		 public async Task<int> UpdateAsync (IBusinessCard updatedBusinessCard)
		 {
			updatedBusinessCard.Id = Guid.NewGuid();
			var entity = Mapper.Map<BusinessCardEntity>(updatedBusinessCard);

			await UnitOfWork.UpdateAsync<BusinessCardEntity>(entity);
			
			await UnitOfWork.CommitAsync<BusinessCardEntity>();

			return await Task.FromResult(1);
		 }
	}
}
