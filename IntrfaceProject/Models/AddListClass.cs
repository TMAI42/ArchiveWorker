using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace IntrfaceProject.Models
{
    class AddListClass : INotifyPropertyChanged
    {
        private List<ItemToAdding> itemsToAdding;
        
        public List<ItemToAdding> ItemToAddings
        {
            get { return itemsToAdding; }
            set
            {
                itemsToAdding = value;
                OnPropertyChanged("ItemToAddings");
            }
        }

        public AddListClass()
        {
            itemsToAdding = new List<ItemToAdding>();
        }

        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }

        public ItemToAdding this[int index]
        {
            get
            {
                return itemsToAdding[index];
            }

            set
            {
                itemsToAdding[index] = value;
            }
        }
    }
}
