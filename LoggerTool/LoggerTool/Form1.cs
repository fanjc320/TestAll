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
using MySqlMgr;
using System.Runtime.InteropServices;
using System.Threading;

//using DocDetector.Core.Extensions;

namespace LoggerTool
{
    using TBName = String;
    using fieldV = String;
    using fieldVList = List<String>;
    using System.Configuration;

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
        FileSystemWatcher fileSystemWatcher1 = new FileSystemWatcher();
        private static string constr = ConfigurationManager.AppSettings["mysql"];
        static string xmlPath = ConfigurationManager.AppSettings["xmlPath"];
        static string logPath = ConfigurationManager.AppSettings["logPath"];
        static string CSVPATH = ConfigurationManager.AppSettings["CsvPath"];
        static string Uids = "";
        MySqlConnection mycon = new MySqlConnection(constr);
        //DataSet dataset = new DataSet();
        //MySqlDataAdapter msqadapter;
        int m_CurLine = 0;
        bool m_Parsed = false;
        TBName m_CurTb;
        Dictionary<TBName, Dictionary<string, bool>> m_Selected = new Dictionary<TBName, Dictionary<string, bool>>();
        List<string> m_CurSelected = new List<string>();
        TreeNode node = null;//全局变量,保存TreeView当前节点
        FileStream fs = null;
        StreamReader sr = null;
        public class NativeMethods
        {

            /// <summary>
            /// 启动控制台
            /// </summary>
            /// <returns></returns>
            [DllImport("kernel32.dll")]
            public static extern bool AllocConsole();
            /// <summary>
            /// 释放控制台
            /// </summary>
            /// <returns></returns>
            [DllImport("kernel32.dll")]
            public static extern bool FreeConsole();

        }
        public Analysis()
        {
            InitializeComponent();
            //开启控制台
            NativeMethods.AllocConsole();
            Console.WriteLine("hello");
            //Console.OutputEncoding = System.Text.Encoding.UTF8;
            //Control.CheckForIllegalCrossThreadCalls = false;//禁止编译器对跨线程访问做检查,不推荐
            try
            {
                mycon.Open();
            }
            catch
            {
                MessageBox.Show("打开数据库失败，请检查配置！");
                return;
            }

            Init();
        }

        private void Init()
        {
            //this.fileSystemWatcher1.Created += new FileSystemEventHandler(fileSystemWatcher1_Created);
            //this.fileSystemWatcher1.Changed += new FileSystemEventHandler(fileSystemWatcher1_Changed);

            //this.fileSystemWatcher1.Path = "E:/";
            //this.fileSystemWatcher1.EnableRaisingEvents = true;
            //this.fileSystemWatcher1.Filter = "*.log";
            //this.fileSystemWatcher1.IncludeSubdirectories = false;//不监视子目录

            loadXml_Click(null, null);

            foreach (var val in m_AllxmlTables.Keys)
            {
                StringBuilder sb = new StringBuilder();
                sb.AppendFormat("truncate TABLE  `{0}`;", val);

                try
                {
                    MySqlCommand command = mycon.CreateCommand();
                    command.CommandType = CommandType.Text;
                    command.CommandText = sb.ToString();
                    command.ExecuteNonQuery();
                }
                catch (Exception)
                {

                }
            }
            checkedListBox1.CheckOnClick = true;
            TbsView.HideSelection = false;
            
            //Timer timer = new Timer();
            //timer.Interval = 2000;
            //timer.Tick += new System.EventHandler(timer_Tick);
            //timer.Start();

            Thread newThread = new Thread(()=>parseLog_Click(null,null));
            newThread.Start();
        }

        private void fileSystemWatcher1_Changed(object sender, System.IO.FileSystemEventArgs e)
        {
            if (e.FullPath == logPath)
            {
                MessageBox.Show("fileSystemWatcher1_Changed！");
            }
            //parseLog_Click(sender, e);
        }
        private void timer_Tick(object sender, System.EventArgs e)
        {
            DateTime begin = DateTime.Now;
            TimeSpan span = DateTime.Now - begin;
            if (!m_Parsed)
            {
                parseLog_Click(sender, e);
            }
            textBoxSql.AppendText(string.Format("###################### parseLog_End 耗时：{0}秒\n", span.Seconds));
            m_Parsed = true;
        }

        private void fileSystemWatcher1_Created(object sender, System.IO.FileSystemEventArgs e)
        {
            if (e.FullPath == "目标文件")
            {
                //监视到目标文件被创建
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            textBox_Xml.Text = xmlPath;
            textBox_Log.Text = logPath;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            TextBox txt = (TextBox)sender;
        }

        private void loadXml_Click(object sender, EventArgs e)
        {
            XmlDocument xmlDoc = new XmlDocument();

            XmlReaderSettings settings = new XmlReaderSettings();
            settings.IgnoreComments = true;//忽略文档里面的注释
            XmlReader reader = XmlReader.Create(xmlPath, settings);
            if (reader == null)
            {
                MessageBox.Show("请检查xml文件路径！");
                return;
            }
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
        Dictionary<TBName, List<fieldVList>> AlllogTables = new Dictionary<TBName, List<fieldVList>>();

        private void parseLog_Click(object sender, EventArgs e)
        {
            DateTime begin = DateTime.Now;
            Array tbNames = m_AllxmlTables.Keys.ToArray<TBName>();
            if (tbNames.Length == 0)
            {
                MessageBox.Show("loadXml error!");
                return;
            }
            
            try
            {
                fs = new FileStream(logPath, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
                sr = new StreamReader(fs, System.Text.Encoding.Default);
                if (fs.CanSeek)
                {
                    //fs.Seek(0, SeekOrigin.Begin);
                }

            }
            catch (Exception)
            {
                if (sr != null) sr.Close();
                MessageBox.Show("无法打开文件，请检查此文件是否被其他程序占用!");
                return;
            }

            string str = "";
            TBName tb = "";

            //while ((str = sr.ReadLine()) != null)
            bool b_parsed = false;
            int alllines = 0;
            while (true)
            {
                str = sr.ReadLine();
                if (str == null)
                {
                    if(!b_parsed)
                    {
                        Parselog();
                        AlllogTables.Clear();
                        if(!m_Parsed)
                        {
                            TimeSpan span = DateTime.Now - begin;
                            Console.WriteLine(string.Format("###################### parseLog_End 耗时：{0}秒",span.Seconds));
                        }
                        Console.ForegroundColor = ConsoleColor.Yellow;
                        m_Parsed = true;
                    }

                    b_parsed = true;
                    continue;
                }
                b_parsed = false;
                
                string[] fields = str.Split('|');
                Debug.Assert(fields.Length > 2);
                tb = fields[0];
                fieldVList fvls = new fieldVList();

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
                ++alllines;

                //Console.WriteLine(string.Format("alllines:{0} count:{1}",alllines,AlllogTables.Count));
            }
        }
        void Parselog()
        {
            //m_AlldtTables.Clear();
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
                    fieldVList ls = AlllogTables[tbname][i];
                    List<stEntryNode> st = m_AllxmlTables[tbname];
                    if (st.Count != ls.Count && bupipei == 0)
                    {
                        ++bupipei;
                        //textBoxSql.AppendText(string.Format("~~~~不匹配error:{0} xml字段个数:{1} log字段个数:{2}\n", tbname, st.Count, ls.Count));

                    }

                    StringBuilder s_out = new StringBuilder();

                    DataRow dr;
                    dr = dt.NewRow();
                    for (int j = 0; j < ls.Count && j < dr.ItemArray.Length; ++j)
                    {
                        dr[j] = ls[j];
                        if (m_Parsed)
                        {
                            s_out.AppendFormat("{0}:{1}|", dt.Columns[j].ColumnName, ls[j]);
                        }
                    }
                    dt.Rows.Add(dr);

                    ++m_CurLine;

                    if (m_Parsed)
                    {
                        Console.WriteLine(string.Format("{0}:{1}", dt.TableName, ParseOutStr(s_out.ToString())));
                        //richTextBox1.AppendTextColorful(string.Format("{0}:{1}\n", dt.TableName, ParseOutStr(s_out.ToString())),Color.Red);
                        //AppendTextColorful(string.Format("{0}:{1}\n", dt.TableName, ParseOutStr(s_out.ToString())),Color.Olive);
                    }
                }
                if (tbname.Contains("sec") || tbname.Contains("Sec"))
                {

                }
                else
                {
                    //m_AlldtTables.Add(tbname, dt);

                    if (dt != null)
                    {

                        MySqlDbHelper helper = new MySqlDbHelper();
                        helper.InsertByDataTable(ref dt);

                        //textBoxSql.AppendText(string.Format("{0}导入行数：{1}\n", dt.TableName, dt.Rows.Count));
                        //Console.WriteLine(string.Format("{0}导入行数：{1}", dt.TableName, dt.Rows.Count));
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.WriteLine(string.Format("**当前行数：{0}", m_CurLine));
                        //richTextBox1.AppendTextColorful(string.Format("{0}导入行数：{1}", dt.TableName, dt.Rows.Count),Color.Green);
                    }
                }
            }

        }

        string ParseOutStr(string s_out)
        {
            bool flag = false;
            if (Uids.Length > 0)
            {
                string[] uids = Uids.Split(';');

                foreach (string uid in uids)
                {
                    if (s_out.Contains(uid))
                    {
                        flag = true;
                    }
                }
            }
            else
            {
                flag = true;
            }
            string s_parsed = "";
            if (flag)
            {
                foreach (string s in s_out.Split('|'))
                {
                    string[] kv = s.Split(':');
                    if (m_CurSelected.Contains(kv[0]))
                    {
                        s_parsed += s;
                        s_parsed += "|";
                    }
                }
                if (s_parsed.Length > 0)
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    return s_parsed;
                }
                else
                {
                    Console.ForegroundColor = ConsoleColor.White;
                    return s_out;
                }
            }
            else
            {
                return "";
            }
        }

        private void textBox_Xml_TextChanged(object sender, EventArgs e)
        {
            xmlPath = ((TextBox)sender).Text;
        }
        private void OutMysql_Click(object sender, EventArgs e)
        {
            loadXml_Click(sender, e);
            parseLog_Click(sender, e);

            DateTime begin = DateTime.Now;
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
                    //int count = BulkInsert(constr, dt);
                    //textBoxSql.AppendText(string.Format("{0}导入{1}条数据\n", dt.TableName, count));

                    MySqlDbHelper helper = new MySqlDbHelper();
                    helper.InsertByDataTable(ref dt);

                    textBoxSql.AppendText(string.Format("{0}导入数据库\n", dt.TableName));
                }
            }
            TimeSpan span = DateTime.Now - begin;
            textBoxSql.AppendText(string.Format("-----------------导入数据到mysql成功,用时：{0}｝\n", span.Seconds));
        }

        private void TbsView_AfterSelect(object sender, TreeViewEventArgs e)
        {

            if (node != null)
            {
                node.BackColor = SystemColors.Window;//上次选择的节点恢复到默认背景色
            }
            e.Node.BackColor = SystemColors.ActiveCaption;//当前选择的节点激活背景色
            node = e.Node;//更新当前节点
        }

        private void TbsView_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            checkedListBox1.Items.Clear();
            TBName tbname = e.Node.Text;
            m_CurTb = tbname;
            DataTable dt = new DataTable(tbname);
            for (int i = 0; i < m_AllxmlTables[tbname].Count; ++i)
            {
                string columname = m_AllxmlTables[tbname][i].name;
                checkedListBox1.Items.Add(columname);
            }
        }

        private void textBoxSql_TextChanged(object sender, EventArgs e)
        {

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
                    //textBoxSql.AppendText(string.Format("--->10000--table:{0} length:{1}", table.TableName, sb.Length));
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

            try
            {
                MySqlCommand command = mycon.CreateCommand();
                command.CommandType = CommandType.Text;
                command.CommandText = sb.ToString();
                command.ExecuteNonQuery();
            }
            catch
            {
                MessageBox.Show("数据导入mysql失败！表：%s", table.TableName);
            }


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
                    string ss = "解析数据表出错！tableName: " + table.TableName + " field: " + ex.ToString();
                    MessageBox.Show(ss);
                    //if (tran != null) tran.Rollback();
                    //throw ex;
                }
            }
            //File.Delete(tmpPath);
            return insertCount;
        }

        //public static void BatchUpdate(DataTable table)
        //{

        //    MySqlConnection connection = new MySqlConnection(constr);
        //    MySqlCommand command = connection.CreateCommand();
        //    command.CommandType = CommandType.Text;
        //    MySqlDataAdapter adapter = new MySqlDataAdapter(command);
        //    MySqlCommandBuilder commandBulider = new MySqlCommandBuilder(adapter);
        //    commandBulider.ConflictOption = ConflictOption.OverwriteChanges;

        //    MySqlTransaction transaction = null;
        //    try
        //    {
        //        connection.Open();
        //        transaction = connection.BeginTransaction();
        //        //设置批量更新的每次处理条数
        //        //adapter.UpdateBatchSize = BatchSize;
        //        //设置事物
        //        adapter.SelectCommand.Transaction = transaction;

        //        if (table.ExtendedProperties["SQL"] != null)
        //        {
        //            adapter.SelectCommand.CommandText = table.ExtendedProperties["SQL"].ToString();
        //            //adapter.InsertCommand.CommandText = table.ExtendedProperties["SQL"].ToString();
        //            //adapter.SelectCommand.CommandText = "select runoob_id from runoob_tbl";
        //        }
        //        adapter.Update(table);
        //        transaction.Commit();/////提交事务
        //    }
        //    catch (MySqlException ex)
        //    {
        //        if (transaction != null) transaction.Rollback();
        //        throw ex;
        //    }
        //    finally
        //    {
        //        connection.Close();
        //        connection.Dispose();
        //    }
        //}

        //void InsertDiece(string connectionString, string tableName, int count)
        //{
        //    var commandText = String.Format("INSERT INTO `{0}` (Dice1, Dice2) Values (@dice1, @dice2)", tableName);
        //    using (var connection = new MySqlConnection(constr))
        //    using (var command = connection.CreateCommand())
        //    {
        //        connection.Open();
        //        command.CommandText = commandText;
        //        for (int i = 0; i < count; i++)
        //        {
        //            command.Parameters.AddWithValue("@dice1", 111);
        //            command.Parameters.AddWithValue("@dice2", 222);
        //            command.ExecuteNonQuery();
        //            command.Parameters.Clear();
        //        }
        //    }
        //}

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
            foreach (var st_p in m_AllxmlTables)
            {
                if (st_p.Key.Contains("sec") || st_p.Key.Contains("Sec"))
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
                    switch (st.type)
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
                        default:
                            MessageBox.Show(string.Format("未知类型:{0}", s_type));
                            break;

                    }
                    //sb.AppendFormat("alter table {0} add {1} VARCHAR(100)", st_p.Key, st.name);
                    sb.AppendFormat("alter table {0} add {1} {2}", st_p.Key, st.name, s_type);
                    command.CommandText = sb.ToString();
                    command.ExecuteNonQuery();
                }
                textBoxSql.AppendText(string.Format("创建mysql表{0}    ok!\n", st_p.Key));
            }
        }

        private void textBox_Uid_TextChanged(object sender, EventArgs e)
        {
            Uids = ((TextBox)sender).Text;
        }

        private void button1_Click_2(object sender, EventArgs e)
        {
            OpenFileDialog file = new OpenFileDialog();
            file.ShowDialog();

            this.textBox_Xml.Text = file.FileName;
        }


        private void button_test_Click(object sender, EventArgs e)
        {
            MysqlMgr.BulkToMySQL();
            //MySqlDbHelper helper = new MySqlDbHelper();
            //helper.InsertByDataTable();
        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_CurSelected.Clear();
            string strCollected = string.Empty;
            DataTable dt = new DataTable();

            for (int i = 0; i < checkedListBox1.Items.Count; i++)
            {
                if (checkedListBox1.GetItemChecked(i))
                {
                    strCollected = checkedListBox1.GetItemText(checkedListBox1.Items[i]);
                    m_CurSelected.Add(strCollected);
                }
            }

        }
        static bool flag = false;
        private void button3_Click(object sender, EventArgs e)
        {
            flag = !flag;
            for (int i = 0; i < checkedListBox1.Items.Count; i++)
            {
                checkedListBox1.SetItemChecked(i, flag);
            }

            checkedListBox1_SelectedIndexChanged(sender, e);
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        
        public void AppendTextColorful(string text, Color color, bool addNewLine = true)
        {
            //RichTextBox rtBox = richTextBox1;
            if (addNewLine)
            {
                text += Environment.NewLine;
            }
            richTextBox1.SelectionStart = richTextBox1.TextLength;
            richTextBox1.SelectionLength = 0;
            richTextBox1.SelectionColor = color;
            richTextBox1.AppendText(text);
            richTextBox1.SelectionColor = richTextBox1.ForeColor;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            AppendTextColorful( "Your message here", Color.Green);
        }
    }
}
