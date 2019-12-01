using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TicTacToe
{
    public partial class MainForm : Form
    {
        public static List<MyButton> listOfMyButtons;
        public static List<Button> buttons;

        private enum Players { FirstPlayer, SecondPlayer };

        private static Players player = Players.FirstPlayer;
        
        public MainForm()
        {
            InitializeComponent();

            buttons = new List<Button>
            {
                button1, button2, button3,
                button4, button5, button6,
                button7, button8, button9
            };

            listOfMyButtons = new List<MyButton>
            {
                new MyButton(button1, ""), new MyButton(button2, ""), new MyButton(button3, ""),
                new MyButton(button4, ""), new MyButton(button5, ""), new MyButton(button6, ""),
                new MyButton(button7, ""), new MyButton(button8, ""), new MyButton(button9, "")
            };

            WhosTurn.Text = player.ToString();
        }
        
        private void MyButtonClick(object sender, EventArgs e)
        {
            MyButton myB = listOfMyButtons.Find(x => x.AssociatedButton.Equals(sender as Button));

            Button clickedButton = listOfMyButtons.Find(y => y.AssociatedButton.Equals(sender as Button)).AssociatedButton;

            if (!myB.IsClicked)
            {
                if (player == Players.FirstPlayer)
                {
                    myB.Value = "X";
                    clickedButton.Text = "X";
                }
                else
                {
                    myB.Value = "O";
                    clickedButton.Text = "O";
                }
                
                myB.IsClicked = true;

                if (IsGameOver(clickedButton))
                {
                    winner.Text = player.ToString();
                    
                    foreach (Button b in buttons)
                        b.Enabled = false;
                }
                
                player = (player == Players.FirstPlayer) ? Players.SecondPlayer : Players.FirstPlayer;

                WhosTurn.Text = player.ToString();
            }
        }

        private bool IsGameOver(Button button)
        {
            int x = listOfMyButtons.FindIndex(y => y.AssociatedButton.Equals(button));
            string XorO = listOfMyButtons[x].Value;

            int i = x, bound, counter = 0;

            while (i >= 0) // find vertical left border
                i -= 3;

            i += 3;
            bound = i + 6;

            while (i <= bound) // vertical
            {
                if (listOfMyButtons[i].Value == XorO)
                {
                    counter++;

                    if (counter == 3)
                        return true;
                } 
                else
                    break;
                i += 3;
            }
            
            i = x; counter = 0;

            while (true) // find horizontal left border
            {
                if (i == 0 || i == 3 || i == 6)
                    break;

                i--;
            }

            bound = i + 2;
            
            while (i <= bound) // horizontal
            {
                if (listOfMyButtons[i].Value == XorO)
                {
                    counter++;

                    if (counter == 3)
                        return true;
                }
                else
                    break;
                i++;
            }
            
            if (x % 2 == 0) // diagonal
            {
                if (x == 0 || x == 8)
                {
                    for (int t = 0; t <= 8; t += 4)
                        if (listOfMyButtons[t].Value != XorO)
                            return false;

                    return true;
                }
                else
                {
                    for (int t = 2; t <= 6; t += 2)
                        if (listOfMyButtons[t].Value != XorO)
                            return false;

                    return true;
                }
            }
            
            return false;
        }
    }
}
