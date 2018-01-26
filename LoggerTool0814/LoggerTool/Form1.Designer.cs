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
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.dataGridView2 = new System.Windows.Forms.DataGridView();
            this.textBox_Xml = new System.Windows.Forms.TextBox();
            this.loadXml = new System.Windows.Forms.Button();
            this.textBox_Log = new System.Windows.Forms.TextBox();
            this.parseLog = new System.Windows.Forms.Button();
            this.OutMysql = new System.Windows.Forms.Button();
            this.TbsView = new System.Windows.Forms.TreeView();
            this.textBoxTbNum = new System.Windows.Forms.TextBox();
            this.textBoxSql = new System.Windows.Forms.TextBox();
            this.btn_execSql = new System.Windows.Forms.Button();
            this.OutCsv = new System.Windows.Forms.Button();
            this.btn_createTb = new System.Windows.Forms.Button();
            this.btn_ClearTxt = new System.Windows.Forms.Button();
            this.textBox_csv = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(24, 70);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.Size = new System.Drawing.Size(858, 116);
            this.dataGridView1.TabIndex = 5;
            // 
            // dataGridView2
            // 
            this.dataGridView2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Location = new System.Drawing.Point(24, 192);
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.RowTemplate.Height = 23;
            this.dataGridView2.Size = new System.Drawing.Size(1053, 330);
            this.dataGridView2.TabIndex = 7;
            this.dataGridView2.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView2_CellContentClick);
            // 
            // textBox_Xml
            // 
            this.textBox_Xml.Location = new System.Drawing.Point(24, 3);
            this.textBox_Xml.Name = "textBox_Xml";
            this.textBox_Xml.Size = new System.Drawing.Size(438, 21);
            this.textBox_Xml.TabIndex = 11;
            this.textBox_Xml.Text = "E:/crossgate-server/binExe/GameWord/tlog_fields.xml";
            this.textBox_Xml.TextChanged += new System.EventHandler(this.textBox_Xml_TextChanged);
            // 
            // loadXml
            // 
            this.loadXml.Location = new System.Drawing.Point(483, 3);
            this.loadXml.Name = "loadXml";
            this.loadXml.Size = new System.Drawing.Size(75, 23);
            this.loadXml.TabIndex = 12;
            this.loadXml.Text = "loadXml";
            this.loadXml.UseVisualStyleBackColor = true;
            this.loadXml.Click += new System.EventHandler(this.loadXml_Click);
            // 
            // textBox_Log
            // 
            this.textBox_Log.Location = new System.Drawing.Point(24, 30);
            this.textBox_Log.Name = "textBox_Log";
            this.textBox_Log.Size = new System.Drawing.Size(438, 21);
            this.textBox_Log.TabIndex = 13;
            this.textBox_Log.Text = "E:/game.log";
            this.textBox_Log.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            // 
            // parseLog
            // 
            this.parseLog.Location = new System.Drawing.Point(483, 30);
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
            this.OutMysql.Location = new System.Drawing.Point(901, 70);
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
            this.TbsView.Location = new System.Drawing.Point(1102, 13);
            this.TbsView.Name = "TbsView";
            this.TbsView.Size = new System.Drawing.Size(121, 596);
            this.TbsView.TabIndex = 16;
            this.TbsView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.TbsView_AfterSelect);
            this.TbsView.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.TbsView_NodeMouseClick);
            // 
            // textBoxTbNum
            // 
            this.textBoxTbNum.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxTbNum.Location = new System.Drawing.Point(1041, 13);
            this.textBoxTbNum.Name = "textBoxTbNum";
            this.textBoxTbNum.Size = new System.Drawing.Size(56, 21);
            this.textBoxTbNum.TabIndex = 17;
            this.textBoxTbNum.Text = "表的个数";
            // 
            // textBoxSql
            // 
            this.textBoxSql.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxSql.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBoxSql.Location = new System.Drawing.Point(24, 528);
            this.textBoxSql.Multiline = true;
            this.textBoxSql.Name = "textBoxSql";
            this.textBoxSql.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBoxSql.Size = new System.Drawing.Size(925, 81);
            this.textBoxSql.TabIndex = 18;
            this.textBoxSql.Text = "ouptut  and exec mysql";
            this.textBoxSql.TextChanged += new System.EventHandler(this.textBoxSql_TextChanged);
            // 
            // btn_execSql
            // 
            this.btn_execSql.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_execSql.Location = new System.Drawing.Point(955, 556);
            this.btn_execSql.Name = "btn_execSql";
            this.btn_execSql.Size = new System.Drawing.Size(122, 23);
            this.btn_execSql.TabIndex = 19;
            this.btn_execSql.Text = "执行sql语句";
            this.btn_execSql.UseVisualStyleBackColor = true;
            this.btn_execSql.Click += new System.EventHandler(this.btn_execSql_Click);
            // 
            // OutCsv
            // 
            this.OutCsv.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.OutCsv.Location = new System.Drawing.Point(901, 28);
            this.OutCsv.Name = "OutCsv";
            this.OutCsv.Size = new System.Drawing.Size(75, 23);
            this.OutCsv.TabIndex = 20;
            this.OutCsv.Text = "导出csv";
            this.OutCsv.UseVisualStyleBackColor = true;
            this.OutCsv.Click += new System.EventHandler(this.OutCsv_Click);
            // 
            // btn_createTb
            // 
            this.btn_createTb.Location = new System.Drawing.Point(680, 1);
            this.btn_createTb.Name = "btn_createTb";
            this.btn_createTb.Size = new System.Drawing.Size(75, 23);
            this.btn_createTb.TabIndex = 21;
            this.btn_createTb.Text = "建mysql表";
            this.btn_createTb.UseVisualStyleBackColor = true;
            this.btn_createTb.Click += new System.EventHandler(this.btn_createTb_Click);
            // 
            // btn_ClearTxt
            // 
            this.btn_ClearTxt.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_ClearTxt.Location = new System.Drawing.Point(955, 528);
            this.btn_ClearTxt.Name = "btn_ClearTxt";
            this.btn_ClearTxt.Size = new System.Drawing.Size(122, 23);
            this.btn_ClearTxt.TabIndex = 22;
            this.btn_ClearTxt.Text = "清空";
            this.btn_ClearTxt.UseVisualStyleBackColor = true;
            this.btn_ClearTxt.Click += new System.EventHandler(this.btn_ClearTxt_Click);
            // 
            // textBox_csv
            // 
            this.textBox_csv.Location = new System.Drawing.Point(564, 30);
            this.textBox_csv.Name = "textBox_csv";
            this.textBox_csv.Size = new System.Drawing.Size(331, 21);
            this.textBox_csv.TabIndex = 23;
            this.textBox_csv.Text = "E:/logTables/";
            this.textBox_csv.TextChanged += new System.EventHandler(this.textBox_csv_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(771, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(227, 12);
            this.label1.TabIndex = 24;
            this.label1.Text = "在xml结构改变后，才需要点击此建表按钮";
            // 
            // Analysis
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1235, 621);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox_csv);
            this.Controls.Add(this.btn_ClearTxt);
            this.Controls.Add(this.btn_createTb);
            this.Controls.Add(this.OutCsv);
            this.Controls.Add(this.btn_execSql);
            this.Controls.Add(this.textBoxSql);
            this.Controls.Add(this.textBoxTbNum);
            this.Controls.Add(this.TbsView);
            this.Controls.Add(this.OutMysql);
            this.Controls.Add(this.parseLog);
            this.Controls.Add(this.textBox_Log);
            this.Controls.Add(this.loadXml);
            this.Controls.Add(this.textBox_Xml);
            this.Controls.Add(this.dataGridView2);
            this.Controls.Add(this.dataGridView1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Analysis";
            this.Text = "每日经分";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridView dataGridView2;
        private System.Windows.Forms.TextBox textBox_Xml;
        private System.Windows.Forms.Button loadXml;
        private System.Windows.Forms.TextBox textBox_Log;
        private System.Windows.Forms.Button parseLog;
        private System.Windows.Forms.Button OutMysql;
        private System.Windows.Forms.TreeView TbsView;
        private System.Windows.Forms.TextBox textBoxTbNum;
        private System.Windows.Forms.TextBox textBoxSql;
        private System.Windows.Forms.Button btn_execSql;
        private System.Windows.Forms.Button OutCsv;
        private System.Windows.Forms.Button btn_createTb;
        private System.Windows.Forms.Button btn_ClearTxt;
        private System.Windows.Forms.TextBox textBox_csv;
        private System.Windows.Forms.Label label1;
    }
}

