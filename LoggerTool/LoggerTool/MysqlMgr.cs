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
using System.Configuration;

namespace MySqlMgr
{
    public class MysqlMgr
    {
        public MysqlMgr()
        {
        }


        private void CreateMysqlTb(DataTable dt)
        {
            string constr = ConfigurationManager.AppSettings["mysql"];
            MySqlConnection mycon = new MySqlConnection(constr);
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("DROP TABLE IF EXISTS `{0}`;", dt.TableName);

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
        // 100k rows took only 3seconds
        public static void BulkToMySQL()
        {
            string ConnectionString = ConfigurationManager.AppSettings["mysql"];
            StringBuilder sCommand = new StringBuilder("INSERT INTO User (FirstName, LastName) VALUES ");
            using (MySqlConnection mConnection = new MySqlConnection(ConnectionString))
            {
                List<string> Rows = new List<string>();
                for (int i = 0; i < 100000; i++)
                {
                    Rows.Add(string.Format("('{0}','{1}')", MySqlHelper.EscapeString("test"), MySqlHelper.EscapeString("test")));
                }
                sCommand.Append(string.Join(",", Rows));
                sCommand.Append(";");
                mConnection.Open();
                using (MySqlCommand myCmd = new MySqlCommand(sCommand.ToString(), mConnection))
                {
                    myCmd.CommandType = CommandType.Text;

                    //myCmd.Parameters.AddWithValue("@FirstName", "test");
                    //myCmd.Parameters.AddWithValue("@LastName", "test");

                    myCmd.ExecuteNonQuery();
                }
            }
        }

        //public static void BulkToMySQL(List<string> fields, List<List<string>> SQLStringList)
        //public static void BulkToMySQL(string connectionString, DataTable table)//
        //{
        //    string ConnectionString = ConfigurationManager.AppSettings["mysql"];
        //    StringBuilder sCommand = new StringBuilder();
        //    sCommand.AppendFormat("INSERT INTO {0}(", table.TableName);
        //    if (table.Rows.Count == 0) return;
        //    for (int i = 1; i < table.Rows.Count; ++i)
        //    {
        //        //sCommand.AppendFormat("INSERT INTO {0} ({1}, {2}) VALUES ", fields);
        //        sCommand.AppendFormat("{0},", fields[i]);
        //    }
        //    sCommand.Append(") VALUES");
        //    using (MySqlConnection mConnection = new MySqlConnection(ConnectionString))
        //    {
        //        //List<string> Rows = new List<string>();

        //        for (int i = 0; i < SQLStringList.Count; ++i)
        //        {
        //            List<string> rows = SQLStringList[i];
        //            //assert(rows.Count==fields.Count-1);
        //            sCommand.Append("(");
        //            for (int j = 0; j < rows.Count; ++j)
        //            {
        //                //Rows.Add(string.Format("('{0}','{1}')", MySqlHelper.EscapeString("test"), MySqlHelper.EscapeString("test")));
        //                sCommand.AppendFormat("'{0}',", rows[i]);
        //            }
        //            sCommand.Remove(sCommand.Length,1);
        //            sCommand.Append(")");
        //        }
        //        //sCommand.Append(string.Join(",", Rows));
        //        sCommand.Append(";");
        //        mConnection.Open();
        //        using (MySqlCommand myCmd = new MySqlCommand(sCommand.ToString(), mConnection))
        //        {
        //            myCmd.CommandType = CommandType.Text;

        //            //myCmd.Parameters.AddWithValue("@FirstName", "test");
        //            //myCmd.Parameters.AddWithValue("@LastName", "test");

        //            myCmd.ExecuteNonQuery();
        //        }
        //    }
        //}

        public /*static*/ void BulkInsert(string connectionString, List<string> SQLStringList)
        {
            StringBuilder sb = new StringBuilder();

            using (MySqlConnection conn = new MySqlConnection(connectionString))
            {
                conn.Open();
                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                MySqlTransaction tx = conn.BeginTransaction();
                cmd.Transaction = tx;
                try
                {
                    for (int n = 0; n < SQLStringList.Count; n++)
                    {
                        string strsql = SQLStringList[n].ToString();
                        if (strsql.Trim().Length > 1)
                        {
                            cmd.CommandText = strsql;
                            cmd.ExecuteNonQuery();
                        }
                        //后来加上的  
                        if (n > 0 && (n % 500 == 0 || n == SQLStringList.Count - 1))
                        {
                            tx.Commit();
                            tx = conn.BeginTransaction();
                        }
                    }
                    //tx.Commit();//原来一次性提交  
                }
                catch (System.Data.SqlClient.SqlException E)
                {
                    tx.Rollback();
                    throw new Exception(E.Message);
                }

            }
        }


    }
}