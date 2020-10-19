using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TicTacToe
{
	public partial class NewAccount : Form
	{
		public NewAccount ()
		{
			InitializeComponent();
		}

		private void NewAccountAcceptButton_Click (object sender, EventArgs e)
		{
			string username = NewAccountUsernameTB.Text.Trim();
			string password = NewAccountPasswordTB.Text.Trim();

			if (username.Length > 0 && password.Length > 0)
			{
				string query = "insert into dbo.Player values(@newPlayerID, @username, @password, 0, 0)";

				Dictionary<string, object> parameters = new Dictionary<string, object>()
				{
					{"@newPlayerID", Guid.NewGuid()},
					{"@username", username},
					{"@password", password}
				};

				string checkingQuery = "select PlayerID from dbo.Player where Username = @username";

				if (SqlWrapper.ExecuteQuery(checkingQuery, new Dictionary<string, object>{{"@username", username}}).Count > 0)
				{
					ErrorLabel.Text = "Username already taken.";
				}
				else
				{
					SqlWrapper.ExeNonQuery(query, parameters);

					this.Close();				
				}
			}
			else
			{
				ErrorLabel.Text = "Username or Password is empty.";
			}
		}
	}
}
