using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FizzGen.GameTile
{
	public class GameTile
	{

		public int Id { get; set; }

		public long Size { get; set; }

		public (int x, int y) GridPosition{ get; set; }

		//public int SideCount { get; set; }

		//public long[] SideLength { get; set; }

		//public bool[] canSideBePassed { get; set; }

		//public int?[] sideLinkRef { get; set; } 

	}
}
