﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using System.Web.Http;
using AutoMapper;
using Devbazaar.Model.Common;
using Devbazaar.RestModels.ClientRest;
using Devbazaar.Service.Common.IClientServices;
using Microsoft.AspNet.Identity;

namespace Devbazaar.Controllers
{
    [RoutePrefix("Devbazaar/Client")]
    public class ClientController : ApiController
    {
        public IClientService ClientService { get; set; }
        public IMapper Mapper { get; set; }
    
        public ClientController (IClientService clientService, IMapper mapper)
        {
            ClientService = clientService;
            Mapper = mapper;
        }

        [Authorize]
        [HttpPut]
        [Route("Update")]
        public async Task<HttpResponseMessage> UpdateAsync ([FromBody] UpdateClientRest changedClient)
        {
            var updatedClient = new Dictionary<string, object>();
            foreach (var property in typeof(UpdateClientRest).GetProperties())
            {
                var value = property.GetValue(changedClient);
                if (value != null)
                {
                    updatedClient[property.Name] = property.GetValue(changedClient);
                }
            }

            Guid clientId = Guid.Parse(User.Identity.GetUserId());

            try
            {
                await ClientService.UpdateAsync(updatedClient, clientId);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                return new HttpResponseMessage(HttpStatusCode.BadRequest);
            }

            return new HttpResponseMessage(HttpStatusCode.OK);
        }


        /* TO-DO:
         * Method for adding favourite Businesses
         */
    }
}
