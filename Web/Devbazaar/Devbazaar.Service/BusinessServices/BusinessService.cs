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
using Devbazaar.Common.IPageData.Business;
using Devbazaar.Common.IPageData.ClientTask;
using Devbazaar.Common.PageData;
using Devbazaar.Common.PageData.ClientTask;

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

		public async Task<List<IClientTaskReturnType>> AcquiredTasks (ClientTaskPage pageData, Guid businessId)
		{
			return await UnitOfWork.ClientTaskRepository.PaginatedGetAsync(pageData, null, businessId);
		}

		public async Task<List<IBusinessPageReturnType>> PaginatedGetAsync (BusinessPage pageData)
		{
			var businessTable = UnitOfWork.BusinessRepository.Table;
		
			int count = Utility.Utility.PageItemLimit;
			int pageItemCount = Utility.Utility.PageItemLimit;
			
			ApplyPageSeasoning(pageData, businessTable);

			businessTable = pageData.PageNumber == 1 ? businessTable.Take(pageItemCount)
													 : businessTable.Skip((pageData.PageNumber - 1) * pageItemCount).Take(pageItemCount);

			var businessEntityList = await businessTable.ToListAsync();
			var businessReturnTypes = new List<IBusinessPageReturnType>();

			foreach (var business in businessEntityList)
			{
				var user = businessTable.Where(b => b.Id == business.Id).Select(b => b.User);

				business.User = await user.SingleAsync();

				// continue if 'search string' is not empty and current Username does not contain search string.
				if (!string.IsNullOrEmpty(pageData.Username) && !business.User.Username.Contains(pageData.Username))
				{
					continue;
				}

				var categories = businessTable.Where(b => b.Id == business.Id).SelectMany(b => b.Categories);

				business.Categories = await categories.ToListAsync();

				businessReturnTypes.Add(
					new BusinessPageReturnType()
					{
						Description = business.Description,
						About = business.About,
						Available = business.Available,
						Categories = Mapper.Map<List<ICategory>>(business.Categories),
						City = business.City,
						Country = business.Country,
						Email = business.User.Email,
						Username = business.User.Username,
						Website = business.Website, 
						Logo = business.Logo
					}
				);
			}

			return businessReturnTypes;
		}

		private void ApplyPageSeasoning (BusinessPage pageData, IQueryable<BusinessEntity> businessTable)
		{
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
			else
			{
				businessTable = businessTable.OrderByDescending(p => p.User.Username);
			}	
		}
	}
}
