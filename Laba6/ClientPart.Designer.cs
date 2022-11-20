using System.Windows.Forms;

namespace Laba6 {
    partial class UniversityForm {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            this.ButtonChooseFile = new System.Windows.Forms.Button();
            this.CollectionField = new System.Windows.Forms.ComboBox();
            this.Responser = new System.Windows.Forms.TextBox();
            this.SpecializationList = new System.Windows.Forms.ListBox();
            this.DataTable = new System.Windows.Forms.DataGridView();
            this.cityDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.nameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.markDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.universityBindingSource = new System.Windows.Forms.BindingSource(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.DataTable)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.universityBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // ButtonChooseFile
            // 
            this.ButtonChooseFile.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.ButtonChooseFile.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.ButtonChooseFile.FlatAppearance.BorderSize = 2;
            this.ButtonChooseFile.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Gray;
            this.ButtonChooseFile.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Silver;
            this.ButtonChooseFile.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.ButtonChooseFile.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ButtonChooseFile.Location = new System.Drawing.Point(634, 412);
            this.ButtonChooseFile.Name = "ButtonChooseFile";
            this.ButtonChooseFile.Size = new System.Drawing.Size(154, 37);
            this.ButtonChooseFile.TabIndex = 0;
            this.ButtonChooseFile.Text = "Выберите файл";
            this.ButtonChooseFile.UseVisualStyleBackColor = true;
            this.ButtonChooseFile.Click += new System.EventHandler(this.ButtonChooseFile_Click);
            // 
            // CollectionField
            // 
            this.CollectionField.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.CollectionField.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CollectionField.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.CollectionField.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CollectionField.FormattingEnabled = true;
            this.CollectionField.ItemHeight = 20;
            this.CollectionField.Items.AddRange(new object[] { "Список", "Словарь" });
            this.CollectionField.Location = new System.Drawing.Point(486, 412);
            this.CollectionField.Name = "CollectionField";
            this.CollectionField.Size = new System.Drawing.Size(127, 28);
            this.CollectionField.TabIndex = 1;
            this.CollectionField.SelectedIndexChanged += new System.EventHandler(this.CollectionField_SelectedIndexChanged);
            // 
            // Responser
            // 
            this.Responser.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) | System.Windows.Forms.AnchorStyles.Right)));
            this.Responser.BackColor = System.Drawing.SystemColors.Control;
            this.Responser.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.Responser.Cursor = System.Windows.Forms.Cursors.Default;
            this.Responser.Enabled = false;
            this.Responser.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Responser.ForeColor = System.Drawing.SystemColors.Desktop;
            this.Responser.Location = new System.Drawing.Point(12, 12);
            this.Responser.Name = "Responser";
            this.Responser.ReadOnly = true;
            this.Responser.Size = new System.Drawing.Size(776, 25);
            this.Responser.TabIndex = 4;
            this.Responser.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // SpecializationList
            // 
            this.SpecializationList.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) | System.Windows.Forms.AnchorStyles.Right)));
            this.SpecializationList.BackColor = System.Drawing.SystemColors.Control;
            this.SpecializationList.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.SpecializationList.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
            this.SpecializationList.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.SpecializationList.ForeColor = System.Drawing.Color.Black;
            this.SpecializationList.FormattingEnabled = true;
            this.SpecializationList.ItemHeight = 20;
            this.SpecializationList.Location = new System.Drawing.Point(541, 52);
            this.SpecializationList.Name = "SpecializationList";
            this.SpecializationList.Size = new System.Drawing.Size(247, 320);
            this.SpecializationList.TabIndex = 6;
            this.SpecializationList.DrawItem += new System.Windows.Forms.DrawItemEventHandler(this.SpecializationList_DrawItem);
            this.SpecializationList.SelectedIndexChanged += new System.EventHandler(this.SpecializationList_SelectedIndexChanged);
            // 
            // DataTable
            // 
            this.DataTable.AllowUserToAddRows = false;
            this.DataTable.AllowUserToDeleteRows = false;
            this.DataTable.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) | System.Windows.Forms.AnchorStyles.Left) | System.Windows.Forms.AnchorStyles.Right)));
            this.DataTable.AutoGenerateColumns = false;
            this.DataTable.BackgroundColor = System.Drawing.SystemColors.Control;
            this.DataTable.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.DataTable.ColumnHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.Single;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.Color.Gray;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.Color.White;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.Color.White;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.Color.White;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.DataTable.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.DataTable.ColumnHeadersHeight = 30;
            this.DataTable.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] { this.cityDataGridViewTextBoxColumn, this.nameDataGridViewTextBoxColumn, this.markDataGridViewTextBoxColumn });
            this.DataTable.DataSource = this.universityBindingSource;
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.TopLeft;
            dataGridViewCellStyle5.BackColor = System.Drawing.Color.White;
            dataGridViewCellStyle5.Font = new System.Drawing.Font("Arial Narrow", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle5.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle5.SelectionBackColor = System.Drawing.Color.White;
            dataGridViewCellStyle5.SelectionForeColor = System.Drawing.Color.White;
            dataGridViewCellStyle5.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.DataTable.DefaultCellStyle = dataGridViewCellStyle5;
            this.DataTable.EnableHeadersVisualStyles = false;
            this.DataTable.GridColor = System.Drawing.Color.Black;
            this.DataTable.Location = new System.Drawing.Point(12, 52);
            this.DataTable.Name = "DataTable";
            this.DataTable.ReadOnly = true;
            dataGridViewCellStyle6.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle6.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle6.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle6.SelectionBackColor = System.Drawing.Color.DarkGray;
            dataGridViewCellStyle6.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle6.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.DataTable.RowHeadersDefaultCellStyle = dataGridViewCellStyle6;
            this.DataTable.Size = new System.Drawing.Size(510, 339);
            this.DataTable.TabIndex = 7;
            this.DataTable.RowPostPaint += new System.Windows.Forms.DataGridViewRowPostPaintEventHandler(this.DataTable_RowPostPaint);
            // 
            // cityDataGridViewTextBoxColumn
            // 
            this.cityDataGridViewTextBoxColumn.DataPropertyName = "City";
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.Color.Silver;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.Color.Black;
            this.cityDataGridViewTextBoxColumn.DefaultCellStyle = dataGridViewCellStyle2;
            this.cityDataGridViewTextBoxColumn.HeaderText = "Город";
            this.cityDataGridViewTextBoxColumn.Name = "cityDataGridViewTextBoxColumn";
            this.cityDataGridViewTextBoxColumn.ReadOnly = true;
            this.cityDataGridViewTextBoxColumn.Width = 180;
            // 
            // nameDataGridViewTextBoxColumn
            // 
            this.nameDataGridViewTextBoxColumn.DataPropertyName = "Name";
            dataGridViewCellStyle3.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.Color.Silver;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.Color.Black;
            this.nameDataGridViewTextBoxColumn.DefaultCellStyle = dataGridViewCellStyle3;
            this.nameDataGridViewTextBoxColumn.HeaderText = "Университет";
            this.nameDataGridViewTextBoxColumn.Name = "nameDataGridViewTextBoxColumn";
            this.nameDataGridViewTextBoxColumn.ReadOnly = true;
            this.nameDataGridViewTextBoxColumn.Width = 150;
            // 
            // markDataGridViewTextBoxColumn
            // 
            this.markDataGridViewTextBoxColumn.DataPropertyName = "Mark";
            dataGridViewCellStyle4.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle4.SelectionBackColor = System.Drawing.Color.Silver;
            dataGridViewCellStyle4.SelectionForeColor = System.Drawing.Color.Black;
            this.markDataGridViewTextBoxColumn.DefaultCellStyle = dataGridViewCellStyle4;
            this.markDataGridViewTextBoxColumn.HeaderText = "Проходной балл";
            this.markDataGridViewTextBoxColumn.Name = "markDataGridViewTextBoxColumn";
            this.markDataGridViewTextBoxColumn.ReadOnly = true;
            this.markDataGridViewTextBoxColumn.Width = 130;
            // 
            // universityBindingSource
            // 
            this.universityBindingSource.DataSource = typeof(Laba6.University);
            // 
            // UniversityForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(800, 461);
            this.Controls.Add(this.DataTable);
            this.Controls.Add(this.SpecializationList);
            this.Controls.Add(this.Responser);
            this.Controls.Add(this.CollectionField);
            this.Controls.Add(this.ButtonChooseFile);
            this.MinimumSize = new System.Drawing.Size(815, 200);
            this.Name = "UniversityForm";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "База данных университетов";
            ((System.ComponentModel.ISupportInitialize)(this.DataTable)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.universityBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion

        private System.Windows.Forms.Button ButtonChooseFile;
        private System.Windows.Forms.ComboBox CollectionField;
        private System.Windows.Forms.TextBox Responser;
        private System.Windows.Forms.ListBox SpecializationList;
        private System.Windows.Forms.DataGridView DataTable;
        private System.Windows.Forms.BindingSource universityBindingSource;
        private DataGridViewTextBoxColumn cityDataGridViewTextBoxColumn;
        private DataGridViewTextBoxColumn nameDataGridViewTextBoxColumn;
        private DataGridViewTextBoxColumn markDataGridViewTextBoxColumn;
    }
}

