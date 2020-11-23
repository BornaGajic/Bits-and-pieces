using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using Utility;
using System.Diagnostics;

namespace Chat_o_Tron
{
	public partial class LogInForm : Form
	{
		public LogInForm ()
		{
			InitializeComponent();
		}

		private void AcceptButton_Click (object sender, EventArgs e)
		{
			UdpClient udpClient = new UdpClient();
			IPEndPoint serverEp = new IPEndPoint(IPAddress.Any, 0);

			var data = Encoding.ASCII.GetBytes("ConnectToServer");

			this.Cursor = Cursors.WaitCursor;

			udpClient.EnableBroadcast = true;
			udpClient.Send(data, data.Length, new IPEndPoint(IPAddress.Broadcast, 11000));
			
			var adress = Encoding.ASCII.GetString(udpClient.Receive(ref serverEp));

			udpClient.Close();

			TcpClient tcpClient = new TcpClient(Dns.GetHostEntry(adress).HostName, 7777);

			this.Cursor = Cursors.Default;

			MenuForm childForm = new MenuForm(tcpClient);

			Utility.Utility.username = textBox1.Text;

			this.Hide();
			childForm.ShowDialog();

			tcpClient.GetStream().Close();
			tcpClient.Close();

			this.Close();
		}
	}
}
