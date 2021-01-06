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
using System.Data.Entity;
using Devbazaar.Common.PageData.Business;

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

			if (categories.Count != 0)
			{
				var categoryEntified = Mapper.Map<ICollection<CategoryEntity>>(categories);

				foreach (var category in categoryEntified)
				{
					category.Id = await UnitOfWork.CategoryRepository.GetIdByName(category.Name);

					await UnitOfWork.CategoryRepository.AttachAsync(category);	
				}
			
				businessEntity.Categories = categoryEntified;
			}
			
			try
			{
				await UnitOfWork.AddAsync<BusinessEntity>(businessEntity);

				await UnitOfWork.CommitAsync<BusinessEntity>();

				return await Task.FromResult(1); 
			}
			catch (Exception e)
			{
				Console.WriteLine(e.Message);

				return await Task.FromResult(0);
			}
		}

		public async Task<int> UpdateAsync (Dictionary<string, object> item, Guid businessId)
		{
			var entity = await (from business in UnitOfWork.BusinessRepository.TableAsNoTracking where business.Id == businessId select business).SingleAsync();

			foreach (var prop in typeof(BusinessEntity).GetProperties())
			{
				if (item.ContainsKey(prop.Name))
				{
					prop.SetValue(entity, item[prop.Name]);
				}
			}
			
			await UnitOfWork.UpdateAsync<BusinessEntity>(entity);
			await UnitOfWork.CommitAsync<BusinessEntity>();

			return await Task.FromResult(1);
		}

		public async Task<List<IBusiness>> PaginatedGetAsync (BusinessPage pageData, Guid? userId = null)
		{
			var businessTable = UnitOfWork.BusinessRepository.Table;	
		
			int count = Utility.Utility.PageItemLimit;
			
			if (userId != null)
			{
				businessTable = from business in businessTable where business.Id == userId select business;
			}
			
			// filter
			if (pageData.Availability.HasValue)
			{
				businessTable = from business in businessTable where business.Available == pageData.Availability select business;
			}
			if (!string.IsNullOrEmpty(pageData.City)) 
			{
				businessTable = from business in businessTable where business.City == pageData.City select business;
			}
			if (!string.IsNullOrEmpty(pageData.Country)) 
			{
				businessTable = from business in businessTable where business.City == pageData.Country select business;
			}
				
			// sort
			if (pageData.NameAsc.HasValue)
			{
				businessTable = pageData.NameAsc.Value ? businessTable.OrderBy(p => p.User.Username)
													   : businessTable.OrderByDescending(p => p.User.Username);
			}

			if (pageData.PageNumber == 1)
			{
				businessTable = businessTable.Take(count);
			}
			else 
			{
				businessTable = businessTable.Skip((pageData.PageNumber - 1) * count).Take(count);
			}
			
			var businessEntityList = await businessTable.ToListAsync();

			foreach (var business in businessEntityList)
			{
				var categories = businessTable.Where(b => b.Id == business.Id).SelectMany(b => b.Categories);

				business.Categories = await categories.ToListAsync();

				var user = businessTable.Where(b => b.Id == business.Id).Select(b => b.User);

				business.User = (await (user).ToListAsync()).First();
			}

			return Mapper.Map<List<IBusiness>>(businessEntityList);
		}
	}
}
