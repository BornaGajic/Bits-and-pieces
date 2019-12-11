using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Threading;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Memory.Properties;


namespace Memory
{
    public partial class MainForm : Form
    {
        private List<Button> buttons = new List<Button>();
        private List<int> imageIndices = new List<int>();
        private List<Bitmap> images;
        
        private Player FirstPlayer { get; }
        private Player SecondPlayer { get; }

        private int ClickCounter {get; set;}

        private Button FirstClickedButton { get; set; }

        public MainForm(string firstName, string secondName)
        {
            InitializeComponent();

            FirstPlayer = new Player(firstName);
            SecondPlayer = new Player(secondName);

            buttons = tableLayoutPanel1.Controls.OfType<Button>().ToList();

            images = new List<Bitmap>
            {
                Resources.fotoaparat, Resources.joystick,
                Resources.laptop, Resources.mobitel,
                Resources.tablet, Resources.sunce,
                Resources.tocke, Resources.krug,
                Resources.graf, Resources.robot,
                Resources.fotoaparat, Resources.joystick,
                Resources.laptop, Resources.mobitel,
                Resources.tablet, Resources.sunce,
                Resources.tocke, Resources.krug,
                Resources.graf, Resources.robot
            };

            foreach (Button b in buttons)
                b.Click += ButtonClick;

            ShuffleImages();

            TurnText.Text = FirstPlayer.PlayerName;
            ScoreX.Text = firstName + ": 0";
            ScoreY.Text = secondName + ": 0";

            FirstPlayer.score = 0;
            SecondPlayer.score = 0;
        }

        private void ButtonClick(object sender, EventArgs args)
        {
            ClickCounter++;

            Button clickedButton = sender as Button;
            clickedButton.Text = "";

            if (ClickCounter == 2)
            {
                string sndStr = clickedButton.Name.ToString().Replace("button", "");
                int sndButtonNum = int.Parse(sndStr);

                clickedButton.BackgroundImage = images[sndButtonNum - 1];
                Refresh();

                Thread.Sleep(2000);

                int cbW = clickedButton.BackgroundImage.Width;
                int fcbW = FirstClickedButton.BackgroundImage.Width;
                int cbH = clickedButton.BackgroundImage.Height;
                int fcbH = FirstClickedButton.BackgroundImage.Height;

                if (cbW == fcbW && cbH == fcbH)
                {
                    clickedButton.Enabled = FirstClickedButton.Enabled = false;

                    if (TurnText.Text == FirstPlayer.PlayerName)
                    {
                        FirstPlayer.score++;

                        ScoreX.Text = FirstPlayer.PlayerName + ": " + FirstPlayer.score.ToString();
                        
                        clickedButton.Text = FirstClickedButton.Text = "";
                    }
                    else
                    {
                        SecondPlayer.score++;

                        ScoreY.Text = SecondPlayer.PlayerName + ": " + SecondPlayer.score.ToString();
                        
                        clickedButton.Text = FirstClickedButton.Text = "";
                    }
                }
                else
                {
                    clickedButton.BackgroundImage = FirstClickedButton.BackgroundImage = base.BackgroundImage;

                    clickedButton.Text = FirstClickedButton.Text = "?";

                    TurnText.Text = TurnText.Text == FirstPlayer.PlayerName ? SecondPlayer.PlayerName : FirstPlayer.PlayerName;
                }

                ClickCounter = 0;
            }
            else
            {
                string strButtonNum = clickedButton.Name.ToString().Replace("button", "");
                int buttonNum = int.Parse(strButtonNum);

                clickedButton.BackgroundImage = images[buttonNum - 1];

                FirstClickedButton = clickedButton;
            }

            foreach (Button b in buttons)
            {
                if (b.Enabled == true)
                    return;
            }

            if (FirstPlayer.score > SecondPlayer.score)
                Winner.Text = FirstPlayer.score.ToString();
            else if (FirstPlayer.score == SecondPlayer.score)
                Winner.Text = "Draw!";
            else
                Winner.Text = SecondPlayer.score.ToString();
        }

        // rearranges images in the list
        private void ShuffleImages()
        {
            Random random = new Random();
            
            int n = buttons.Count;
            while (n > 1)
            {
                n--;
                int r = random.Next(n + 1);
                Bitmap temp = images[r];
                images[r] = images[n];
                images[n] = temp;
            }
        }
    }
}
