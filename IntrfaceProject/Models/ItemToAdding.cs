using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace IntrfaceProject.Models
{
    class ItemToAdding
    {
        private string fullName;
        public string name
        {
            get
            {
                return fullName.Substring(fullName.LastIndexOf("\\") + 1);
            }
        }

        public ItemToAdding(string path)
        {
            fullName = path;
        }
    }
}
