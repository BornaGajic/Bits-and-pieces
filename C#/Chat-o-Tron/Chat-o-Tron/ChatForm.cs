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
using System.Threading;

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
			byte[] bytes = Encoding.ASCII.GetBytes("post;" + RoomId.ToString() + ';' + inputBox.Text);

			inputBox.Text = "";

			Client.GetStream().Write(bytes, 0, bytes.Length);
		}

		private async void ChatForm_FormClosing (object sender, FormClosingEventArgs e)
		{
			var leave = Encoding.ASCII.GetBytes("leave;" + RoomId.ToString());
			var rfr = Encoding.ASCII.GetBytes("refresh");

			Client.GetStream().Write(leave, 0, leave.Length);

			await Task.Run(() => {
				Thread.Sleep(500);
			});

			Client.GetStream().Write(rfr, 0, rfr.Length);
		}

		public void ShowMessage (string message, bool isMessageMine)
		{
			chatBox.RowCount++;

			SizeF stringSize = new SizeF();
			stringSize = chatBox.CreateGraphics().MeasureString(message, chatBox.Font);
			
			float rowHeight = stringSize.Height;

			if (stringSize.Width > inputBox.Width)
			{
				rowHeight = (stringSize.Width / inputBox.Width) * stringSize.Height;
			}
			
			chatBox.RowStyles.Add(new RowStyle(SizeType.Absolute, rowHeight));
			

			Label newMessage = new Label()
			{ 
				Text = message, 
				Dock = DockStyle.Fill
			};

			if (isMessageMine)
				chatBox.Controls.Add(newMessage, 1, chatBox.RowCount - 1);
			else
				chatBox.Controls.Add(newMessage, 0, chatBox.RowCount - 1);

			ToolTip messageToolTip = new ToolTip();
			messageToolTip.SetToolTip(newMessage, DateTime.Now.ToString());
		}
	}
}
