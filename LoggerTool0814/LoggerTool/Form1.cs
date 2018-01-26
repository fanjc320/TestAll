using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;
using System.IO;
using MySql.Data.MySqlClient;
using System.Diagnostics;

namespace LoggerTool
{
    using TBName = String;
    using fieldV = String;
    using fieldVList = List<String>;
    public struct stEntryNode
    {
        public string name;
        public string type;
        public int size;
        public string defaultvalue;
        public string desc;
    }
    public partial class Analysis : Form
    {
        Dictionary<TBName, List<stEntryNode>> m_AllxmlTables = new Dictionary<TBName, List<stEntryNode>>();
        Dictionary<TBName, DataTable> m_AlldtTables = new Dictionary<TBName, DataTable>();
        //List<string> tables = new List<string>();
        private static string constr = "Server=127.0.0.1;User Id=root;password=123456;Database=test1";
        static string xmlPath = "E:/tlog_fields.xml";
        //static string logPath = "E:/crossgate-server/binExe/server/GameWorld/log/game.log";
        static string logPath = "E:/game.log";
        static string CSVPATH = "E:/logTables/";
        static string SavePath = "C:/LoggerTool.txt";
        //static string logPath = "E:/crossgate-server/binExe/GameWord/log/game.log";
        //private DataSet dsall;
        //private static String mysqlcon = "database=test;Password=你的密码;User ID=你的用户名;server=你的ip地址";//Data Source=MySQL;;charset=utf8";
        //private MySqlConnection conn;
        //private MySqlDataAdapter mDataAdapter;
        MySqlConnection mycon = new MySqlConnection(constr);
        DataSet dataset = new DataSet();
        MySqlDataAdapter msqadapter;
        string tablename = "office";
        public Analysis()
        {
            InitializeComponent();
            mycon.Open();
            msqadapter = new MySqlDataAdapter("select * from items", mycon);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: 这行代码将数据加载到表“testDataSet.office”中。您可以根据需要移动或删除它。
            //this.officeTableAdapter.Fill(this.testDataSet.office);
            textBox_Xml.Text = xmlPath;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //using (MySqlConnection mycon = new MySqlConnection(constr))
            //{
            //string mysql = "select * from userspassword_table where usersName= '" + textBox1.Text.Trim() + "' and password = '" + textBox2.Text.Trim() + "' ";
            string mysql = "select * from office ; ";

            mycon.Open();

            MySqlDataAdapter da = new MySqlDataAdapter(mysql, mycon);

            DataTable ds = new DataTable();

            da.Fill(ds);

            if (ds.Rows.Count > 0)
            {
                MessageBox.Show("登录成功");
                this.Hide();//隐藏登录窗体 
            }
            else
            {
                MessageBox.Show("登录失败");

            }
            //}
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            mycon.Close();
        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            //mycon.Open();
            msqadapter.SelectCommand.CommandText = string.Format("select * from {0}", tablename);
            //msqadapter.SelectCommand.Connection = mycon;
            //msqda.SelectCommand = new MySqlCommand("select * from office");
            msqadapter.Fill(dataset, tablename);
            dataGridView1.DataSource = dataset.Tables[tablename];
            //dataGridView1.DataMember = tablename;

            MySqlConnection mycon2 = new MySqlConnection(constr);
            mycon2.Open();

            DataSet dataset2 = new DataSet();
            string sqlstr = string.Format("select * from {0}", tablename);
            MySqlDataAdapter msqadapter2 = new MySqlDataAdapter(sqlstr, mycon2);
            msqadapter2.Fill(dataset2, tablename);
            dataGridView2.DataSource = dataset2.Tables[tablename];
            //dataGridView2.DataMember = tablename;

            mycon2.Close();
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            TextBox txt = (TextBox)sender;
            tablename = txt.Text;
            logPath = txt.Text;
        }

        private void loadXml_Click(object sender, EventArgs e)
        {
            XmlDocument xmlDoc = new XmlDocument();

            XmlReaderSettings settings = new XmlReaderSettings();
            settings.IgnoreComments = true;//忽略文档里面的注释
            XmlReader reader = XmlReader.Create(xmlPath, settings);
            xmlDoc.Load(reader);
            reader.Close();

            XmlNode xn = xmlDoc.SelectSingleNode("metalib");
            XmlNodeList xnl = xn.ChildNodes;

            m_AllxmlTables.Clear();
            foreach (XmlNode xn1 in xnl)
            {
                XmlElement xe = (XmlElement)xn1;
                string tablename = "";
                if (xe.Name == "struct")
                {
                    tablename = xe.GetAttribute("name").ToString();
                    //tables.Add(tablename);

                    List<stEntryNode> nodes = new List<stEntryNode>();
                    foreach (XmlElement xei in xe)//entry
                    {
                        string fieldname = xei.GetAttribute("name").ToString();
                        string type = xei.GetAttribute("type").ToString();
                        string size = xei.GetAttribute("size").ToString();
                        string defaultvalue = xei.GetAttribute("defaultvalue").ToString();
                        string desc = xei.GetAttribute("desc").ToString();
                        stEntryNode node = new stEntryNode();
                        node.name = fieldname;
                        node.type = type;
                        if (size != "")
                            node.size = Convert.ToInt32(size);
                        node.defaultvalue = defaultvalue;
                        node.desc = desc;

                        nodes.Add(node);
                    }
                    m_AllxmlTables.Add(tablename, nodes);

                }
                // 得到所有子节点
                //XmlNodeList xnl0 = xe.ChildNodes;
                //bookModel.BookName = xnl0.Item(0).InnerText;
                //bookModel.BookPrice = Convert.ToDouble(xnl0.Item(2).InnerText);
            }

            TbsView.Nodes.Clear();
            foreach (var val in m_AllxmlTables.Keys)
            {
                TreeNode tree = new TreeNode();
                tree.Name = val;
                tree.Text = val;
                TbsView.Nodes.Add(tree);
            }

            textBoxTbNum.Text = m_AllxmlTables.Count.ToString();
        }
        /*
        void InstanceMgr::ReloadTLog(bool aupdateline)
        {
            cout << "ReloadTLog" << endl;
            string data;
            //ifstream map("game.log.0629");
            ifstream map("qqq.txt");
            if (!map.is_open())
            {
                sLog.outError("LoadJsonFile", "LoadJsonFile no find (%s)", "game.log");
                return;
            }
            char buffer[4096];
            uint32 nub = 1;
            while (!map.eof())
            {
                map.getline(buffer, 4096);
                data = buffer;
                std::vector < std::string> datelist = StrSplit(data, "|");
                if (datelist.size() <= 8)
                    continue;
                RLogData ldata;
                ldata.CmdStr = datelist[0];
                ldata.OpenId = datelist[7];
                for (uint32 i = 9; i < datelist.size(); i++)
                {
                    ldata.datalist.push_back(datelist[i]);
                }
                m_LogMap[ldata.OpenId][ldata.CmdStr].push_back(ldata);
                nub++;
                //	if (nub > 10000) break;
            }
            cout << "ReloadTLog end" << endl;
        }*/
        private void parseLog_Click(object sender, EventArgs e)
        {
            Array tbNames = m_AllxmlTables.Keys.ToArray<TBName>();
            if (tbNames.Length == 0)
            {
                MessageBox.Show("请先点击loadXml!");
                return;
            }
            Dictionary<TBName, List<fieldVList>> AlllogTables = new Dictionary<TBName, List<fieldVList>>();
            //初始化key值
            for (int i = 0; i < tbNames.Length; ++i)
            {
                AlllogTables[(TBName)tbNames.GetValue(i)] = new List<fieldVList>();
            }
            //Debug.Assert(xmlTables.Count>0,"请先loadXml!");
            int alllines = 0;

            //for (int k=0;k<7;++k)
            //{
            StreamReader sr = null;
            try
            {
                //logPath = string.Format("E:/xa{0}",'a');
                FileStream fs = new FileStream(logPath, FileMode.Open, FileAccess.ReadWrite);
                sr = new StreamReader(fs, System.Text.Encoding.GetEncoding(936));
            }
            catch (Exception)
            {
                if (sr != null) sr.Close();
                MessageBox.Show("无法打开文件，请检查此文件是否被其他程序占用!");
                return;
            }

            string str = "";
            //string s = Console.ReadLine();
            TBName tb = "";

            int lines = 0;
            while ((str = sr.ReadLine()) != null)
            {
                fieldVList fvls = new fieldVList();

                ++lines;
                if (lines > 1000000)
                {
                    //sr.DiscardBufferedData();//会出错
                    lines = 0;
                }
                ++alllines;
                //fvls.Clear();
                string[] fields = str.Split('|');
                Debug.Assert(fields.Length > 2);
                tb = fields[0];

                for (int i = 1; i < fields.Length; ++i)
                {
                    fvls.Add(fields[i]);
                }
                if (AlllogTables.ContainsKey(tb))
                {
                    AlllogTables[tb].Add(fvls);
                }
                else
                {
                    AlllogTables[tb] = new List<fieldVList>();
                    AlllogTables[tb].Add(fvls);
                }
            }
            textBoxSql.AppendText(string.Format("-----------------已将log文件解析为字典!-共{0}个table-{1}行-\n", AlllogTables.Count, alllines));

            sr.Close();
            //}

            m_AlldtTables.Clear();
            //int alllines = 0;
            foreach (var item in AlllogTables)
            {
                TBName tbname = item.Key;
                DataTable dt = new DataTable(tbname);
                for (int i = 0; i < m_AllxmlTables[tbname].Count; ++i)
                {
                    string columname = m_AllxmlTables[tbname][i].name;
                    dt.Columns.Add(m_AllxmlTables[tbname][i].name);
                    dt.Columns[i].ColumnName = m_AllxmlTables[tbname][i].name;
                }
                int bupipei = 0;
                for (int i = 0; i < AlllogTables[tbname].Count; ++i)
                {
                    ++alllines;
                    fieldVList ls = AlllogTables[tbname][i];
                    List<stEntryNode> st = m_AllxmlTables[tbname];
                    if (st.Count != ls.Count && bupipei == 0)
                    {
                        ++bupipei;
                        textBoxSql.AppendText(string.Format("{0} xml字段个数:{1} log字段个数:{2}\n", tbname, st.Count, ls.Count));
                        //MessageBox.Show(string.Format("{0}表字段个数xml与log不匹配 bupipei{1}", tbname,bupipei));
                    }
                    //Console.WriteLine(ls.Count);
                    DataRow dr;
                    dr = dt.NewRow();
                    for (int j = 0; j < ls.Count && j < dr.ItemArray.Length; ++j)
                    {
                        dr[j] = ls[j];
                    }
                    dt.Rows.Add(dr);
                }
                if(tbname.Contains("sec")||tbname.Contains("Sec"))
                {

                }
                else
                {
                    m_AlldtTables.Add(tbname, dt);
                }
            }

            textBoxSql.AppendText(string.Format("-----------------已将字典解析为DataTable!-共{0}条记录,{1}个table-\n", alllines, m_AlldtTables.Count));

        }

        private void textBox_Xml_TextChanged(object sender, EventArgs e)
        {
            xmlPath = ((TextBox)sender).Text;
        }

        private void textBox_Log_TextChanged(object sender, EventArgs e)
        {
            logPath = ((TextBox)sender).Text;
        }
        public int updateDataTable(string db_string, DataTable db_datatable)
        {
            int ret = -1;
            MySqlConnection db_conn = new MySqlConnection(constr);
            MySqlDataAdapter adapter = new MySqlDataAdapter(db_string, db_conn);
            MySqlCommandBuilder builder = new MySqlCommandBuilder(adapter);
            ret = adapter.Update(db_datatable);
            return ret;
        }
        private void OutMysql_Click(object sender, EventArgs e)
        {
            if (m_AlldtTables.Count == 0)
            {
                MessageBox.Show("请先点击parseLog按钮!");
                return;
            }

            foreach (var val in m_AlldtTables)
            {
                DataTable dt = val.Value;
                if (dt != null)
                {
                    int count = BulkInsert(constr, dt);
                    textBoxSql.AppendText(string.Format("{0}导入{1}条数据\n", dt.TableName, count));
                }
            }
            textBoxSql.AppendText(string.Format("-----------------导出数据到mysql成功\n"));
        }

        private void TbsView_AfterSelect(object sender, TreeViewEventArgs e)
        {
        }

        private void TbsView_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            TBName tbname = e.Node.Text;

            if (m_AlldtTables.Count != 0)
            {
                DataTable dt = m_AlldtTables[tbname];

                dataGridView2.DataSource = dt;
            }
            else
            {
                MessageBox.Show("请先点击解析按钮!");
            }

        }

        private void textBoxSql_TextChanged(object sender, EventArgs e)
        {

        }

        private void btn_execSql_Click(object sender, EventArgs e)
        {
            string strSql = textBoxSql.Text;

            MySqlConnection connection = new MySqlConnection(constr);
            connection.Open();
            MySqlCommand command = connection.CreateCommand();
            command.CommandType = CommandType.Text;
            command.CommandText = textBoxSql.Text;
            MySqlDataAdapter adapter = new MySqlDataAdapter(command);

            int test = command.ExecuteNonQuery();

            DataTable dt = new DataTable();

            adapter.Fill(dt);

            if (dt.Rows.Count > 0)
            {
                MessageBox.Show("执行sql成功!");
                dataGridView2.DataSource = dt;
            }
        }

        private void OutCsv_Click(object sender, EventArgs e)
        {
            if (!System.IO.Directory.Exists(CSVPATH))
            {
                System.IO.Directory.CreateDirectory(CSVPATH);//不存在就创建文件夹 } 
            }

            if (m_AlldtTables.Count == 0)
            {
                MessageBox.Show("请先点击解析按钮");
                return;
            }
            textBoxSql.AppendText(string.Format("m_AlldtTables.Count:{0}\n", m_AlldtTables.Count));

            int count = 0;
            int alllines = 0;
            foreach (var item in m_AlldtTables)
            {
                TBName tbname = item.Key;
                List<stEntryNode> fls = m_AllxmlTables[tbname];
                DataTable dt = item.Value;
                DataRow dr0 = dt.NewRow();
                DataRow dr1 = dt.NewRow();
                for (int i = 0; i < fls.Count; ++i)
                {
                    //dt.Columns[i].ColumnName = fls[i].name;
                    dr0[i] = fls[i].name;
                    dr1[i] = fls[i].desc;
                }
                dt.Rows.InsertAt(dr0, 0);
                dt.Rows.InsertAt(dr1, 1);
                //string csvPath = string.Format("{0}{1}.csv",CSVPATH, tbname);
                int rows = DataTableToCsv(ref dt);
                //File.WriteAllText(csvPath, csv);
                ++count;
                alllines += rows;
                textBoxSql.AppendText(string.Format("已导出{0}.csv  第{1}个\n  共{2}条记录\n", tbname, count, rows));
                //dt.Rows.RemoveAt(0);
                //dt.Rows.RemoveAt(0);
            }
            textBoxSql.AppendText(string.Format("-----------------DataTable导出全部csv文件成功!-共{0}条记录-\n", alllines));
        }

        ///将DataTable转换为标准的CSV
        private static int DataTableToCsv(ref DataTable table)
        {
            //以半角逗号（即,）作分隔符，列为空也要表达其存在。
            //列内容如存在半角逗号（即,）则用半角引号（即""）将该字段值包含起来。
            //列内容如存在半角引号（即"）则应替换成半角双引号（""）转义，并用半角引号（即""）将该字段值包含起来。
            StringBuilder sb = new StringBuilder();
            //FileStream fs = new FileStream();
            DataColumn colum;
            int lines = 0;
            string csvPath = string.Format("{0}{1}.csv", CSVPATH, table.TableName);
            int rows = 0;
            foreach (DataRow row in table.Rows)
            {
                for (int i = 0; i < table.Columns.Count; i++)
                {
                    colum = table.Columns[i];
                    if (i != 0) sb.Append(",");
                    if (colum.DataType == typeof(string) && row[colum].ToString().Contains(","))
                    {
                        sb.Append("\"" + row[colum].ToString().Replace("\"", "\"\"") + "\"");
                    }
                    else sb.Append(row[colum].ToString());
                }
                sb.AppendLine();
                ++lines;
                ++rows;
                if (lines > 10000)
                {
                    Console.WriteLine("--->10000--table:{0} length:{1}", table.TableName, sb.Length);
                    File.WriteAllText(csvPath, sb.ToString());
                    sb.Clear();
                    lines = 0;
                }
            }
            Console.WriteLine("table:{0} length:{1}", table.TableName, sb.Length);
            File.WriteAllText(csvPath, sb.ToString());
            //return sb.ToString();
            return rows;
        }
        /// <summary>
        ///大批量数据插入,返回成功插入行数
        public /*static*/ int BulkInsert(string connectionString, DataTable table)
        {
            //if (table.TableName!="Activity")
            //{
            //    return 0;
            //}
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("truncate TABLE  `{0}`;", table.TableName);
            
            MySqlCommand command = mycon.CreateCommand();
            command.CommandType = CommandType.Text;
            command.CommandText = sb.ToString();
            command.ExecuteNonQuery();

            if (string.IsNullOrEmpty(table.TableName)) throw new Exception("请给DataTable的TableName属性附上表名称");
            if (table.Rows.Count == 0) return 0;
            int insertCount = 0;
            string tmpPath = string.Format("{0}{1}.csv", CSVPATH, table.TableName);
            //string csv = DataTableToCsv(table);
            //File.WriteAllText(tmpPath, csv);

            if (!File.Exists(tmpPath))
            {
                textBoxSql.AppendText(string.Format("@@@@@@@@@@@@@ error:{0}不存在", tmpPath));
                return -1;
            }
            
            using (MySqlConnection conn = new MySqlConnection(connectionString))
            {
                MySqlTransaction tran = null;
                try
                {
                    conn.Open();

                    tran = conn.BeginTransaction();
                    MySqlBulkLoader bulk = new MySqlBulkLoader(conn)
                    {
                        FieldTerminator = ",",
                        FieldQuotationCharacter = '"',
                        EscapeCharacter = '"',
                        LineTerminator = "\r\n",
                        FileName = tmpPath,
                        NumberOfLinesToSkip = 2,
                        TableName = table.TableName,
                    };
                    bulk.Columns.Clear();
                    List<TBName> tblist = table.Columns.Cast<DataColumn>().Select(colum => colum.ColumnName).ToList();
                    bulk.Columns.AddRange(table.Columns.Cast<DataColumn>().Select(colum => colum.ColumnName).ToList());
                    insertCount = bulk.Load();

                    tran.Commit();
                }
                catch (MySqlException ex)
                {
                    string ss = "解析数据表出错！tableName: " + table.TableName + " field: "+ ex.ToString();
                    MessageBox.Show(ss);
                    //if (tran != null) tran.Rollback();
                    //throw ex;
                }
            }
            //File.Delete(tmpPath);
            return insertCount;
        }

        public static void BatchUpdate(DataTable table)
        {

            MySqlConnection connection = new MySqlConnection(constr);
            MySqlCommand command = connection.CreateCommand();
            command.CommandType = CommandType.Text;
            MySqlDataAdapter adapter = new MySqlDataAdapter(command);
            MySqlCommandBuilder commandBulider = new MySqlCommandBuilder(adapter);
            commandBulider.ConflictOption = ConflictOption.OverwriteChanges;

            MySqlTransaction transaction = null;
            try
            {
                connection.Open();
                transaction = connection.BeginTransaction();
                //设置批量更新的每次处理条数
                //adapter.UpdateBatchSize = BatchSize;
                //设置事物
                adapter.SelectCommand.Transaction = transaction;

                if (table.ExtendedProperties["SQL"] != null)
                {
                    adapter.SelectCommand.CommandText = table.ExtendedProperties["SQL"].ToString();
                    //adapter.InsertCommand.CommandText = table.ExtendedProperties["SQL"].ToString();
                    //adapter.SelectCommand.CommandText = "select runoob_id from runoob_tbl";
                }
                adapter.Update(table);
                transaction.Commit();/////提交事务
            }
            catch (MySqlException ex)
            {
                if (transaction != null) transaction.Rollback();
                throw ex;
            }
            finally
            {
                connection.Close();
                connection.Dispose();
            }
        }

        void InsertDiece(string connectionString, string tableName, int count)
        {
            var commandText = String.Format("INSERT INTO `{0}` (Dice1, Dice2) Values (@dice1, @dice2)", tableName);
            using (var connection = new MySqlConnection(constr))
            using (var command = connection.CreateCommand())
            {
                connection.Open();
                command.CommandText = commandText;
                for (int i = 0; i < count; i++)
                {
                    command.Parameters.AddWithValue("@dice1", 111);
                    command.Parameters.AddWithValue("@dice2", 222);
                    command.ExecuteNonQuery();
                    command.Parameters.Clear();
                }
            }
        }

        private void btn_createTb_Click(object sender, EventArgs e)
        {

            CreateMysqlTbByXml();
            textBoxSql.AppendText("-----------------创建所有mysql数据表成功\n");
        }

        private void btn_ClearTxt_Click(object sender, EventArgs e)
        {
            textBoxSql.Text = "";
        }

        private void CreateMysqlTbByXml()
        {
            //MySqlConnection connection = new MySqlConnection(constr);
            //MySqlCommand command = connection.CreateCommand();
            //command.CommandType = CommandType.Text;
            //MySqlDataAdapter adapter = new MySqlDataAdapter(command);
            //MySqlCommandBuilder commandBulider = new MySqlCommandBuilder(adapter);
            //commandBulider.ConflictOption = ConflictOption.OverwriteChanges;
            //connection.Open();
            foreach (var st_p in m_AllxmlTables)
            {
                if(st_p.Key.Contains("sec")|| st_p.Key.Contains("Sec"))
                {
                    continue;
                }
                StringBuilder sb = new StringBuilder();
                sb.AppendFormat("DROP TABLE IF EXISTS `{0}`;", st_p.Key);

                MySqlCommand command = mycon.CreateCommand();
                command.CommandType = CommandType.Text;
                command.CommandText = sb.ToString();

                command.ExecuteNonQuery();

                sb.Clear();
                sb.AppendFormat("create TABLE `{0}` (id INT UNSIGNED AUTO_INCREMENT,PRIMARY KEY (id))ENGINE = InnoDB DEFAULT CHARSET = utf8 ;", st_p.Key);
                command.CommandText = sb.ToString();
                command.ExecuteNonQuery();
                List<stEntryNode> ls = st_p.Value;
                for (int i = 0; i < ls.Count; ++i)
                {
                    stEntryNode st = ls[i];
                    sb.Clear();
                    string s_type = "varchar";
                    switch(st.type)
                    {
                        case "string":
                            s_type = "varchar(100)";
                            break;
                        case "datetime":
                            s_type = "datetime";
                            break;
                        case "int":
                            s_type = "int";
                            break;
                        case "bigint":
                            s_type = "bigint";
                            break;
                        case "float":
                            s_type = "float";
                            break;
                        default :
                            MessageBox.Show(string.Format("未知类型:{0}",s_type));
                            break;

                    }
                    //sb.AppendFormat("alter table {0} add {1} VARCHAR(100)", st_p.Key, st.name);
                    sb.AppendFormat("alter table {0} add {1} {2}", st_p.Key, st.name,s_type);
                    command.CommandText = sb.ToString();
                    command.ExecuteNonQuery();
                }
                textBoxSql.AppendText(string.Format("创建mysql表{0}    ok!\n", st_p.Key));
            }
        }
        private void CreateMysqlTb(DataTable dt)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("DROP TABLE IF EXISTS `{0}`;", dt.TableName);

            //MySqlCommand command = connection.CreateCommand();
            MySqlCommand command = mycon.CreateCommand();
            command.CommandType = CommandType.Text;
            command.CommandText = sb.ToString();
            //MySqlDataAdapter adapter = new MySqlDataAdapter(command);

            command.ExecuteNonQuery();

            sb.Clear();
            sb.AppendFormat("create TABLE `{0}` (id INT UNSIGNED)ENGINE = InnoDB DEFAULT CHARSET = utf8 ;", dt.TableName);
            command.CommandText = sb.ToString();
            command.ExecuteNonQuery();

            for (int i = 0; i < dt.Columns.Count; ++i)
            {
                sb.Clear();
                sb.AppendFormat("alter table {0} add {1} VARCHAR(100)", dt.TableName, dt.Columns[i].ColumnName);
                command.CommandText = sb.ToString();
                command.ExecuteNonQuery();
            }

        }

        private void textBox_csv_TextChanged(object sender, EventArgs e)
        {
            CSVPATH = ((TextBox)sender).Text;
        }
    }
}

/*
            DataSource可以是任何System.Collections.IEnumerable对象
比如：DataView
DataSet
            一些集合等等。
            你自己也可以写一个类实现IEnumerable接口。

            DataTable orders = ds.Tables["SalesOrderHeader"];

            //查询SalesOrderHeader表中2001年8月以后的订单

            IEnumerable<DataRow> query = from order in orders.AsEnumerable()

                                         where order.Field<DateTime>("OrderDate") > new DateTime(2001, 8, 1)

                                         select order;

            //用CopyToDataTable方法从查询生成表

            DataTable boundTable = query.CopyToDataTable<DataRow>();

            //绑定表作为BindingSource的数据源对象

            bindingSource1.DataSource = boundTable;

            dataGridView1.AutoResizeColumns();

            dataGridView1.DataSource = bindingSource1;
            */
