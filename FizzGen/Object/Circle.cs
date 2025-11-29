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

		public void UpdatePosition()
		{
			if (!isPisyicsActive)
			{ return; }

			//update position
			Position = (Position.x + Valocity.x, Position.y + Valocity.y);

		}

		public void UpdateGridIndex(GameBoard.SquareGrid gridData)
		{

			if (Position.x < (Radius / 2))
			{
				if(Position.x <  0 && GridIndex.x > 0 || gridData.isGridLooped)
				{
					GridIndex = (GridIndex.x - 1 < 0) ? (gridData.tileGrid.GetLength(0) - 1, GridIndex.y) : (GridIndex.x - 1, GridIndex.y);
					Position = ((gridData.GetTileDimentions(GridIndex.x, GridIndex.y).x + Position.x), Position.y);
				}
				else if(GridIndex.x <= 0 && !gridData.isGridLooped)
				{  
					 Position = (((Position.x - (Radius / 2))* -1)+(Radius/2), Position.y);
					 Valocity = ((Valocity.x * -1), Valocity.y);
				}
			}
			
			if (Position.x > gridData.GetTileDimentions(GridIndex.x, GridIndex.y).x - (Radius / 2))
			{
				if(Position.x > gridData.GetTileDimentions(GridIndex.x, GridIndex.y).x && GridIndex.x < gridData.tileGrid.GetLength(0) - 1 || gridData.isGridLooped)
				{ 
					GridIndex = (GridIndex.x + 1 > gridData.tileGrid.GetLength(0) - 1) ? (0, GridIndex.y) : (GridIndex.x + 1, GridIndex.y);
					Position = (Position.x - (gridData.GetTileDimentions(gridData.tileGrid.GetLength(0) - 1, GridIndex.y).x), Position.y);
				}
				else if (GridIndex.x >= gridData.tileGrid.GetLength(0) - 1 && !gridData.isGridLooped)
				{
					Position = ((gridData.GetTileDimentions(GridIndex.x,GridIndex.y).x - (Radius/2))-((Position.x + (Radius/2))- gridData.GetTileDimentions(GridIndex.x, GridIndex.y).x), Position.y);
					Valocity = ((Valocity.x * -1), Valocity.y);
				}
			}

			if (Position.y < (Radius / 2))
			{
				if (Position.y < 0 && GridIndex.y > 0 || gridData.isGridLooped)
				{
					GridIndex = (GridIndex.y - 1 < 0) ? (GridIndex.x, gridData.tileGrid.GetLength(1) - 1) : (GridIndex.x, GridIndex.y - 1);
					Position = (Position.x, (gridData.GetTileDimentions(GridIndex.x, GridIndex.y).y + Position.y));
				}
				else if (GridIndex.y <= 0 && !gridData.isGridLooped)
				{
					Position = (Position.x, ((Position.y - (Radius / 2)) * -1) + (Radius / 2));
					Valocity = (Valocity.x, (Valocity.y * -1));
				}
			}

			if (Position.y > gridData.GetTileDimentions(GridIndex.x, GridIndex.y).y - (Radius / 2))
			{
				if (Position.y > gridData.GetTileDimentions(GridIndex.x, GridIndex.y).y && GridIndex.y < gridData.tileGrid.GetLength(1) - 1 || gridData.isGridLooped)
				{
					GridIndex = (GridIndex.y + 1 > gridData.tileGrid.GetLength(1) - 1) ? (GridIndex.x, 0) : (GridIndex.x, GridIndex.y + 1);
					Position = (Position.x , Position.y - (gridData.GetTileDimentions(gridData.tileGrid.GetLength(1) - 1, GridIndex.y).y));
				}
				else if (GridIndex.y >= gridData.tileGrid.GetLength(1) - 1 && !gridData.isGridLooped)
				{
					Position = ( Position.x, (gridData.GetTileDimentions(GridIndex.x, GridIndex.y).y - (Radius / 2)) - ((Position.y + (Radius / 2)) - gridData.GetTileDimentions(GridIndex.x, GridIndex.y).y));
					Valocity = (Valocity.x, (Valocity.y * -1));
				}
			}

		}

		public void Update(GameBoard.SquareGrid gridData)
		{

			if(!isPisyicsActive)
			{ return; }

			GameTile.Rectangle tileData = gridData.GetTile(GridIndex);

			//update position
			Position = (Position.x + Valocity.x , Position.y + Valocity.y);

			//check if circle goes off tile (stop if edge of grid & grid not looped)
			if
			(
				Position.x < 0 || Position.x > tileData.Size  ||
				Position.y < 0 || Position.y > tileData.Size 
			)
			{

				//check if grid is looped
				if (gridData.isGridLooped)
				{
					//change grid index, loop grid
					LoopedGridUpdate(gridData, tileData);
				}
				else
				{
			
				}

				
			}
			

		}

		private void LoopedGridUpdate(GameBoard.SquareGrid gridData, Rectangle tileData)
		{
			if (Position.x < 0)
			{
				GridIndex = (GridIndex.x - 1 < 0) ? (gridData.tileGrid.GetLength(0) - 1, GridIndex.y) : (GridIndex.x - 1, GridIndex.y);
				Position = ((gridData.GetTileDimentions(GridIndex.x, GridIndex.y).x + Position.x), Position.y);
			}
			if (Position.x > tileData.Size)
			{
				GridIndex = (GridIndex.x + 1 > gridData.tileGrid.GetLength(0) - 1) ? (0, GridIndex.y) : (GridIndex.x + 1, GridIndex.y);
				Position = (Position.x - (gridData.GetTileDimentions(gridData.tileGrid.GetLength(0) - 1, GridIndex.y).x), Position.y);
			}
			if (Position.y < 0)
			{
				GridIndex = (GridIndex.y - 1 < 0) ? (GridIndex.x, gridData.tileGrid.GetLength(1) - 1) : (GridIndex.x, GridIndex.y - 1);
				Position = (Position.x, (gridData.GetTileDimentions(GridIndex.x, GridIndex.y).y + Position.y));
			}
			if (Position.y > tileData.Size)
			{
				GridIndex = (GridIndex.y + 1 > gridData.tileGrid.GetLength(1) - 1) ? (GridIndex.x, 0) : (GridIndex.x, GridIndex.y + 1);
				Position = (Position.x, Position.y - (gridData.GetTileDimentions(GridIndex.x, GridIndex.y).y));
			}
		}


	}
}
