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
using System.Threading;
using System.Net.Http.Headers;

namespace Chat_o_Tron
{
	public partial class MenuForm : Form
	{
		private string Username { get; set; }
		private TcpClient Client { get; set; }

		private Dictionary<Guid, ChatForm> activeChatRooms = new Dictionary<Guid, ChatForm>();
		
		public MenuForm (string username, TcpClient client)
		{
			InitializeComponent();

			Username = username;
			Client = client;

			button1.Visible = false;
			button2.Visible = false;
			button3.Visible = false;

			RefreshButton.Click += RefreshRooms;
		}

		private async void CreateRoomButton_Click (object sender, EventArgs e)
		{
			byte[] data = Encoding.ASCII.GetBytes("newroom");

			await Client.GetStream().WriteAsync(data, 0, data.Length);
		}

		private async void RefreshRooms (object sender, EventArgs e)
		{
			byte[] refreshCommand = Encoding.ASCII.GetBytes("refresh");

			await Client.GetStream().WriteAsync(refreshCommand, 0, refreshCommand.Length);
		}

		private async void EnterRoom (object sender, EventArgs e)
		{
			Guid roomId = Guid.Parse((sender as Button).Tag.ToString());

			var data = Encoding.ASCII.GetBytes("join;" + roomId.ToString());

			await Client.GetStream().WriteAsync(data, 0, data.Length);

			activeChatRooms[roomId].Show();
		}

		private void ClientReciever ()
		{	
			byte[] serverData = new byte[1024];
			string[] payload = null;
			Task<int> reciever = null;

			while (this.Visible == true)
			{
				if (reciever == null)
				{
					reciever = Client.GetStream().ReadAsync(serverData, 0, serverData.Length);
				}

				if (reciever.IsCompleted)
				{
					payload = Encoding.ASCII.GetString(serverData, 0, reciever.Result).Split(';');

					switch(payload[0])
						{
							case "leave":
								activeChatRooms.Remove(Guid.Parse(payload[1]));
								break;
							case "post":
								this.Invoke(new Action<string>(activeChatRooms[Guid.Parse(payload[1])].ShowMessage), payload[2]);
								break;
							case "refresh":
								if (payload[1] != "None" && button1.Visible == false)
								{
									var str = payload[1].Split('|')[0];
									Guid roomid = Guid.Parse(payload[1].Split('|')[1]);

									var func = new Action<string, bool, Guid>(this.ShowRoomList);
									this.Invoke(func, str, true, roomid);
								}
								break;
							case "newroom":
								Guid roomId = Guid.Parse(payload[1]);

								activeChatRooms[roomId] = new ChatForm(Client, roomId);
								this.Invoke(new MethodInvoker(activeChatRooms[roomId].Show));
								
								break;
						}

					reciever = null;
				}
			}
		}

		private void ShowRoomList (string text, bool visibility, Guid roomid)
		{
			button1.Text = text;
			button1.Visible = visibility;
			button1.Tag = roomid;

			button1.Click += EnterRoom;	
		}

		private void MenuForm_Shown (object sender, EventArgs e)
		{
			Thread recieverThread = new Thread(new ThreadStart(ClientReciever));
			recieverThread.Start();
		}
	}
}
