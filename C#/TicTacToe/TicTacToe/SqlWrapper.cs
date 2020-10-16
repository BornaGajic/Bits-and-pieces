using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;

namespace TicTacToe
{
	public static class SqlWrapper
	{
		public static List<List<object>> ExecuteQuery (string query, Dictionary<string, object> parameters = null)
		{
			string connectionString = "Data Source=BORNA-PC\\SQLEXPRESS;Initial Catalog=TickTackToe;Integrated Security=True";
			var result = new List<List<object>>();

			using (SqlConnection connection = new SqlConnection(connectionString))
			{
				try
				{
					connection.Open();
				}	
				catch (Exception e)
				{
					Console.WriteLine(e.Message);
				}

				SqlCommand command = new SqlCommand(query, connection);

				if (parameters != null)
				{
					foreach (var parameter in parameters)
					{
						var parameterValue = parameter.Value == null ? DBNull.Value : parameter.Value;

						command.Parameters.AddWithValue(parameter.Key, parameterValue);	
					}
				}

				SqlDataReader reader = null;

				try
				{
					reader = command.ExecuteReader();
				}
				catch (Exception e)
				{
					Console.WriteLine(e.Message);
				}

				while (reader.Read())
				{
					List<object> row = new List<object>();
					foreach (int i in Enumerable.Range(0, reader.FieldCount))
                    {
                        row.Add(reader[i]);
                    }

                    result.Add(row);
				}

				try
				{
					connection.Close();
				}
				catch (Exception e)
				{
					Console.WriteLine(e.ToString());
				}

				return result;
			}
		}

		public static bool ExeNonQuery (string query, Dictionary<string, object> parameters)
        {
			string connectionString = "Data Source=BORNA-PC\\SQLEXPRESS;Initial Catalog=TickTackToe;Integrated Security=True";
            using (var connection = new SqlConnection(connectionString))
            {
                try
				{
					connection.Open();
				}	
				catch (Exception e)
				{
					Console.WriteLine(e.ToString());
				}

                try
                {
                    var command = new SqlCommand(query, connection);
                
                    foreach (var param in parameters)
                    {
                        var parameterValue = param.Value == null ? DBNull.Value : param.Value;

                        command.Parameters.AddWithValue(param.Key, parameterValue);
                    }

					command.ExecuteNonQuery();
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());  
                }

				try
				{
					connection.Close();
				}
				catch (Exception e)
				{
					Console.WriteLine(e.ToString());
				}
            }

            return true;
        }
	}
}
