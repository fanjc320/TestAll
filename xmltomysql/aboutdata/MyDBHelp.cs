using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aboutdata
{
    class MyDBHelp
    {
        static string str = ConfigurationManager.ConnectionStrings["conn"].ConnectionString;
        //带sql查询方法
        public static DataSet mysqlQuery(string sql)
        {
            MySqlConnection DBConn = new MySqlConnection(str);
            if (DBConn.State == ConnectionState.Closed)
            {
                DBConn.Open();
            }
            MySqlDataAdapter mda = new MySqlDataAdapter(sql, DBConn);
            DataSet ds = new DataSet();
            mda.Fill(ds);
            DBConn.Close();
            return ds;
        }
        //带sql操作方法
        public static int mysqlNotQuery(string sql)
        {
            MySqlConnection conn = new MySqlConnection(str);
            if (conn.State == ConnectionState.Closed)
            {
                conn.Open();

            }
            MySqlCommand comm = new MySqlCommand(sql, conn);
            int i = comm.ExecuteNonQuery();
            conn.Close();
            return i;
        }
        //执行增删改
        public static int ExecuteNonQuery(string sql, MySqlParameter[] parameters)
        {
            MySqlConnection conn = new MySqlConnection(str);
            if (conn.State == ConnectionState.Closed)
            {
                conn.Open();

            }
            MySqlCommand comm = new MySqlCommand(sql, conn);
            comm.Parameters.AddRange(parameters);
            return comm.ExecuteNonQuery();
        }
    }
}
