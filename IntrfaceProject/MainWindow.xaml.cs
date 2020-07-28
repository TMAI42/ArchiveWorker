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






namespace IntrfaceProject
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ArchiveExternal current;
        private List<IntrfaceProject.Models.ItemToAdding> addList;
        public MainWindow()
        {
            InitializeComponent();
            addList = new List<IntrfaceProject.Models.ItemToAdding>();
            AddList.ItemsSource = addList;
        }

        private void WriteNew(object sender, RoutedEventArgs e)
        {
            if (Type.SelectedItem == null|| addList.Count()==0)
                return;

            if (current == null)
                current = new ArchiveExternal(System.Reflection.Assembly.GetExecutingAssembly().Location, 
                    TypeOfArchive.Standart);

            current.WriteToArchive(addList, "test", Type.Text);



        }

        private void AddToOpen(object sender, RoutedEventArgs e)
        {

        }

        private void Extract(object sender, RoutedEventArgs e)
        {

        }

        private void AddToList(object sender, RoutedEventArgs e)
        {
            var tmp = Browse();
            if (tmp == null)
            {
                return;
            }

            addList.Add(
                new Models.ItemToAdding()
                {
                    name = tmp.Substring(tmp.LastIndexOf("\\") + 1),
                    path = tmp.Substring(0, tmp.Length - tmp.LastIndexOf("\\") + 1)
                });

        }

        private void OpenArchive(object sender, RoutedEventArgs e)
        {
            var tmp = Browse();
            if (tmp == null)
            {
                return;
            }

            current = new ArchiveExternal(tmp, TypeOfArchive.Standart);

            //Window window = Window.GetWindow(Diagram);
            //var wih = new System.Windows.Interop.WindowInteropHelper(window);
            //IntPtr hWnd = wih.Handle;
            //current.SetDrawingObject(hWnd, (int)window.Width, (int)window.Height, TypeOfDiagram.ArchiveSizeDependency);

            //using (var archive = new ArchiveExternal(tmp, TypeOfArchive.Standart))
            //{
            Archive.ItemsSource = current.ReadArchive();

            //current.DisplayArchiv();
            //}
            //GetWindow(this).UpdateLayout();
        }

        private string Browse()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Text files (*.zip)|*.zip|All files (*.*)|*.*";
            openFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

            if (openFileDialog.ShowDialog() == true)
            {
                return openFileDialog.FileName;
            }

            return null;
        }
    }
}
