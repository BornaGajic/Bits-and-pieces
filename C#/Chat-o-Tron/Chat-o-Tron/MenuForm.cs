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

			RefreshButton.Click += RefreshRooms;
		}

		private async void CreateRoomButton_Click (object sender, EventArgs e)
		{
			byte[] data = Encoding.ASCII.GetBytes("newroom");

			await Client.GetStream().WriteAsync(data, 0, data.Length);

			await Task.Run(() => {
				Thread.Sleep(500);
			});

			RefreshRooms(null, null);
		}

		private async void RefreshRooms (object sender, EventArgs e)
		{
			byte[] refreshCommand = Encoding.ASCII.GetBytes("refresh");

			await Client.GetStream().WriteAsync(refreshCommand, 0, refreshCommand.Length);
		}

		private async void JoinRoom (string roomId, string roomName)
		{
			Guid id = Guid.Parse(roomId);

			var data = Encoding.ASCII.GetBytes("join;" + id.ToString());

			await Client.GetStream().WriteAsync(data, 0, data.Length);

			activeChatRooms[id] = new ChatForm(Client, id);
			activeChatRooms[id].Text = roomName;
			activeChatRooms[id].Show();

			RefreshRooms(null, null);
		}

		private async void ClientReciever ()
		{	
			// payload: 0 - keyword, 1 - id/None, 2 - message

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
					int byteCount = await reciever;
					payload = Encoding.ASCII.GetString(serverData, 0, byteCount).Split(';');

					switch(payload[0])
						{
							case "leave":
								activeChatRooms.Remove(Guid.Parse(payload[1]));
								break;
							case "post":
								ChatForm room = activeChatRooms[Guid.Parse(payload[1])];
								this.Invoke(new Action<string>(room.ShowMessage), payload[2]);
								break;
							case "refresh":
								if (payload[1] != "None")
								{
									var func = new Action<string[]>(this.ShowRoomList);
									this.Invoke(func, (object)payload); // array covariance
								}
								break;
							case "newroom":
								Guid roomId = Guid.Parse(payload[1]);

								activeChatRooms[roomId] = new ChatForm(Client, roomId);
								this.Invoke(new MethodInvoker(activeChatRooms[roomId].Show));

								break;
							default: // update num of participants for a room
								UpdateNumOfParticipants(payload[0], payload[1]);
								break;
						}

					reciever = null;
				}
			}
		}

		private void UpdateNumOfParticipants (string newNumber, string roomId)
		{
			string roomName = activeChatRooms[Guid.Parse(roomId)].Text;

			foreach (ListViewItem item in RoomList.Items)
			{
				if (item.Text == roomName)
				{
					item.SubItems[1].Text = newNumber;
					break;
				}
			}
		}

		private void ShowRoomList (string[] rooms)
		{
			bool contains = false;

			foreach (string room in rooms)
			{
				if (room == "refresh" || room == "None") continue;

				string[] props = room.Split('|');
				string roomName = props[0];
				string roomId = props[1];
				string numOfParticipants = props[2];

				foreach (ListViewItem item in RoomList.Items)
				{
					if (item.Text == roomName)
					{	
						contains = true;
						item.SubItems[1].Text = numOfParticipants;
						break;
					}
				}

				if (!contains)
				{
					var listItem = new ListViewItem(new string[] { roomName,  numOfParticipants})
					{
						Font = new Font("Arial", 12),
						Tag = roomId
					};

					RoomList.Items.Add(listItem);
				}

				contains = false;
			}
		}

		private void MenuForm_Shown (object sender, EventArgs e)
		{
			Thread recieverThread = new Thread(new ThreadStart(ClientReciever));
			recieverThread.Start();

			RefreshRooms(null, null);
		}

		private void RoomList_DoubleClick (object sender, EventArgs e)
		{
			string roomId = RoomList.SelectedItems[0].Tag.ToString();
			string roomName = RoomList.SelectedItems[0].Text.ToString();

			JoinRoom(roomId, roomName);
		}
	}
}
