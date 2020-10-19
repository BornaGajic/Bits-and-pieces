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
	public partial class MenuForm : Form
	{
		private StartForm parentForm = null;

		public MenuForm (List<object> logedInPlayer, StartForm parent)
		{
			InitializeComponent();

			UsernameLabel.Text = logedInPlayer[1].ToString();

			parentForm = parent;

			this.FormClosing += MenuForm_FormClosing;
		}

		private void MenuForm_FormClosing (object sender, FormClosingEventArgs e)
		{
			parentForm.Close();
		}

		private void LocalButton_Click (object sender, EventArgs e)
		{
			MainForm game = new MainForm(UsernameLabel.Text);

			game.ShowDialog();
		}
	}
}
