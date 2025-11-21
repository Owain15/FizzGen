using FizzGen.Object;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FizzGen.TestWindow
{
	internal class GameData
	{

			public GameBoard.SquareGrid gameBoard;

			public Circle p1;

			public GameData()
			{
				gameBoard = new GameBoard.SquareGrid(1);

				p1 = new Circle(0,0,10,10,20,10,5,5);
			}

			public void Update()
			{
				p1.Update(gameBoard);
			}

	}

	
}
