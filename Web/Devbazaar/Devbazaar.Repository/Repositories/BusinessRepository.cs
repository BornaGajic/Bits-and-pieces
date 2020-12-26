using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Contexts;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.EntityModels;
using Devbazaar.DAL.Context;
using Devbazaar.Repository.Common.Repositories;
using System.Data.Entity;

namespace Devbazaar.Repository.Repositories
{
	public class BusinessRepository : BaseRepository<BusinessEntity>, IBusinessRepository
	{
		public BusinessRepository (DevbazaarDbContext context) : base(context)
		{
		}

		public async Task<BusinessEntity> GetByIdAsync (Guid id)
		{
			return await Entities.FindAsync(id);
		}

		public async Task<IEnumerable<BusinessEntity>> PaginatedGetAsync (int page, int count)
		{
			var businesses = from b in TableAsNoTracking select b;

			if (page == 1)
			{
				businesses.Take(count);
			}
			else 
			{
				businesses.Skip((page - 1) * count).Take(count);
			}

			return await businesses.ToListAsync();
		}
	}
}
