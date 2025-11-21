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

        double frameRate = 100;

		DispatcherTimer gameTimer;

        GameData gameData;

        Canvas canvas;


        public MainWindow()
        {

            InitializeComponent();

            gameData = new GameData();
            //InitializeBackCanvas();
            InitializeCanvas();

			InitializeGameTimer();

        }

        private void InitializeCanvas()
        {
			//< Canvas x: Name = "canvas" Background = "Black" Cursor = "None"
            //Margin = "30,30,30,30" UseLayoutRounding = "False"
            //ScrollViewer.VerticalScrollBarVisibility = "Disabled" />

            canvas = new Canvas();
            canvas.Cursor = Cursors.None;
            canvas.Margin = new Thickness(30);
            canvas.Background = Brushes.Black;

            grid.Children.Add(canvas);

        }

        private void InitializeGameTimer()
		{
            gameTimer = new DispatcherTimer();
            gameTimer.Interval = TimeSpan.FromMilliseconds(frameRate);
            gameTimer.Tick += RunGameLoop;

            gameTimer.Start();
		}

        private void RunGameLoop(object sender, EventArgs e)
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

            AddRectanglToCanvas(gameData.gameBoard.tileGrid[0, 0], canvas);

            AddCircelToCanvas(gameData.p1, canvas);

		}

        internal void AddRectanglToCanvas(FizzGen.GameTile.GameTile tile, Canvas targetCanvas)
        {
			Rectangle rec = new Rectangle();
			rec.Height = tile.Size;
			rec.Width = tile.Size;
			rec.Fill = Brushes.Pink;

			targetCanvas.Children.Add(rec);
		}

        internal void AddCircelToCanvas(FizzGen.Object.Circle circle, Canvas targetCanvas)
        {
			Ellipse c1 = new Ellipse();

			(long x, long y) position = circle.Position;

			long radius = circle.Radius;

			c1.Height = radius;
			c1.Width = radius;

			c1.Fill = Brushes.WhiteSmoke;

			targetCanvas.Children.Add(c1);

			Canvas.SetTop(c1, (position.y - (radius / 2)));
			Canvas.SetLeft(c1, (position.x - (radius / 2)));
		}

    }
}