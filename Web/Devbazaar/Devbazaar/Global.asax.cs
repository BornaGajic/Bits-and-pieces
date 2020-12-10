using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Web;
using System.Web.Http;
using System.Web.Mvc;
using System.Web.Optimization;
using System.Web.Routing;
using AutoMapper;
using Autofac;
using Autofac.Integration.WebApi;
using Devbazaar.DAL.Context;
using Devbazaar.Repository;
using Devbazaar.Service;
using Devbazaar.AutoMapperProfiles;

namespace Devbazaar
{
	public class WebApiApplication : System.Web.HttpApplication
	{
		protected void Application_Start ()
		{
			GlobalConfiguration.Configure(WebApiConfig.Register);

			var builder = new ContainerBuilder();
			var config = GlobalConfiguration.Configuration;

			builder.RegisterApiControllers(Assembly.GetExecutingAssembly());
			builder.RegisterType<DevbazaarDbContext>().InstancePerLifetimeScope();

			builder.RegisterModule(new RepositoryDIModule());
			builder.RegisterModule(new ServiceDIModule());

			builder.Register(context => new MapperConfiguration(cfg => {
				cfg.AddProfile<BusinessCardProfile>();
			}));

			var container = builder.Build();
			config.DependencyResolver = new AutofacWebApiDependencyResolver(container);
		}
	}
}
