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

        double frameRate = 20;

		DispatcherTimer gameTimer;

        FizzGen.Code.GameData gameData;

        //Canvas backCanvas;


        public MainWindow()
        {
            InitializeComponent();

            gameData = new Code.GameData();
            //InitializeBackCanvas();
            InitializeCanvas();

			InitializeGameTimer();

        }



        //private void InitializeBackCanvas()
        //      {
        //          backCanvas = new Canvas();
        //          backCanvas.Background = Brushes.Brown;

        //      }

        private void InitializeCanvas()
        {
            Ellipse c1 = new Ellipse();

            (long x, long y) position = gameData.p1.Position;

			long radius = gameData.p1.Radius;

            c1.Height = radius;
            c1.Width = radius;

            c1.Fill = Brushes.WhiteSmoke;
            c1.Tag = gameData.p1.Id.ToString();

            canvas.Children.Add(c1);

            Canvas.SetTop(c1,(position.y - (radius/2)));
            Canvas.SetLeft(c1, (position.x - (radius / 2)));

			//Ellipse c1c = new Ellipse();


			//c1c.Height = 1;
			//c1c.Width = 1;

			//c1c.Fill = Brushes.Red;

			//canvas.Children.Add(c1c);

			//Canvas.SetTop(c1c, position.y) ;
			//Canvas.SetLeft(c1c, position.x);

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
            //UpdateBackCanvas();
            //canvas = backCanvas;
        }

        private void UpdateGameData()
        { gameData.Update(); }

        private void UpdateCanvas()
        {
			foreach(var shape in canvas.Children.OfType<Ellipse>())
            {
                if((string)shape.Tag == gameData.p1.Id.ToString())
                {
                    Canvas.SetTop(shape, gameData.p1.Position.x -(gameData.p1.Radius/2));
                    Canvas.SetLeft(shape, gameData.p1.Position.y -(gameData.p1.Radius / 2));
                }
            }

		}

		//private void UpdateBackCanvas()
		//{
		//	backCanvas.Background = Brushes.Teal;
		//}


	}
}