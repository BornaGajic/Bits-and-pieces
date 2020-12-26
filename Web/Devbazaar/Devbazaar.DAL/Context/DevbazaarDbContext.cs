﻿using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Devbazaar.DAL.EntityModels;
using System.ComponentModel.DataAnnotations.Schema;

namespace Devbazaar.DAL.Context
{
	public class DevbazaarDbContext : DbContext
	{
		public DbSet<BusinessEntity> Businesses { get; set; }
		public DbSet<CategoryEntity> Categories { get; set; }
		public DbSet<ClientEntity> Clients { get; set; }
		public DbSet<TaskEntity> Tasks { get; set; }

		public DevbazaarDbContext () : base("name=DevbazaarDBConnectionString")
		{
		}

		protected override void OnModelCreating (DbModelBuilder modelBuilder)
		{
			base.OnModelCreating(modelBuilder);

			modelBuilder.Entity<BusinessEntity>().ToTable("Businesses").HasKey(b => b.Id).Property(p => p.Id).IsRequired().HasDatabaseGeneratedOption(DatabaseGeneratedOption.None);
			modelBuilder.Entity<BusinessEntity>().Property(p => p.About).IsOptional().HasMaxLength(300);
			modelBuilder.Entity<BusinessEntity>().Property(p => p.Website).IsOptional().HasMaxLength(2083);
			modelBuilder.Entity<BusinessEntity>().Property(p => p.Description).IsRequired();
			modelBuilder.Entity<BusinessEntity>().Property(p => p.Available).IsRequired();
			modelBuilder.Entity<BusinessEntity>().Property(p => p.City).IsRequired().HasMaxLength(50);
			modelBuilder.Entity<BusinessEntity>().Property(p => p.Country).IsRequired().HasMaxLength(50);
			modelBuilder.Entity<BusinessEntity>().HasMany<CategoryEntity>(b => b.Categories).WithMany(c => c.Businesses).Map(bc => {
				bc.MapLeftKey("BusinessRefId");
				bc.MapRightKey("CategoryRefId");
				bc.ToTable("BusinessCategory");
			});

			modelBuilder.Entity<CategoryEntity>().ToTable("Categories");
			modelBuilder.Entity<CategoryEntity>().HasKey(p => p.Id).Property(p => p.Id).IsRequired().HasDatabaseGeneratedOption(DatabaseGeneratedOption.None);
			modelBuilder.Entity<CategoryEntity>().Property(p => p.Name).IsRequired().HasMaxLength(50);
			modelBuilder.Entity<CategoryEntity>().HasMany<TaskEntity>(c => c.Tasks).WithMany(t => t.Categories).Map(ct => {
				ct.MapLeftKey("CategoryRefId");
				ct.MapRightKey("TaskRefId");
				ct.ToTable("CategoryTask");
			});

			modelBuilder.Entity<ClientEntity>().ToTable("Clients");
			modelBuilder.Entity<ClientEntity>().HasKey(p => p.Id).Property(p => p.Id).IsRequired().HasDatabaseGeneratedOption(DatabaseGeneratedOption.None);

			modelBuilder.Entity<TaskEntity>().ToTable("Tasks");
			modelBuilder.Entity<TaskEntity>().HasKey(p => p.Id).Property(p => p.Id).IsRequired().HasDatabaseGeneratedOption(DatabaseGeneratedOption.None);
			modelBuilder.Entity<TaskEntity>().Property(p => p.Description).IsRequired();
			modelBuilder.Entity<TaskEntity>().Property(p => p.LowPrice).IsOptional();
			modelBuilder.Entity<TaskEntity>().Property(p => p.HighPrice).IsOptional();
			modelBuilder.Entity<TaskEntity>().HasRequired<ClientEntity>(t => t.Client).WithMany(c => c.Tasks).HasForeignKey<Guid>(t => t.ClientId);
			modelBuilder.Entity<TaskEntity>().HasOptional<BusinessEntity>(t => t.Business).WithMany(b => b.Tasks).HasForeignKey<Guid?>(t => t.BusinessId);

			modelBuilder.Entity<UserEntity>().ToTable("Users").HasKey(p => p.Id);
			modelBuilder.Entity<UserEntity>().Property(p => p.Username).IsRequired().HasMaxLength(50);
			modelBuilder.Entity<UserEntity>().Property(p => p.Password).IsRequired();
			modelBuilder.Entity<UserEntity>().Property(p => p.Email).IsRequired().HasMaxLength(50);
			modelBuilder.Entity<UserEntity>().HasOptional(u => u.Client).WithRequired(uc => uc.User).WillCascadeOnDelete();
			modelBuilder.Entity<UserEntity>().HasOptional(u => u.Business).WithRequired(uc => uc.User).WillCascadeOnDelete();
		}
	}
}
