using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.Model.Common;

namespace Devbazaar.Service.Common.IBusinessCardServices
{
	public interface IBusinessCardService
	{
		Task<int> CreateAsync (IBusinessCard newBusinessCard, List<ICategory> categories, Guid businessId);
		Task<int> UpdateAsync (IBusinessCard updatedBusinessCard);
	}
}
