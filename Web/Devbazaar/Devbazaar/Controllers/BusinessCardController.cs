using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using System.Web.Http;
using AutoMapper;
using Devbazaar.Model.Common;
using Devbazaar.RestModels.BusinessCardRest;
using Devbazaar.Service.Common.IBusinessCardServices;

namespace Devbazaar.Controllers
{
    [RoutePrefix("Devbazaar/BusinessCard")]
    public class BusinessCardController : ApiController
    {
        IBusinessCardService BusinessCardService { get; set; }
        IMapper Mapper { get; set; }

        public BusinessCardController (IBusinessCardService businessCardService, IMapper mapper)
        {
            BusinessCardService = businessCardService;
            Mapper = mapper;
        }

       [HttpPost]
       [Route("Create")]
       public async Task<HttpResponseMessage> CreateAsync ([FromBody] CreateBusinessCardRest createBusinessCardRest)
       {
            var businessCard = Mapper.Map<IBusinessCard>(createBusinessCardRest);
            var categories = createBusinessCardRest.Categories;
            var businessId = createBusinessCardRest.BusinessId;

            try
            {
                await BusinessCardService.CreateAsync(businessCard, categories, businessId);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                return new HttpResponseMessage(HttpStatusCode.BadRequest);
            }

            return new HttpResponseMessage(HttpStatusCode.OK);
       }

       [HttpPut]
       [Route("Update")]
       public async Task<HttpResponseMessage> UpdateAsync ([FromBody] UpdateBusinessCardRest updateBusinessCardRest)
       {
            var businessCard = Mapper.Map<IBusinessCard>(updateBusinessCardRest);

            try
            {
                await BusinessCardService.UpdateAsync(businessCard);
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
