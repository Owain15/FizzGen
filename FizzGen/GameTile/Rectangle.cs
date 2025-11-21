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
			Id = 0;
			Size = 400;
			GridPosition = (0,0);
		}
	}
}
