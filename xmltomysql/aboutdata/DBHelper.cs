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
    class DBHelper
    {
        //private static string connString = ConfigurationManager.ConnectionStrings["conn"].ConnectionString;
        private static string connString = "server=127.0.0.1;User Id=sa;pwd=123456;Database=Test";
        // 数据库连接 Connection 对象
       public static MySqlConnection connection = new MySqlConnection(connString);

    }
}
