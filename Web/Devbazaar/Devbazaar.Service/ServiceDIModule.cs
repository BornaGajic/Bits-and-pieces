using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Autofac;
using Devbazaar.Service.BusinessCardServices;
using Devbazaar.Service.Common.IBusinessCardServices;

namespace Devbazaar.Service
{
	public class ServiceDIModule : Module
	{
		protected override void Load (ContainerBuilder builder)
		{
			builder.RegisterType<BusinessCardService>().As<IBusinessCardService>();
		}
	}
}
