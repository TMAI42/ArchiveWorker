using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;

using ArchiveProjectCLI;
using IntrfaceProject.Models;

namespace IntrfaceProject
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ArchiveExternal current;
        private List<string> addList;

        public MainWindow()
        {
            InitializeComponent();
            addList = new List<string>();
           
        }

        private void WriteNew(object sender, RoutedEventArgs e)
        {
            if (Type.SelectedItem == null|| addList.Count()==0)
                return;

            if (current == null)
                current = new ArchiveExternal(System.Reflection.Assembly.GetExecutingAssembly().Location, 
                    TypeOfArchive.Standart);

            current.WriteToArchive(addList, "test", Type.Text);

            Archive.ItemsSource = current.ReadArchive();

        }

        private void AddToOpen(object sender, RoutedEventArgs e)
        {
            if (current == null)
                return;

            current.AddToArchive(addList);
        }

        private void Extract(object sender, RoutedEventArgs e)
        {
            if (current == null)
                return;

            current.Extract(Browse());
        }

        private void AddToList(object sender, RoutedEventArgs e)
        {
            var tmp = Browse();
            if (tmp == null)
            {
                return;
            }

            addList.Add(tmp);

            //List<ItemToAdding> itemsToAddingTmp = new List<ItemToAdding>();

            //foreach (var path in addList)
            //    ttttt.itemsToAdding.Add(new ItemToAdding(path));
            AddList.ItemsSource = null;
            AddList.ItemsSource = addList;
          
            //AddList.ItemsSource = ttttt.itemsToAdding;
            //AddList.SourceUpdated(() => { });


        }

        private void OpenArchive(object sender, RoutedEventArgs e)
        {
            var tmp = Browse();
            if (tmp == null)
            {
                return;
            }

            if (current != null)
                current.Dispose();

            current = new ArchiveExternal(tmp, TypeOfArchive.Standart);

            //Window window = Window.GetWindow(qwr);
            //qwr.Handle;
            //var wih = new System.Windows.Interop.WindowInteropHelper(window);

            IntPtr hWnd = wfhSample.Child.Handle;
            current.SetDrawingObject(hWnd, 500, 700, TypeOfDiagram.MaxSizeDependency);

            //using (var archive = new ArchiveExternal(tmp, TypeOfArchive.Standart))
            //{
            Archive.ItemsSource = current.ReadArchive();

            current.DisplayArchiv();
        //}
        GetWindow(this).UpdateLayout();
    }

        private string Browse()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Zip files (*.zip)|*.zip, *.tar|All files (*.*)|*.*";
            openFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

            if (openFileDialog.ShowDialog() == true)
            {
                return openFileDialog.FileName;
            }

            return null;
        }


       

    }
}
