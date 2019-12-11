using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Memory
{
    public partial class IntroScreen : Form
    {
        private string FirstPlayerName { get; set; }
        private string SecondPlayerName { get; set; }

        public IntroScreen()
        {
            InitializeComponent();

            FirstPlayerName = SecondPlayerName = "";
            
            ApplyButton.Click += OnApplyClicked;
            fText.TextChanged += OnFirstTextChanged;
            sText.TextChanged += OnSecondTextChanged;
        }

        private void OnApplyClicked(object sender, EventArgs args)
        {
            string defaultString = "Player X";
            string defaultStringTwo = "Player Y";

            if (FirstPlayerName == "")
            {
                MainForm mainForm = new MainForm(defaultString, SecondPlayerName);
                this.Hide();
                mainForm.ShowDialog();
                this.Close();
            }
            else if (SecondPlayerName == "")
            {
                MainForm mainForm = new MainForm(FirstPlayerName, defaultStringTwo);
                this.Hide();
                mainForm.ShowDialog();
                this.Close();
            }
            else
            {
                MainForm mainForm = new MainForm(FirstPlayerName, SecondPlayerName);
                this.Hide();
                mainForm.ShowDialog();
                this.Close();
            }

            //this.Close();
        }

        private void OnFirstTextChanged(object sender, EventArgs args)
        {
            TextBox textBox = sender as TextBox;
            FirstPlayerName = textBox.Text;
        }

        private void OnSecondTextChanged(object sender, EventArgs args)
        {
            TextBox textBox = sender as TextBox;
            SecondPlayerName = textBox.Text;
        }
    }
}
