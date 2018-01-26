using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Data.OleDb;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace aboutdata
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void buttonopen_Click(object sender, EventArgs e)
        {
            if (openFileDialogSource.ShowDialog() == DialogResult.OK)
            {
                ctlPath.Text = openFileDialogSource.FileName;
                ExceltoDataSet(ctlPath.Text);

            }

        }
        DataTable dTable;//全局变量

        //     string tableName = schemaTable.Rows[0][2].ToString().Trim();

        //打开方法 
        public DataTable ExceltoDataSet(string path)
        {
            string strConn = "Provider=Microsoft.Jet.OLEDB.4.0;" + "Data Source=" + @path + ";" + "Extended Properties=Excel 8.0;";
            string strExcel = "";
            OleDbDataAdapter myCommand = null;

            DataSet ds = null;
            System.Data.DataTable dt = null;

            try
            {
                OleDbConnection conn = new OleDbConnection(strConn);
                conn.Open();
                System.Data.DataTable schemaTable = conn.GetOleDbSchemaTable(System.Data.OleDb.OleDbSchemaGuid.Tables, null);
                string tableName = schemaTable.Rows[0][2].ToString().Trim();
                strExcel = "select * from [" + tableName + "]";
                myCommand = new OleDbDataAdapter(strExcel, strConn);
                //DataTable dt = new DataTable();
                ds = new DataSet();
                myCommand.Fill(ds);
                dt = ds.Tables[0];

                if (dt.Columns.Count > 1 && dt.Rows.Count >= 1)
                {
                    gridSource.DataSource = dt;
                    gridSource.RowHeadersWidth = 18;
                    gridSource.RowHeadersWidthSizeMode = DataGridViewRowHeadersWidthSizeMode.DisableResizing;
                    gridSource.AllowUserToResizeRows = false;//行大小不能调整
                    tb.Text = "共有 " + (gridSource.RowCount - 1).ToString() + " 条信息";
                    ;
                }
                else
                {
                    MessageBox.Show(tableName + " 表中没有数据，不能导入！", "系统提示", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
            }
            catch
            {
                MessageBox.Show("读取Excel错误！", "系统提示", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }


            dTable = dt;
            return dt;


        }
        public void gx()
        {


            DBHelper.connection.Open();
            string strsql = " EXEC  proc_gx";
            MySqlCommand cmd = new MySqlCommand(strsql, DBHelper.connection);
            cmd.CommandTimeout = 180;
            cmd.ExecuteNonQuery();
            DBHelper.connection.Close();
            MessageBox.Show(" 导入成功！", "系统提示", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);

        }

        //SqlCommand command = new SqlCommand(sql, DBHelper.connection);  // 创建command对象
        //         DBHelper.connection.Open();  // 打开数据库连接

        //       int result = command.ExecuteNonQuery();  // 执行命令

        //   string sql = string.Format("DELETE FROM Student WHERE StudentID={0}",(int)lvStudent.SelectedItems[0].Tag);

        private void btnsx_Click(object sender, EventArgs e)
        {
            ImportTableToDB(dTable);
            //gx();

        }
        public bool ImportTableToDB(DataTable dtImp)
        {
           // int i = 1;
            int ms = -1;
            try
            {
                foreach (DataRow datarow in dTable.Rows)
                {
                     string str = ConfigurationManager.ConnectionStrings["conn"].ConnectionString;
                    //DBHelper.connection.Open();
                    MySqlConnection conn = new MySqlConnection(str);
                    if (conn.State == ConnectionState.Closed)
                    {
                        conn.Open();

                    }
                    string sql = "insert into test(rq,ch,jql,zy,hsdj,hsze,dj,je,se,bz,gys) values(@rq,@ch,@jql,@zy,@hsdj,@hsze,@dj,@je,@se,@bz,@gys)";
                    MySqlCommand cmd = new MySqlCommand(sql, conn);
                    cmd.Parameters.AddWithValue("@gys", datarow["供应商"].ToString());
                    cmd.Parameters.AddWithValue("@ch", datarow["车号"].ToString());
                    cmd.Parameters.AddWithValue("@rq", datarow["日期"].ToString());
                    cmd.Parameters.AddWithValue("@zy", datarow["职员"].ToString());
                    cmd.Parameters.AddWithValue("@jql", datarow["加气量"].ToString());
                    cmd.Parameters.AddWithValue("@hsdj", datarow["含税单价"].ToString());
                    cmd.Parameters.AddWithValue("@hsze", datarow["含税金额"].ToString());
                    cmd.Parameters.AddWithValue("@dj", datarow["单价"].ToString());
                    cmd.Parameters.AddWithValue("@je", datarow["金额"].ToString());
                    cmd.Parameters.AddWithValue("@se", datarow["税额"].ToString());
                    cmd.Parameters.AddWithValue("@bz", datarow["备注"].ToString());
                    //cmd.Parameters.AddWithValue("@ID", i++);
                    int i=ms= cmd.ExecuteNonQuery();
                    if (i < 0) {
                        MessageBox.Show("xxx");
                    }
                    conn.Close();
                }
                if (ms > 0)
                {
                    MessageBox.Show(" 导入成功！", "系统提示", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
                return true;

            }
            catch
            {
                return false;
            }
        }

        //此注释的是连接sql进行操作
      /*  public bool ImportTableToDB(DataTable dtImp)
        {
            delete();
            int i = 1;
            try
            {
                foreach (DataRow datarow in dTable.Rows)
                {

                    DBHelper.connection.Open();


                    string sql = "insert into test(日期,车号,加气量,职员,含税单价,含税金额,单价,金额,税额,备注,供应商,ID) values(@日期,@车号,@加气量,@职员,@含税单价,@含税金额,@单价,@金额,@税额,@备注,@供应商,@ID)";
                    SqlCommand cmd = new SqlCommand(sql, DBHelper.connection);
                    cmd.Parameters.AddWithValue("@日期", datarow["日期"].ToString());
                    cmd.Parameters.AddWithValue("@车号", datarow["车号"].ToString());
                    cmd.Parameters.AddWithValue("@加气量", datarow["加气量"].ToString());
                    cmd.Parameters.AddWithValue("@职员", datarow["职员"].ToString());
                    cmd.Parameters.AddWithValue("@含税单价", datarow["含税单价"].ToString());
                    cmd.Parameters.AddWithValue("@含税金额", datarow["含税金额"].ToString());
                    cmd.Parameters.AddWithValue("@单价", datarow["单价"].ToString());
                    cmd.Parameters.AddWithValue("@金额", datarow["金额"].ToString());
                    cmd.Parameters.AddWithValue("@税额", datarow["税额"].ToString());
                    cmd.Parameters.AddWithValue("@备注", datarow["备注"].ToString());
                    cmd.Parameters.AddWithValue("@供应商", datarow["供应商"].ToString());
                    cmd.Parameters.AddWithValue("@ID", i++);

                    cmd.ExecuteNonQuery();
                    DBHelper.connection.Close();
                }

                // MessageBox.Show( " 导入成功！", "系统提示", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return true;

            }
            catch
            {
                return false;
            }
        }*/
       

        public void deletesr()
        {
            DBHelper.connection.Open();
            string strsql = "DECLARE @test int   select @test=count(*) from test_1 if @test>0  delete test_1";
            MySqlCommand cmd = new MySqlCommand(strsql, DBHelper.connection);
            cmd.ExecuteNonQuery();
            DBHelper.connection.Close();
        }
   
    }
}
