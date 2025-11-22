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

			if(!isPisyicsActive)
			{ return; }

			GameTile.Rectangle tileData = tileGrid.GetTile(GridIndex);

			Position = (Position.x + Valocity.x , Position.y + Valocity.y);

			//check if circle goes out off tile (stop if edge of grid & grid not looped)
			if
			(   
				
				Position.x < (Radius / 2) || Position.x > tileData.Size - (Radius / 2) ||
				Position.y < (Radius / 2) || Position.y > tileData.Size - (Radius / 2)
			)
			{
				
				//check if circle position goes off grid, adjust GridIndex & position data
				if
				(
					Position.x < 0 || Position.x > tileData.Size  ||
					Position.y < 0 || Position.y > tileData.Size 
				)
				{ 
				
					if(Position.x < 0)
					{
						GridIndex = (GridIndex.x - 1 < 0) ?  (tileGrid.tileGrid.GetLength(0)-1, GridIndex.y) : (GridIndex.x - 1, GridIndex.y);
						Position = ((tileGrid.GetTileDimentions(GridIndex.x, GridIndex.y).x + Position.x),Position.y);
					}
					if (Position.x > tileData.Size)
					{
						GridIndex = (GridIndex.x + 1 > tileGrid.tileGrid.GetLength(0) - 1) ? (0, GridIndex.y) : (GridIndex.x + 1, GridIndex.y);
						Position = (Position.x - (tileGrid.GetTileDimentions(tileGrid.tileGrid.GetLength(0) - 1, GridIndex.y).x ), Position.y);
					}
					if (Position.y < 0)
					{
						GridIndex = (GridIndex.y - 1 < 0) ? (GridIndex.x, tileGrid.tileGrid.GetLength(1) - 1) : (GridIndex.x, GridIndex.y - 1);
						Position = (Position.x, (tileGrid.GetTileDimentions(GridIndex.x, GridIndex.y).y + Position.y) );
					}
					if (Position.y > tileData.Size)
					{
						GridIndex = (GridIndex.y + 1 > tileGrid.tileGrid.GetLength(1) - 1) ? (GridIndex.x, 0) : (GridIndex.x, GridIndex.y + 1);
						Position = (Position.x, Position.y - (tileGrid.GetTileDimentions(GridIndex.x, GridIndex.y).y ));
					}
				}
			}

		}

	

	}
}
