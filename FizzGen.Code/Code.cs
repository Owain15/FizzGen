namespace FizzGen.Code
{
	public class GameData
	{
		public Circle p1;

		public GameData()
		{
			p1 = new Circle();
		}

		public void  Update()
		{
			p1.Update();
		}

	}

	public class Circle
	{
		public long Id { get; set; }

		public (long x ,long y) Position { get; set; }

		public long Radius { get; set; }

		public long Mass { get; set; }

		public (long x, long y) Valocity { get; set; }

		public Circle()
		{
			Position = (10, 10);
			Radius = 20;
			Mass = 10;
			Valocity = (10,10);
		}

		public void Update()
		{
			Position = (Position.x + Valocity.x , Position.y + Valocity.y);
		}

	}
}
