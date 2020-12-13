﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using System.Web.Http;
using AutoMapper;
using Devbazaar.Model.Common;
using Devbazaar.RestModels.BusinessRest;
using Devbazaar.Service.Common.IBusinessServices;
using Microsoft.AspNet.Identity;

namespace Devbazaar.Controllers
{
    [RoutePrefix("Devbazaar/Business")]
    public class BusinessController : ApiController
    {
        IBusinessService BusinessService { get; set; }
        IMapper Mapper { get; set; }

        public BusinessController (IBusinessService businessService, IMapper mapper)
        {
            BusinessService = businessService;
            Mapper = mapper;
        }

        [Authorize]
        [HttpPost]
        [Route("Create")]
        public async Task<HttpResponseMessage> CreateAsync ([FromBody] CreateBusinessRest createBusinessRest)
        {
            var business = Mapper.Map<IBusiness>(createBusinessRest);

            List<ICategory> categories = Mapper.Map<List<ICategory>>(createBusinessRest.Categories);

            try
            {
                await BusinessService.CreateAsync(business, categories, Guid.Parse(User.Identity.GetUserId()));
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                return new HttpResponseMessage(HttpStatusCode.BadRequest);
            }

            return new HttpResponseMessage(HttpStatusCode.OK);
        }

        [Authorize]
        [HttpPut]
        [Route("Update")]
        public async Task<HttpResponseMessage> UpdateAsync ([FromBody] UpdateBusinessRest updateBusinessRest)
        {
            var businessCard = Mapper.Map<IBusiness>(updateBusinessRest);

            try
            {
                await BusinessService.UpdateAsync(businessCard);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                return new HttpResponseMessage(HttpStatusCode.BadRequest);
            }

            return new HttpResponseMessage(HttpStatusCode.OK);
        }
    }
}
