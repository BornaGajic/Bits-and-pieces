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
using Utility;

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
			if (inputBox.Text.Length != 0)
			{
				string username = Utility.Utility.username;
				byte[] bytes = Encoding.ASCII.GetBytes("post;" + RoomId.ToString() + ';' + inputBox.Text + ';' + username);

				inputBox.Text = "";

				Client.GetStream().Write(bytes, 0, bytes.Length);
			}
		}

		private async void ChatForm_FormClosing (object sender, FormClosingEventArgs e)
		{
			var leave = Encoding.ASCII.GetBytes("leave;" + RoomId.ToString());
			var rfr = Encoding.ASCII.GetBytes("refresh");

			Client.GetStream().Write(leave, 0, leave.Length);

			await Task.Run(() => {
				Thread.Sleep(500);
			});

			try
			{
				Client.GetStream().Write(rfr, 0, rfr.Length);
			}
			catch
			{
				return; // app closed before refresh.
			}
		}

		public void ShowMessage (string message, bool isMessageMine, string username)
		{
			chatBox.RowCount++;

			Label Username = new Label()
			{
				Text = username,
				Dock = DockStyle.Fill,
				TextAlign = ContentAlignment.MiddleCenter,
			};

			Label newMessage = new Label()
			{ 
				Text = message, 
				Dock = DockStyle.Fill,
				BorderStyle = BorderStyle.FixedSingle,
				TextAlign = ContentAlignment.BottomRight,
				Margin = new Padding(0, 0, 0, 5),
				Padding = new Padding(0, -2, 0, 2)
			};


			float colWidth;
			if (isMessageMine)
			{
				chatBox.ColumnStyles[1].Width += 0.1f * chatBox.ColumnStyles[1].Width;
				colWidth = (chatBox.ColumnStyles[1].Width / 100) * chatBox.Width;
			}
			else
			{
				chatBox.ColumnStyles[0].Width += 0.1f * chatBox.ColumnStyles[0].Width;
				colWidth = (chatBox.ColumnStyles[0].Width / 100) * chatBox.Width;
			}
			
			using (Graphics g = chatBox.CreateGraphics())
			{
				SizeF stringSize = g.MeasureString(message, chatBox.Font, (int)colWidth);

				float rowHeight = Math.Abs(newMessage.Padding.Top) + newMessage.Padding.Bottom + stringSize.Height + (0.25f * (float)Math.Ceiling(stringSize.Height));

				chatBox.RowStyles.Add(new RowStyle(SizeType.Absolute, rowHeight));
			}

			if (isMessageMine)
			{
				chatBox.Controls.Add(newMessage, 2, chatBox.RowCount - 1);
				//chatBox.Controls.Add(Username, 3, chatBox.RowCount - 1);
			}
			else
			{
				chatBox.Controls.Add(newMessage, 1, chatBox.RowCount - 1);
				//chatBox.Controls.Add(Username, 0, chatBox.RowCount - 1);
			}
				

			ToolTip messageToolTip = new ToolTip();
			messageToolTip.SetToolTip(newMessage, DateTime.Now.ToString());

			if (isMessageMine)
				chatBox.ColumnStyles[1].Width -= 0.1f * chatBox.ColumnStyles[1].Width;
			else
				chatBox.ColumnStyles[0].Width -= 0.1f * chatBox.ColumnStyles[0].Width;
		}
	}
}
