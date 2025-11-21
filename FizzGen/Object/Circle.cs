using FizzGen.GameTile;

namespace FizzGen.Object
{
	public class Circle : FizzObject
	{
		
		public long Radius { get; set; }

		public Circle()
		{
			Radius = 1;
		}

		public Circle(long gridIndexX, long gridIndexY, long positionX, long positionY, long radius, long mass, long valocityX, long valocityY)
		{
			isPisyicsActive = true;
			GridIndex = (gridIndexX,gridIndexY);
			Position = (positionX, positionY);
			Radius = radius;
			Mass = mass;
			Valocity = (valocityX, valocityY);
		}

		public void Update(GameBoard.SquareGrid tileGrid)
		{
			GameTile.Rectangle tileData = tileGrid.GetTile(CurrentGridId);

			Position = (Position.x + Valocity.x , Position.y + Valocity.y);
		}

	}
}
