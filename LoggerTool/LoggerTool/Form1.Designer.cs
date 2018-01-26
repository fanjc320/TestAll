namespace LoggerTool
{
    partial class Analysis
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
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Analysis));
            this.textBox_Xml = new System.Windows.Forms.TextBox();
            this.textBox_Log = new System.Windows.Forms.TextBox();
            this.parseLog = new System.Windows.Forms.Button();
            this.OutMysql = new System.Windows.Forms.Button();
            this.TbsView = new System.Windows.Forms.TreeView();
            this.textBoxTbNum = new System.Windows.Forms.TextBox();
            this.textBoxSql = new System.Windows.Forms.TextBox();
            this.OutCsv = new System.Windows.Forms.Button();
            this.btn_createTb = new System.Windows.Forms.Button();
            this.btn_ClearTxt = new System.Windows.Forms.Button();
            this.textBox_csv = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.checkedListBox1 = new System.Windows.Forms.CheckedListBox();
            this.button3 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.button4 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox_Xml
            // 
            this.textBox_Xml.Location = new System.Drawing.Point(112, 3);
            this.textBox_Xml.Name = "textBox_Xml";
            this.textBox_Xml.Size = new System.Drawing.Size(350, 21);
            this.textBox_Xml.TabIndex = 11;
            this.textBox_Xml.TextChanged += new System.EventHandler(this.textBox_Xml_TextChanged);
            // 
            // textBox_Log
            // 
            this.textBox_Log.Location = new System.Drawing.Point(112, 30);
            this.textBox_Log.Name = "textBox_Log";
            this.textBox_Log.Size = new System.Drawing.Size(350, 21);
            this.textBox_Log.TabIndex = 13;
            this.textBox_Log.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            // 
            // parseLog
            // 
            this.parseLog.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.parseLog.Enabled = false;
            this.parseLog.Location = new System.Drawing.Point(-209, 33);
            this.parseLog.Name = "parseLog";
            this.parseLog.Size = new System.Drawing.Size(75, 23);
            this.parseLog.TabIndex = 14;
            this.parseLog.Text = "parseLog";
            this.parseLog.UseVisualStyleBackColor = true;
            this.parseLog.Click += new System.EventHandler(this.parseLog_Click);
            // 
            // OutMysql
            // 
            this.OutMysql.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.OutMysql.Enabled = false;
            this.OutMysql.Location = new System.Drawing.Point(-46, 33);
            this.OutMysql.Name = "OutMysql";
            this.OutMysql.Size = new System.Drawing.Size(75, 23);
            this.OutMysql.TabIndex = 15;
            this.OutMysql.Text = "导出数据库";
            this.OutMysql.UseVisualStyleBackColor = true;
            this.OutMysql.Click += new System.EventHandler(this.OutMysql_Click);
            // 
            // TbsView
            // 
            this.TbsView.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TbsView.Location = new System.Drawing.Point(289, 13);
            this.TbsView.Name = "TbsView";
            this.TbsView.Size = new System.Drawing.Size(168, 449);
            this.TbsView.TabIndex = 16;
            this.TbsView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.TbsView_AfterSelect);
            this.TbsView.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.TbsView_NodeMouseClick);
            // 
            // textBoxTbNum
            // 
            this.textBoxTbNum.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxTbNum.Location = new System.Drawing.Point(227, 13);
            this.textBoxTbNum.Name = "textBoxTbNum";
            this.textBoxTbNum.Size = new System.Drawing.Size(56, 21);
            this.textBoxTbNum.TabIndex = 17;
            this.textBoxTbNum.Text = "表的个数";
            // 
            // textBoxSql
            // 
            this.textBoxSql.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxSql.BackColor = System.Drawing.SystemColors.WindowText;
            this.textBoxSql.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBoxSql.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBoxSql.ForeColor = System.Drawing.SystemColors.Window;
            this.textBoxSql.Location = new System.Drawing.Point(24, 82);
            this.textBoxSql.MaxLength = 1000;
            this.textBoxSql.Multiline = true;
            this.textBoxSql.Name = "textBoxSql";
            this.textBoxSql.ReadOnly = true;
            this.textBoxSql.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBoxSql.Size = new System.Drawing.Size(92, 167);
            this.textBoxSql.TabIndex = 18;
            this.textBoxSql.TextChanged += new System.EventHandler(this.textBoxSql_TextChanged);
            // 
            // OutCsv
            // 
            this.OutCsv.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.OutCsv.Enabled = false;
            this.OutCsv.Location = new System.Drawing.Point(-127, 33);
            this.OutCsv.Name = "OutCsv";
            this.OutCsv.Size = new System.Drawing.Size(75, 23);
            this.OutCsv.TabIndex = 20;
            this.OutCsv.Text = "导出csv";
            this.OutCsv.UseVisualStyleBackColor = true;
            this.OutCsv.Click += new System.EventHandler(this.OutCsv_Click);
            // 
            // btn_createTb
            // 
            this.btn_createTb.Location = new System.Drawing.Point(564, 4);
            this.btn_createTb.Name = "btn_createTb";
            this.btn_createTb.Size = new System.Drawing.Size(75, 23);
            this.btn_createTb.TabIndex = 21;
            this.btn_createTb.Text = "建mysql表";
            this.btn_createTb.UseVisualStyleBackColor = true;
            this.btn_createTb.Click += new System.EventHandler(this.btn_createTb_Click);
            // 
            // btn_ClearTxt
            // 
            this.btn_ClearTxt.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_ClearTxt.Location = new System.Drawing.Point(49, 60);
            this.btn_ClearTxt.Name = "btn_ClearTxt";
            this.btn_ClearTxt.Size = new System.Drawing.Size(52, 23);
            this.btn_ClearTxt.TabIndex = 22;
            this.btn_ClearTxt.Text = "清空";
            this.btn_ClearTxt.UseVisualStyleBackColor = true;
            this.btn_ClearTxt.Click += new System.EventHandler(this.btn_ClearTxt_Click);
            // 
            // textBox_csv
            // 
            this.textBox_csv.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox_csv.Location = new System.Drawing.Point(123, 59);
            this.textBox_csv.Multiline = true;
            this.textBox_csv.Name = "textBox_csv";
            this.textBox_csv.Size = new System.Drawing.Size(159, 48);
            this.textBox_csv.TabIndex = 23;
            this.textBox_csv.TextChanged += new System.EventHandler(this.textBox_Uid_TextChanged);
            // 
            // button1
            // 
            this.button1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button1.Enabled = false;
            this.button1.Location = new System.Drawing.Point(123, 32);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 25;
            this.button1.Text = "uids:";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click_2);
            // 
            // button2
            // 
            this.button2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button2.Enabled = false;
            this.button2.Location = new System.Drawing.Point(35, 32);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(81, 23);
            this.button2.TabIndex = 26;
            this.button2.Text = "testMysql";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button_test_Click);
            // 
            // checkedListBox1
            // 
            this.checkedListBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.checkedListBox1.FormattingEnabled = true;
            this.checkedListBox1.Location = new System.Drawing.Point(112, 152);
            this.checkedListBox1.Name = "checkedListBox1";
            this.checkedListBox1.Size = new System.Drawing.Size(161, 276);
            this.checkedListBox1.TabIndex = 29;
            this.checkedListBox1.SelectedIndexChanged += new System.EventHandler(this.checkedListBox1_SelectedIndexChanged);
            // 
            // button3
            // 
            this.button3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button3.Location = new System.Drawing.Point(121, 123);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(52, 23);
            this.button3.TabIndex = 30;
            this.button3.Text = "全选";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(32, 11);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 31;
            this.label2.Text = "xmlpath：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(32, 33);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 12);
            this.label3.TabIndex = 32;
            this.label3.Text = "logpath：";
            // 
            // richTextBox1
            // 
            this.richTextBox1.BackColor = System.Drawing.SystemColors.MenuText;
            this.richTextBox1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.richTextBox1.ForeColor = System.Drawing.SystemColors.Window;
            this.richTextBox1.Location = new System.Drawing.Point(24, 365);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(348, 207);
            this.richTextBox1.TabIndex = 33;
            this.richTextBox1.Text = "test";
            this.richTextBox1.UseWaitCursor = true;
            this.richTextBox1.TextChanged += new System.EventHandler(this.richTextBox1_TextChanged);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(387, 375);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 23);
            this.button4.TabIndex = 34;
            this.button4.Text = "button4";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // Analysis
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(469, 474);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.checkedListBox1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textBox_csv);
            this.Controls.Add(this.btn_ClearTxt);
            this.Controls.Add(this.btn_createTb);
            this.Controls.Add(this.OutCsv);
            this.Controls.Add(this.textBoxSql);
            this.Controls.Add(this.textBoxTbNum);
            this.Controls.Add(this.TbsView);
            this.Controls.Add(this.OutMysql);
            this.Controls.Add(this.parseLog);
            this.Controls.Add(this.textBox_Log);
            this.Controls.Add(this.textBox_Xml);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Analysis";
            this.Text = "每日经分";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox textBox_Xml;
        private System.Windows.Forms.TextBox textBox_Log;
        private System.Windows.Forms.Button parseLog;
        private System.Windows.Forms.Button OutMysql;
        private System.Windows.Forms.TreeView TbsView;
        private System.Windows.Forms.TextBox textBoxTbNum;
        private System.Windows.Forms.TextBox textBoxSql;
        private System.Windows.Forms.Button OutCsv;
        private System.Windows.Forms.Button btn_createTb;
        private System.Windows.Forms.Button btn_ClearTxt;
        private System.Windows.Forms.TextBox textBox_csv;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.CheckedListBox checkedListBox1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Button button4;
    }
}

