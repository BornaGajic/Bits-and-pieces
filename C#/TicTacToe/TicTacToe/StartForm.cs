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
	public partial class StartForm : Form
	{
		public StartForm ()
		{
			InitializeComponent();
		}

		private void LogInButton_Click (object sender, EventArgs e)
		{
			string username = UsernameTB.Text;
			string password = PasswordTB.Text;

			if (username.Length > 0 && password.Length > 0)
			{
				string query = "select PlayerID, Username, Wins, Loses " +
							   "from dbo.Player " +
							   "where Username = @username and " +
							     	 "Password = @password";

				var props = new Dictionary<string, object>
				{
					{"@username", username},
					{"@password", password}
				};

				List<List<object>> matrixResult = SqlWrapper.ExecuteQuery(query, props);

				if (matrixResult.Count > 0)
				{
					MenuForm menuChild = new MenuForm(matrixResult[0], this);

					menuChild.Show();

					this.Visible = false;
				}
				else
				{
					PasswordTB.Text = "";
					WrongPassLabel.Visible = true;
				}
			}

		}

		private void NewPlayerButton_Click (object sender, EventArgs e)
		{
			NewAccount childForm = new NewAccount();
			childForm.ShowDialog();
		}
	}
		/*
		private void SaveButton_Click (object sender, EventArgs args)
		{
			Button saveSlot = sender as Button;

			if (saveSlot.Text == "New Save")
			{
				NewSaveForm childForm = new NewSaveForm();
				childForm.ShowDialog(); // this form is waiting for childForm to finish its work

				StartForm_Load(this, null);
			}
		}
	}*/
}
