using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Service.Common.IBusinessServices;
using Devbazaar.Repository.Common;
using Devbazaar.Model.Common;
using AutoMapper;
using Devbazaar.DAL.EntityModels;


namespace Devbazaar.Service.BusinessServices
{
	public class BusinessService : IBusinessService
	{
		public IUnitOfWork UnitOfWork { get; set; }
		public IMapper Mapper { get; set; }

		public BusinessService (IUnitOfWork unitOfWork, IMapper mapper)
		{
			UnitOfWork = unitOfWork;
			Mapper = mapper;
		}

		public async Task<int> CreateAsync (IBusiness newBusiness, List<ICategory> categories, Guid userId)
		{
			var businessEntity = Mapper.Map<BusinessEntity>(newBusiness);
			businessEntity.Id = userId;

			var categoryEntified = Mapper.Map<ICollection<CategoryEntity>>(categories);

			foreach (var category in categoryEntified)
			{
				category.Id = await UnitOfWork.CategoryRepository.GetIdByName(category.Name);

				await UnitOfWork.CategoryRepository.AttachAsync(category);	
			}
			
			businessEntity.Categories = categoryEntified;

			await UnitOfWork.AddAsync<BusinessEntity>(businessEntity);

			await UnitOfWork.CommitAsync<BusinessEntity>();

			return await Task.FromResult(1); 
		}

		public async Task<int> UpdateAsync (IBusiness updatedBusiness)
		{
			var entity = Mapper.Map<BusinessEntity>(updatedBusiness);

			await UnitOfWork.UpdateAsync<BusinessEntity>(entity);
			
			await UnitOfWork.CommitAsync<BusinessEntity>();

			return await Task.FromResult(1);
		}
	}
}
