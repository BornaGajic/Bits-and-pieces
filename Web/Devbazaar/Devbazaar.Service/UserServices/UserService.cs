using System;
using System.Collections.Generic;
using System.Configuration;
using System.IdentityModel.Tokens.Jwt;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AutoMapper;
using Devbazaar.DAL.EntityModels;
using Devbazaar.Model.Common.IUser;
using Devbazaar.Repository.Common;
using Devbazaar.Service.Common.IUserService;
using Microsoft.IdentityModel.Tokens;
using System.Security.Claims;
using static Devbazaar.Utility.Utility;

namespace Devbazaar.Service.UserServices
{
	public class UserService : IUserService
	{
		protected IUnitOfWork UnitOfWork { get; set; }
		protected IMapper Mapper { get; set; }

		public UserService (IUnitOfWork unitOfWork, IMapper mapper)
		{
			UnitOfWork = unitOfWork;
			Mapper = mapper;
		}

		public static string GenerateToken (Guid userId, int expireMinutes = 30)
		{
			var SecurityKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(ConfigurationManager.AppSettings["SecretKey"]));
			var credentials = new SigningCredentials(SecurityKey, SecurityAlgorithms.HmacSha256);

			List<Claim> claims = new List<Claim>()
			{
				new Claim(JwtRegisteredClaimNames.Jti, userId.ToString()),
				new Claim(ClaimTypes.NameIdentifier, userId.ToString())
			};

			string issuer = "https://localhost:44356";

			var token = new JwtSecurityToken(issuer, issuer, claims, expires: DateTime.Now.AddDays(1), signingCredentials: credentials);

			return new JwtSecurityTokenHandler().WriteToken(token);
		}

		public async Task<string> CreateAsync (IUser user, TypeOfUser tou)
		{
			user.Id = Guid.NewGuid();
			var userEntity = Mapper.Map<UserEntity>(user);

			await UnitOfWork.AddAsync(userEntity);

			switch (tou)
			{
				case TypeOfUser.Business:
					await UnitOfWork.AddAsync(new BusinessEntity() { Id = user.Id });
					await UnitOfWork.CommitAsync<BusinessEntity>();
					break;
				case TypeOfUser.Client:
					await UnitOfWork.AddAsync(new ClientEntity() { Id = user.Id });
					await UnitOfWork.CommitAsync<ClientEntity>();
					break;
			}

			await UnitOfWork.CommitAsync<UserEntity>();

			return await Task.Run(() => { return GenerateToken(user.Id); });
		}
	}
}
