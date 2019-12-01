using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TicTacToe
{
    public class MyButton
    {
        public string Value { get; set; }
        public Button AssociatedButton { get; set; }
        public bool IsClicked { get; set; }
        
        public MyButton(Button b, string value)
        {
            Value = value;
            AssociatedButton = b;
            IsClicked = false;
        }

        /*
        public event EventHandler Click;
        public void OnClick()
        {
            EventHandler handler = Click;
            if (null != handler) handler(this, EventArgs.Empty);
        }
        */
    }
}
