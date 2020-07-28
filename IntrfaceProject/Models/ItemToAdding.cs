using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace IntrfaceProject.Models
{
    class ItemToAdding : DependencyObject
    {
        public string name { get; set; }
        public string path { get; set; }

        public static readonly DependencyProperty MyPropertyProperty =
         DependencyProperty.Register("name", typeof(string), typeof(ItemToAdding), new PropertyMetadata(""));

        

    }
}
