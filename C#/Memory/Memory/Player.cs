using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Memory
{
    class Player
    {
        public string PlayerName { get; }
        public int score { get; set; }

        public Player(string name)
        {
            PlayerName = name;
            score = 0;
        }
    }
}
