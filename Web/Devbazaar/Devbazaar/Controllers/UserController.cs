using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using System.Web.Http;
using AutoMapper;
using Devbazaar.Model.Common.IUser;
using Devbazaar.RestModels.UserRest;
using Devbazaar.Service.Common.IUserService;
using Microsoft.AspNet.Identity;
using static Devbazaar.Utility.Utility;

namespace Devbazaar.Controllers
{
    [RoutePrefix("Devbazaar/Login")]
    public class UserController : ApiController
    {
        protected IUserService LoginService { get; set; }
        protected IMapper Mapper { get; set; }

        public UserController (IUserService loginService, IMapper mapper)
        {
             LoginService = loginService;
             Mapper = mapper;
        }

        [AllowAnonymous]
        [HttpPost]
        [Route("x")]
        public async Task<HttpResponseMessage> CreateAsync ([FromBody] CreateUserRest newUser, [FromUri] TypeOfUser tou)
        {
            var user = Mapper.Map<Model.Common.IUser.IUser>(newUser);

            string token;
            try
            {
                token = await LoginService.CreateAsync(user, tou);            
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);

                return new HttpResponseMessage(HttpStatusCode.BadRequest);
            } 

            return Request.CreateResponse(HttpStatusCode.OK, token);
        }
    }
}
