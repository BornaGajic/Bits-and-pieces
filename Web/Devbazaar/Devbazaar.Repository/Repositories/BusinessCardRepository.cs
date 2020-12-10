using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Contexts;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.EntityModels;
using Devbazaar.DAL.Context;
using Devbazaar.Repository.Common.Repositories;

namespace Devbazaar.Repository.Repositories
{
	public class BusinessCardRepository : BaseRepository<BusinessCardEntity>, IBusinessCardRepository
	{
		public BusinessCardRepository (DevbazaarDbContext context) : base(context)
		{
		}
	}
}
