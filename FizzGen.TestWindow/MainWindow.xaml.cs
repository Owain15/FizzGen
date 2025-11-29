using FizzGen.Object;
using System.Text;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace FizzGen.TestWindow
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        double frameRate = 80;

		DispatcherTimer gameTimer;

        GameData gameData;

        Canvas canvas;


        public MainWindow()
        {

            InitializeComponent();

            gameData = new GameData();

            canvas = InitializeCanvas();

			gameTimer = InitializeGameTimer();

            gameTimer.Start();

        }

        private Canvas InitializeCanvas()
        {
			//< Canvas x: Name = "canvas" Background = "Black" Cursor = "None"
            //Margin = "30,30,30,30" UseLayoutRounding = "False"
            //ScrollViewer.VerticalScrollBarVisibility = "Disabled" />

            Canvas result = new Canvas();
			result.Cursor = Cursors.None;
			result.Margin = new Thickness(30);
			result.Background = Brushes.Black;

            grid.Children.Add(result);

            return result;
		}

        private DispatcherTimer InitializeGameTimer()
		{
            DispatcherTimer result = new DispatcherTimer();
   
			result.Interval = TimeSpan.FromMilliseconds(frameRate);
			result.Tick += RunGameLoop;

            return result;
		}

        private void RunGameLoop(object? sender, EventArgs e)
        {
            GameLoop();
        }


		private void GameLoop()
        {
            //UpdateInputs();
            UpdateGameData();
            UpdateCanvas();
        }

        private void UpdateGameData()
        { gameData.Update(); }

        private void UpdateCanvas()
        {
            canvas.Children.Clear();

            foreach (var tile in gameData.gameBoard.tileGrid)
            {
				AddRectanglToCanvas(tile, canvas);
			}

            foreach (var circle in gameData.GetGameObjects().OfType<Circle>())
            {

                AddCircelToCanvas(circle, gameData.gameBoard, canvas);
            }

		}

        internal void AddRectanglToCanvas(FizzGen.GameTile.GameTile tile, Canvas targetCanvas)
        {
			Rectangle rec = new Rectangle();
			rec.Height = tile.Size;
			rec.Width = tile.Size;
			rec.Fill = Brushes.Pink;
            rec.Stroke = Brushes.Black;

			targetCanvas.Children.Add(rec);

            Canvas.SetTop(rec,(tile.GridPosition.y * tile.Size));
            Canvas.SetLeft(rec,(tile.GridPosition.x * tile.Size));

		}

        internal void AddCircelToCanvas(FizzGen.Object.Circle circle, FizzGen.GameBoard.SquareGrid gridData, Canvas targetCanvas)
        {
			Ellipse c1 = new Ellipse();

			c1.Height = circle.Radius;
			c1.Width = circle.Radius;

			c1.Fill = Brushes.WhiteSmoke;
            c1.Stroke = Brushes.Black;

			targetCanvas.Children.Add(c1);

			Canvas.SetTop (c1, ((circle.GridIndex.y * 100) + circle.Position.y - (circle.Radius / 2)));
			Canvas.SetLeft(c1, ((circle.GridIndex.x * 100) + circle.Position.x - (circle.Radius / 2)));
		}

    }

}