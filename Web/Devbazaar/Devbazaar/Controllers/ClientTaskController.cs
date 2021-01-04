using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using System.Web.Http;
using AutoMapper;
using Devbazaar.Model.Common;
using Devbazaar.RestModels.UserTaskRest;
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
        public async Task<HttpResponseMessage> CreateAsync ([FromBody] CreateUserTaskRest newTask)
        {
            throw new NotImplementedException();
        }

        [Authorize]
        [Route("Update")]
        [HttpPut]
        public async Task<HttpResponseMessage> UpdateAsync ([FromBody] CreateUserTaskRest newTask)
        {
            throw new NotImplementedException();
        }

        [Authorize]
        [Route("Delete")]
        [HttpDelete]
        public async Task<HttpResponseMessage> DeleteAsync ([FromBody] CreateUserTaskRest newTask)
        {
            throw new NotImplementedException();
        }
    }
}
