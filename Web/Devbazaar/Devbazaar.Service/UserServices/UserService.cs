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
using System.Security.Cryptography;

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

		public async Task<string> CreateAsync (IUser user, TypeOfUser tou)
		{
			if (await UnitOfWork.UserRepository.CheckExistence(user.Email, user.Username) == Guid.Empty)
			{
				user.Id = Guid.NewGuid();
				user.Password = EncodePassword(user.Password);

				var userEntity = Mapper.Map<UserEntity>(user);

				await UnitOfWork.AddAsync(userEntity);

				if (tou == TypeOfUser.Client)
				{
					await UnitOfWork.AddAsync<ClientEntity>(new ClientEntity(){ Id = userEntity.Id });
					await UnitOfWork.CommitAsync<ClientEntity>();
				}

				await UnitOfWork.CommitAsync<UserEntity>();

				return await Task.Run(() => { return GenerateToken(user); });
			}
			else
			{
				return "User already exists";
			}
		}

		public async Task<string> LoginAsync (IUser user)
		{
			Guid userId = await UnitOfWork.UserRepository.CheckExistence(user.Email, EncodePassword(user.Password));

			return userId == Guid.Empty ? string.Empty : GenerateToken(user);
		}

		public async Task<string> UpdateAsync (IUser user)
		{
			var userEntity = Mapper.Map<UserEntity>(user);

			try
			{
				await UnitOfWork.UpdateAsync<UserEntity>(userEntity);

				await UnitOfWork.CommitAsync<UserEntity>();
			}
			catch (Exception e)
			{
				Console.WriteLine(e.Message);

				return string.Empty;
			}
			
			return await Task.Run(() => { return GenerateToken(user); });
		}

		public async Task<bool> DeleteAsync (IUser user)
		{
			var userEntity = Mapper.Map<UserEntity>(user);

			await UnitOfWork.DeleteAsync(userEntity);

			await UnitOfWork.CommitAsync<UserEntity>();

			return true;
		}

		private static string GenerateToken (IUser user, int expireMinutes = 30)
		{
			var SecurityKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(ConfigurationManager.AppSettings["SecretKey"]));
			var credentials = new SigningCredentials(SecurityKey, SecurityAlgorithms.HmacSha256);

			List<Claim> claims = new List<Claim>()
			{
				new Claim(JwtRegisteredClaimNames.Jti, user.Id.ToString()),
				new Claim(ClaimTypes.NameIdentifier, user.Id.ToString()),
				new Claim(ClaimTypes.Email, user.Email.ToString()),
			};

			string issuer = ConfigurationManager.AppSettings["issuer"];

			var token = new JwtSecurityToken(issuer, issuer, claims, expires: DateTime.Now.AddDays(1), signingCredentials: credentials);

			return new JwtSecurityTokenHandler().WriteToken(token);
		}

		private static string EncodePassword (string password)
		{
			string encodedPassword = Encoding.UTF8.GetString(new SHA256Managed().ComputeHash(Encoding.UTF8.GetBytes(password)));
			string encoded = string.Empty;

			foreach (byte b in encodedPassword)
            {
                encoded += String.Format("{0:x2}", b);
            }

			return encoded;
		}
	}
}
