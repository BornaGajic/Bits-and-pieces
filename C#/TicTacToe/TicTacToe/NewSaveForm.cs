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
	public partial class NewSaveForm : Form
	{
		public NewSaveForm ()
		{
			InitializeComponent();
		}

		private void newsaveaccept_Click (object sender, EventArgs e)
		{
			string query = "insert into dbo.MyUser values(@userCount, @username, 0, 0)";

			Dictionary<string, object> parameters = new Dictionary<string, object>()
			{
				{"@userCount", new Random().Next()},
				{"@username", newsavetextbox.Text}
			};

			SqlWrapper.ExeNonQuery(query, parameters);

			this.Close();
		}
	}
}
