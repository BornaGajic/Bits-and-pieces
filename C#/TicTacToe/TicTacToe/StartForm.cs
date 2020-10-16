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
		private List<Button> Saves = null;

		public StartForm ()
		{
			InitializeComponent();

			Saves = new List<Button> () 
			{
				button1, button2, button3, button4, button5
			};

			foreach (Button b in Saves)
			{
				b.Click += SaveButton_Click;
			}
		}

		private void StartForm_Load (object sender, EventArgs e)
		{
			string query = "select * from dbo.MyUser";

			List<List<object>> users = SqlWrapper.ExecuteQuery(query);

			for (int i = 0; i < users.Count; i++)
			{
				foreach(var element in users[i])
				{
					Console.WriteLine(element.ToString());
				}

				Saves[i].Text = users[i][1].ToString();
			}
		}

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
	}
}
