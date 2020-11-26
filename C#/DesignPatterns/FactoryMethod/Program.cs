using System;

namespace FactoryMethod
{
	// Creator
	public abstract class Logistics
	{
		public abstract ITransport CreateTransport ();

		// Other methods that both logistics can use
	}

	// Concrete creators
	public class LandLogistics : Logistics
	{
		override public ITransport CreateTransport ()
		{
			return new Truck();
		}

		// something specific before creating a new Truck
	}

	public class SeaLogistics : Logistics
	{
		public override ITransport CreateTransport ()
		{
			return new Ship();
		}

		// something specific before creating a new Ship
	}


	// Product
	public interface ITransport
	{
		void Deliver ();	
	}

	// Concrete products
	public class Truck : ITransport
	{
		public void Deliver()
		{
			Console.WriteLine("Delivery by land.");
		}
	}

	public class Ship : ITransport
	{
		public void Deliver()
		{
			Console.WriteLine("Delivery by sea.");
		}
	}

	class Program
	{
		public static void SomethingAfterDelivery (Logistics logistics)
		{
			logistics.CreateTransport().Deliver();
		}

		static void Main (string[] args)
		{
			string line = Console.ReadLine();

			if (line.ToLower() == "land")
			{
				SomethingAfterDelivery(new LandLogistics());
			}
			else if (line.ToLower() == "sea")
			{
				SomethingAfterDelivery(new SeaLogistics());
			}
		}
	}
}
