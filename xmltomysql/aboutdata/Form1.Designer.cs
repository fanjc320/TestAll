namespace aboutdata
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.gridSource = new System.Windows.Forms.DataGridView();
            this.openFileDialogSource = new System.Windows.Forms.OpenFileDialog();
            this.tb = new System.Windows.Forms.TextBox();
            this.btnsx = new System.Windows.Forms.Button();
            this.ctlPath = new System.Windows.Forms.ComboBox();
            this.buttonopen = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.gridSource)).BeginInit();
            this.SuspendLayout();
            // 
            // gridSource
            // 
            this.gridSource.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.gridSource.Location = new System.Drawing.Point(63, 39);
            this.gridSource.Name = "gridSource";
            this.gridSource.RowTemplate.Height = 23;
            this.gridSource.Size = new System.Drawing.Size(711, 481);
            this.gridSource.TabIndex = 9;
            // 
            // openFileDialogSource
            // 
            this.openFileDialogSource.FileName = "openFileDialog1";
            // 
            // tb
            // 
            this.tb.Location = new System.Drawing.Point(631, 13);
            this.tb.Name = "tb";
            this.tb.Size = new System.Drawing.Size(121, 21);
            this.tb.TabIndex = 10;
            // 
            // btnsx
            // 
            this.btnsx.Location = new System.Drawing.Point(458, 13);
            this.btnsx.Name = "btnsx";
            this.btnsx.Size = new System.Drawing.Size(75, 23);
            this.btnsx.TabIndex = 8;
            this.btnsx.Text = "数据导入";
            this.btnsx.UseVisualStyleBackColor = true;
            this.btnsx.Click += new System.EventHandler(this.btnsx_Click);
            // 
            // ctlPath
            // 
            this.ctlPath.FormattingEnabled = true;
            this.ctlPath.Location = new System.Drawing.Point(63, 13);
            this.ctlPath.Name = "ctlPath";
            this.ctlPath.Size = new System.Drawing.Size(277, 20);
            this.ctlPath.TabIndex = 7;
            // 
            // buttonopen
            // 
            this.buttonopen.Location = new System.Drawing.Point(359, 13);
            this.buttonopen.Name = "buttonopen";
            this.buttonopen.Size = new System.Drawing.Size(75, 23);
            this.buttonopen.TabIndex = 6;
            this.buttonopen.Text = "打开";
            this.buttonopen.UseVisualStyleBackColor = true;
            this.buttonopen.Click += new System.EventHandler(this.buttonopen_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(868, 505);
            this.Controls.Add(this.gridSource);
            this.Controls.Add(this.tb);
            this.Controls.Add(this.btnsx);
            this.Controls.Add(this.ctlPath);
            this.Controls.Add(this.buttonopen);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.gridSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView gridSource;
        private System.Windows.Forms.OpenFileDialog openFileDialogSource;
        private System.Windows.Forms.TextBox tb;
        private System.Windows.Forms.Button btnsx;
        private System.Windows.Forms.ComboBox ctlPath;
        private System.Windows.Forms.Button buttonopen;
    }
}

