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

namespace Chat_o_Tron
{
	public partial class ChatForm : Form
	{
		private TcpClient Client {get; set;}
		private Guid RoomId {get; set;}
		
		public ChatForm (TcpClient client, Guid roomId)
		{
			InitializeComponent();

			Client = client;
			RoomId = roomId;
		}

		private void SendButton_Click (object sender, EventArgs e)
		{
			byte[] bytes = Encoding.ASCII.GetBytes("post;" + RoomId.ToString() + ';' + textBox1.Text);

			Client.GetStream().Write(bytes, 0, bytes.Length);
		}

		private void ChatForm_FormClosing (object sender, FormClosingEventArgs e)
		{
			var leave = Encoding.ASCII.GetBytes("leave;" + RoomId.ToString());
			Client.GetStream().Write(leave, 0, leave.Length);
		}

		public void ShowMessage (string message)
		{
			ResponseLabel.Text = message;
		}
	}
}
