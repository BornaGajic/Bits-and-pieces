using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using System.Web.Http;
using AutoMapper;
using Devbazaar.Model.Common;
using Devbazaar.RestModels.ClientTaskRest;
using Devbazaar.Service.Common.IClientTaskServices;
using Microsoft.AspNet.Identity;

namespace Devbazaar.Controllers
{
	[RoutePrefix("Devbazaar/Task")]
    public class ClientTaskController : ApiController
    {
        private IClientTaskService ClientTaskService { get; set; }
        private IMapper Mapper { get; set; }

        public ClientTaskController (IMapper mapper, IClientTaskService clientTaskService)
        {
            Mapper = mapper;
            ClientTaskService = clientTaskService;
        }

        [Authorize]
        [Route("Create")]
        [HttpPost]
        public async Task<HttpResponseMessage> CreateAsync ([FromBody] CreateClientTaskRest newTask)
        {
            var newClientTask = Mapper.Map<IClientTask>(newTask);

            if (await ClientTaskService.CreateAsync(newClientTask))
            {
                return Request.CreateResponse(HttpStatusCode.OK);    
            }
            else
            {
                return Request.CreateResponse(HttpStatusCode.BadRequest);
            }
        }

        [Authorize]
        [Route("Update")]
        [HttpPut]
        public async Task<HttpResponseMessage> UpdateAsync ([FromBody] UpdateClientTaskRest newTask)
        {
            var updatedClientTask = Mapper.Map<IClientTask>(newTask);

            if (await ClientTaskService.UpdateAsync(updatedClientTask))
            {
                return Request.CreateResponse(HttpStatusCode.OK);    
            }
            else
            {
                return Request.CreateResponse(HttpStatusCode.BadRequest);
            }
        }

        [Authorize]
        [Route("Delete")]
        [HttpDelete]
        public async Task<HttpResponseMessage> DeleteAsync ([FromBody] DeleteClientTaskRest task)
        {
            if (await ClientTaskService.DeleteAsync(task.Id))
            {
                return Request.CreateResponse(HttpStatusCode.OK);    
            }
            else
            {
                return Request.CreateResponse(HttpStatusCode.BadRequest);
            }
        }
    }
}
