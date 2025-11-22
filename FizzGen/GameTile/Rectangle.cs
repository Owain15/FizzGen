using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FizzGen.GameTile
{
	public class Rectangle : GameTile
	{
		public Rectangle()
		{ 
			Size = 400;
			GridPosition = (0,0);
		}

		public Rectangle((int x, int y) gridPosition)
		{
			Size = 100;
			GridPosition = gridPosition;
		}

		public Rectangle(long tileSize, (int x, int y) gridPosition)
		{
			Size = tileSize;
			GridPosition = gridPosition;
		}


	}
}
