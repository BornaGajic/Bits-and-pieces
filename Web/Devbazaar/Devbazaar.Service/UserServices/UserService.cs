﻿using System;
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
using Microsoft.IdentityModel.Tokens;
using System.Security.Claims;
using static Devbazaar.Utility.Utility;
using System.Security.Cryptography;
using Devbazaar.Service.Common.IUserServices;
using System.Data.Entity;

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

		// creates new user, by default it creates new Business, else it creates Client
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

				return await Task.Run(() => { return GenerateToken(user, tou); });
			}
			else
			{
				return "User already exists";
			}
		}

		// returns token if User exists, else returns empty string
		public async Task<string> LoginAsync (IUser user)
		{
			Guid userId = await UnitOfWork.UserRepository.CheckExistence(user.Email, EncodePassword(user.Password));
			TypeOfUser role = TypeOfUser.Business;

			if (userId == Guid.Empty)
			{
				return string.Empty;
			}
			else if (await UnitOfWork.BusinessRepository.GetByIdAsync(userId) == null)
			{
				role = TypeOfUser.Client;
			}

			user.Id = userId;

			return GenerateToken(user, role);
		}

		public async Task<int> UpdateAsync (Dictionary<string, object> item, Guid userId)
		{
			var entity = await (from u in UnitOfWork.UserRepository.TableAsNoTracking where u.Id == userId select u).SingleAsync();	

			foreach (var prop in typeof(BusinessEntity).GetProperties())
			{
				if (item.ContainsKey(prop.Name))
				{
					prop.SetValue(entity, item[prop.Name]);
				}
			}
			
			try
			{
				await UnitOfWork.UpdateAsync<UserEntity>(entity);

				await UnitOfWork.CommitAsync<UserEntity>();
			}
			catch (Exception e)
			{
				Console.WriteLine(e.Message);

				return await Task.FromResult(0);
			}
			
			return await Task.FromResult(1);
		}

		public async Task<bool> DeleteAsync (IUser user)
		{
			var userEntity = Mapper.Map<UserEntity>(user);

			await UnitOfWork.DeleteAsync(userEntity);

			await UnitOfWork.CommitAsync<UserEntity>();

			return true;
		}

		private static string GenerateToken (IUser user, TypeOfUser role, int expireMinutes = 30)
		{
			var SecurityKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(ConfigurationManager.AppSettings["SecretKey"]));
			var credentials = new SigningCredentials(SecurityKey, SecurityAlgorithms.HmacSha256);

			List<Claim> claims = new List<Claim>()
			{
				new Claim(JwtRegisteredClaimNames.Jti, user.Id.ToString()),
				new Claim(ClaimTypes.NameIdentifier, user.Id.ToString()),
				new Claim(ClaimTypes.Email, user.Email.ToString()),
				new Claim(ClaimTypes.Role, role.ToString())
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
