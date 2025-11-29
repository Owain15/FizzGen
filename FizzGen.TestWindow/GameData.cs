using FizzGen.Object;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input.Manipulations;

namespace FizzGen.TestWindow
{
	internal class GameData
	{

		public GameBoard.SquareGrid gameBoard;

		private ICollection<FizzObject> gameObjects;

		public Circle p1;

		public Circle p2;

		public GameData()
		{
			gameBoard = new GameBoard.SquareGrid(3, false);

			p1 = new Circle(0, 0, 40, 40, 40, 10, 10, 10);

			//p2 = new Circle(1, 1, 50, 50, 10, 10, 0, 0);
			p2 = new Circle
			{
				isPisyicsActive = true,
				GridIndex = (0, 2),
				Position = (40, 60),
				Radius = 20,
				Mass = 10,
				Valocity = (10, -10)
			};

			gameObjects = new List<FizzObject>();

			gameObjects.Add(p1);
			gameObjects.Add(p2);
		}

		public ICollection<FizzObject> GetGameObjects() =>
			gameObjects;

		public void Update()
		{

			// Update all game objects
			foreach (FizzObject obj in gameObjects)
			{
				if (obj is Circle circle)
				{
					circle.UpdatePosition();
				}
			}

			// Collition detction/handeling, tiledata update
			foreach (FizzObject obj in gameObjects)
			{
				if (obj is Circle circle)
				{
					//tile data update, bunders and loop
					circle.UpdateGridIndex(gameBoard);
				}
			}
			



		}

	}


}
