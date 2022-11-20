using System;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace Laba6
{
    public partial class UniversityForm : Form
    {
        Data data;

        public UniversityForm()
        {
            InitializeComponent();
            InitializeElements();
        }

        // Выбрать элемент по-умолчанию в ComboBox
        private void InitializeElements()
        {
            CollectionField.SelectedItem = CollectionField.Items[0];
        }

        // Нажатие на кнопку выбора файла
        private void ButtonChooseFile_Click(object sender, EventArgs e)
        {
            var dialog = new OpenFileDialog
            {
                Title = "Select file",
                InitialDirectory = @"C:\",
                Filter = "Текстовый документ (*.txt)|*.txt"
            };
            dialog.ShowDialog();
            if (dialog.FileName == "")
                Responser.Text = "Файл не выбран";
            else
            {
                data = new Data();
                string errorMessage =
                    data.FileHandler(dialog, ContainerChoice());
                if (errorMessage != null)
                    Responser.Text = errorMessage;
                else
                    SpecializationList.DataSource =
                        data.specializationSet.ToList();
                dialog.Dispose();
            }
        }

        // Метод динамического выбора коллекции в зависимости от выбранного
        // элемента в CollectionField
        private CollectionType ContainerChoice()
        {
            return CollectionField.SelectedItem == CollectionField.Items[0]
                ? CollectionType.List
                : CollectionType.Dictionary;
        }

        // Метод, вызываемый при смене выбранного элемента в списке специальностей
        private void SpecializationList_SelectedIndexChanged(object sender,
            EventArgs e)
        {
            SpecializationList.Invalidate();
            var list =
                data.GetRequest(SpecializationList.SelectedItem.ToString());
            Responser.Text = "По заданной специальности найдено " + list.Count +
                             " университета (-ов)";
            DataTable.DataSource = list;
            DataTable.CurrentCell.Selected = false;
        }

        // Нумерация строк
        private void DataTable_RowPostPaint(object sender,
            DataGridViewRowPostPaintEventArgs e)
        {
            int index = e.RowIndex;
            string indexStr = (index + 1).ToString();
            object header = DataTable.Rows[index].HeaderCell.Value;
            if (header == null || !header.Equals(indexStr))
                DataTable.Rows[index].HeaderCell.Value = indexStr;
        }

        // Метод перерисовки предметов в списке специализаций, служит для изменения цвета выделяемого элемента
        private void SpecializationList_DrawItem(object sender,
            DrawItemEventArgs e)
        {
            if (SpecializationList.Items.Count > 0)
            {
                int index = e.Index;
                var g = e.Graphics;
                foreach (int selectedIndex in
                         SpecializationList.SelectedIndices)
                {
                    if (index == selectedIndex)
                    {
                        // Отобразить новый цвет заднего фона
                        e.DrawBackground();
                        g.FillRectangle(new SolidBrush(Color.Silver), e.Bounds);
                    }
                }

                Font font = SpecializationList.Font;
                string text = SpecializationList.Items[index].ToString();

                // Выписать текст
                g.DrawString(text, font, new SolidBrush(Color.Black),
                    e.Bounds.X, e.Bounds.Y);
                e.DrawFocusRectangle();
            }
        }

        // Метод вызывается при выборе нового элемента в ComboBox
        private void CollectionField_SelectedIndexChanged(object sender,
            EventArgs e)
        {
            if (data != null)
                Responser.Text =
                    "Данный контейнер применится только после открытия нового файла";
        }
    }
}