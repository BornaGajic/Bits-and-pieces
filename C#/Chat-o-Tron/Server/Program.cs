using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using Utility;
using System.Runtime.CompilerServices;
using System.Net.NetworkInformation;
using System.Net.Configuration;
using System.Runtime.InteropServices;

namespace ChatServer
{
	class Program
	{
		private static Dictionary<Guid, List<TcpClient>> RoomClients = new Dictionary<Guid, List<TcpClient>>();
		private static List<TcpClient> ConnectedClients = new List<TcpClient>();

		static async Task Main (string[] args)
		{
			var serverBroadcastThread = new Thread(new ThreadStart( () => {
				UdpClient server = new UdpClient(11000);
				var host = Dns.GetHostEntry(Dns.GetHostName());

				while (true)
				{
					var clientEp = new IPEndPoint(IPAddress.Any, 0);
					server.Receive(ref clientEp);
					
					foreach (var ip in host.AddressList)
					{
						if (clientEp.Address.ToString() == ip.ToString())
						{
							var adress = Encoding.ASCII.GetBytes(Utility.Utility.GetLocalIPAddress());
							server.Send(adress, adress.Length, clientEp);

							break;
						}
					}
				}				
			}));

			serverBroadcastThread.Start();

			TcpListener serverSocket = new TcpListener(IPAddress.Any, 7777);
			
			serverSocket.Start();
			Console.WriteLine(" >> Server Started");

			var leavers = new List<KeyValuePair<Guid, TcpClient>>();
			Task<TcpClient> client = null;
			while (true)
			{
				if (client == null )
				{
					client = serverSocket.AcceptTcpClientAsync();
				}
				if (client.IsCompleted)
				{
					ConnectedClients.Add(client.Result);
					Console.WriteLine(" >> Client connected!");

					client = null;
				}

				foreach (var connectedClient in ConnectedClients)
				{
					NetworkStream ns = connectedClient.GetStream();
					
					if (ns.DataAvailable)
					{
						byte[] data = new byte[1024];

						int count = await ns.ReadAsync(data, 0, data.Length);
						var payload = Encoding.ASCII.GetString(data, 0, count).Split(';');
						
						switch(payload[0])
						{
							case "leave":
								var leaver = new KeyValuePair<Guid, TcpClient>(Guid.Parse(payload[1]), connectedClient);
								leavers.Add(leaver);
								LeaveRoom(connectedClient, payload[1]);
								break;
							case "post":
								PostMessage(payload);
								break;
							case "join":
								RoomClients[Guid.Parse(payload[1])].Add(connectedClient);
								break;
							case "refresh":
								RefreshRooms(connectedClient);
								break;
							case "newroom":
								NewRoom(connectedClient);
								break;
							default:
								Console.WriteLine("default");
								break;
						}
					}
				}

				foreach (var leaver in leavers)
				{
					RoomClients[leaver.Key].Remove(leaver.Value);
						
					Console.WriteLine(" >> Client has left a room with id {0}.", leaver.Key.ToString());
				}

				leavers.Clear();
			}
		}

		private static async void NewRoom (TcpClient client)
		{
			NetworkStream ns = client.GetStream();

			Guid roomId = Guid.NewGuid();
			RoomClients[roomId] = new List<TcpClient>(){client};

			string response = "newroom;" + roomId.ToString();

			await ns.WriteAsync(Encoding.ASCII.GetBytes(response), 0, response.Length);
		}

		private static async void LeaveRoom (TcpClient client, string roomId)
		{
			NetworkStream ns = client.GetStream();

			string response = "leave;" + roomId;

			await ns.WriteAsync(Encoding.ASCII.GetBytes(response), 0, response.Length);
		}

		private static async void PostMessage (string[] payload)
		{
			string data = payload[0] + ';' + payload[1] + ';' + payload[2];

			byte[] message = Encoding.ASCII.GetBytes(data);

			foreach (TcpClient c in RoomClients[Guid.Parse(payload[1])])
			{
				NetworkStream clientNs = c.GetStream();

				await clientNs.WriteAsync(message, 0, message.Length);	
			}
		}

		private static async void RefreshRooms (TcpClient client)
		{
			NetworkStream ns = client.GetStream();
			string stringifiedChatRooms = "None";
			
			if (RoomClients.Count > 0)
			{
				stringifiedChatRooms = "";
				for (int i = 0; i < RoomClients.Count; i++)
				{
					string roomId = RoomClients.Keys.ToList()[i].ToString();
					stringifiedChatRooms += "Room " + i.ToString() + '|' + roomId + ';';
				}			
			}
			
			stringifiedChatRooms = "refresh;" + stringifiedChatRooms;

			await ns.WriteAsync(Encoding.ASCII.GetBytes(stringifiedChatRooms), 0, stringifiedChatRooms.Length);	
		}
	}
}
