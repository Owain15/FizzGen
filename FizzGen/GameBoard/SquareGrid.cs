using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FizzGen.GameBoard
{
	public class SquareGrid
	{
		//GameTile.Rectangle tile;

		public bool isGridLooped {  get; set; }

		public GameTile.Rectangle[,] tileGrid;

		public SquareGrid(int dimentions) 
		{
			isGridLooped = false;

			tileGrid = intalizeGrid(dimentions);


		
		}

		private GameTile.Rectangle[,] intalizeGrid(int dimentions)
		{
			GameTile.Rectangle[,] result = new GameTile.Rectangle[dimentions, dimentions];

			for(int y = 0; y < dimentions; y ++)
			{ for(int x = 0; x < dimentions; x++)
				{ result[x, y] = new GameTile.Rectangle((x,y)); }
			}

			return result;
		}

		public GameTile.Rectangle GetTile((long x, long y) gridLocation)
		{ return tileGrid[gridLocation.x,gridLocation.y]; }

		public (long x, long y) GetTileDimentions(long x, long y)
		{
			return (tileGrid[x, y].Size, tileGrid[x, y].Size);
		}

	}
}
