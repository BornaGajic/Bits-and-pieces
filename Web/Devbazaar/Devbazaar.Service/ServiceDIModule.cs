using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Autofac;
using Devbazaar.Service.BusinessCardServices;
using Devbazaar.Service.Common.IBusinessCardServices;
using Devbazaar.Service.Common.IUserService;
using AutoMapper;
using Devbazaar.Service.UserServices;

namespace Devbazaar.Service
{
	public class ServiceDIModule : Module
	{
		protected override void Load (ContainerBuilder builder)
		{
			builder.RegisterType<BusinessCardService>().As<IBusinessCardService>();
			builder.RegisterType<UserService>().As<IUserService>();
		}
	}
}
