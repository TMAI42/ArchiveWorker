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
        private List<string> addList;
        private List<string> nameList;

        private string AddListProp
        {
            set
            {
                addList.Add(value);
                nameList.Add(value.Substring(value.LastIndexOf("\\") + 1));
            }
        }

        public MainWindow()
        {
            InitializeComponent();
            addList = new List<string>();
            nameList = new List<string>();
        }

        private void WriteNew(object sender, RoutedEventArgs e)
        {
            if (Type.SelectedIndex < 0)
            {
                MessageBox.Show("Select type!", "", MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }

            if (addList.Count == 0)
            {
                MessageBox.Show("Add elemets to addlist!", "", MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }


            if (ArchiveName.Text.Length == 0)
            {
                MessageBox.Show("Add name of new Archive!", "", MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }

            if (current == null)
                current = new ArchiveExternal(System.Reflection.Assembly.GetExecutingAssembly().Location,
                    TypeOfArchive.Standart);

            var tmp = FolderBrowse();

            if (tmp == null)
                return;

            current.WriteToArchive(addList, ArchiveName.Text + "." + Type.Text, Type.Text, tmp + "\\", (int)ComprsionLvl.Value);
            DisplayAchiveData();

            addList.Clear();
            nameList.Clear();

        }

        private void AddToOpen(object sender, RoutedEventArgs e)
        {
            if (current == null)
                return;

            current.AddToArchive(addList);

            addList.Clear();
            nameList.Clear();
        }

        private void Extract(object sender, RoutedEventArgs e)
        {
            if (current == null)
            {
                MessageBox.Show("Open archive!", "", MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }

            var tmp = FolderBrowse();

            if (tmp == null)
                return;

            current.Extract(tmp + "\\");
            MessageBox.Show("Exracted!", "", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void AddToList(object sender, RoutedEventArgs e)
        {

            var tmp = Browse();
            if (tmp == null)
            {
                return;
            }

            AddListProp = tmp;

            AddList.ItemsSource = null;
            AddList.ItemsSource = nameList;

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

            DisplayAchiveData();

            GetWindow(this).UpdateLayout();
        }

        private void ConvertTo(object sender, RoutedEventArgs e)
        {

            if (Type.SelectedIndex < 0)
            {
                MessageBox.Show("Select type!", "", MessageBoxButton.OK, MessageBoxImage.Information);
            }

            var tmp = Browse();
            if (tmp == null)
            {
                return;
            }

            if (current != null)
                current.Dispose();

            current = new ArchiveExternal(tmp, TypeOfArchive.Standart);

            DisplayAchiveData();

            GetWindow(this).UpdateLayout();

            current.ConvertTo(tmp.Substring(0, tmp.Length - tmp.LastIndexOf("\\") + 1), Type.Text);

            MessageBox.Show($"Converted to { Type.Text }!", "", MessageBoxButton.OK, MessageBoxImage.Information); ;

        }

        private string Browse()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();

            openFileDialog.Filter =
                "All files (*.*)|*.*|" +
                "Zip files (*.zip)|*.zip|" +
                "Archive files|*.tar;*.rar;*.7z;*.lz;*.lzma;*.zip";


            openFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

            if (openFileDialog.ShowDialog() == true)
            {
                return openFileDialog.FileName;
            }

            return null;
        }

        string FolderBrowse()
        {
            using (var dialog = new System.Windows.Forms.FolderBrowserDialog())
            {
                System.Windows.Forms.DialogResult result = dialog.ShowDialog();

                if (result == System.Windows.Forms.DialogResult.OK)
                    return dialog.SelectedPath;
            }

            return null;
        }

        void DisplayAchiveData()
        {
            IntPtr hWnd = wfhSample.Child.Handle;

            current.SetDrawingObject(hWnd, (int)wfhSample.ActualWidth, (int)wfhSample.ActualHeight, TypeOfDiagram.ArchiveSizeDependency);

            Archive.ItemsSource = current.ReadArchive();

            current.DisplayArchiv();
        }

    }
}
