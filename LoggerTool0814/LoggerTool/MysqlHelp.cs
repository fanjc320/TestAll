using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Text;

public class MySqlDbHelper
{

    #region 私有变量
    private const string defaultConfigKeyName = "MySqlConnection";//连接字符串 Database='数据库';Data Source='IP地址';User Id='sa';Password='sa';pooling=true
    private string connectionString;
    private string providerName;

    #endregion

    #region 构造函数

    /// <summary>
    /// 默认构造函数(DbHelper)
    /// </summary>
    public MySqlDbHelper()
    {
        //this.connectionString = ConfigurationManager.ConnectionStrings[defaultConfigKeyName].ConnectionString;
        //this.providerName = ConfigurationManager.ConnectionStrings[defaultConfigKeyName].ProviderName;
    }

    /// <summary>
    /// DbHelper构造函数
    /// </summary>
    /// <param name="keyName">连接字符串名</param>
    public MySqlDbHelper(string keyName)
    {
        //this.connectionString = ConfigurationManager.ConnectionStrings[keyName].ConnectionString;
        //this.providerName = ConfigurationManager.ConnectionStrings[keyName].ProviderName;
    }

    #endregion

    public int ExecuteNonQuery(string sql, params MySqlParameter[] parameters)
    {
        int res = 0;
        using (MySqlConnection con = new MySqlConnection(connectionString))
        {
            con.Open();
            using (MySqlCommand cmd = new MySqlCommand(sql, con))
            {
                foreach (MySqlParameter parameter in parameters)
                {
                    cmd.Parameters.Add(parameter);
                }
                try
                {
                    res = cmd.ExecuteNonQuery();
                }
                catch
                {
                    res = -1;
                }
            }
        }
        return res;
    }

    public object GetExeScalar(string sql, params MySqlParameter[] parameters)
    {
        object res = null;
        using (MySqlConnection con = new MySqlConnection(connectionString))
        {
            con.Open();
            using (MySqlCommand cmd = new MySqlCommand(sql, con))
            {
                foreach (MySqlParameter parameter in parameters)
                {
                    cmd.Parameters.Add(parameter);
                }
                res = cmd.ExecuteScalar();
            }
        }
        return res;
    }

    public DataTable GetDataTable(string sql, params MySqlParameter[] parameters)
    {
        DataSet dataset = new DataSet();
        using (MySqlConnection con = new MySqlConnection(connectionString))
        {
            con.Open();
            using (MySqlCommand cmd = new MySqlCommand(sql, con))
            {
                foreach (MySqlParameter parameter in parameters)
                {
                    cmd.Parameters.Add(parameter);
                }
                MySqlDataAdapter adapter = new MySqlDataAdapter(cmd);
                adapter.Fill(dataset);
            }
        }
        return dataset.Tables[0];
    }

    /// <summary>
    /// DataTable批量加入MYSQL数据库
    /// </summary>
    /// <param name="dataTable"></param>
    /// <returns></returns>
    public string InsertByDataTable(DataTable dataTable)
    {
        string result = string.Empty;
        if (null == dataTable || dataTable.Rows.Count <= 0)
        {
            return "添加失败！DataTable暂无数据！";
        }
        if (string.IsNullOrEmpty(dataTable.TableName))
        {
            return "添加失败！请先设置DataTable的名称！";
        }
        // 构建INSERT语句
        StringBuilder sb = new StringBuilder();
        sb.Append("INSERT INTO " + dataTable.TableName + "(");
        for (int i = 0; i < dataTable.Columns.Count; i++)
        {
            sb.Append(dataTable.Columns[i].ColumnName + ",");
        }
        sb.Remove(sb.ToString().LastIndexOf(','), 1);
        sb.Append(") VALUES ");
        for (int i = 0; i < dataTable.Rows.Count; i++)
        {
            sb.Append("(");
            for (int j = 0; j < dataTable.Columns.Count; j++)
            {
                sb.Append("'" + dataTable.Rows[i][j] + "',");
            }
            sb.Remove(sb.ToString().LastIndexOf(','), 1);
            sb.Append("),");
        }
        sb.Remove(sb.ToString().LastIndexOf(','), 1);
        sb.Append(";");
        int res = -1;
        using (MySqlConnection con = new MySqlConnection(connectionString))
        {
            con.Open();
            using (MySqlCommand cmd = new MySqlCommand(sb.ToString(), con))
            {
                try
                {
                    res = cmd.ExecuteNonQuery();
                }
                catch (Exception ex)
                {
                    res = -1;
                    // Unknown column 'names' in 'field list' 
                    result = "操作失败！" + ex.Message.Replace("Unknown column", "未知列").Replace("in 'field list'", "存在字段集合中！");
                }
            }
        }
        if (res > 0)
        {
            result = "恭喜添加成功!";
        }
        return result;
    }

    //for sql ,not mysql
    public void createsqltable(DataTable dt, string tablename)
    {
        string strconnection = "";
        string table = "";
        table += "IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[" + tablename + "]') AND type in (N'U'))";
        table += "BEGIN ";
        table += "create table " + tablename + "";
        table += "(";
        for (int i = 0; i < dt.Columns.Count; i++)
        {
            if (i != dt.Columns.Count - 1)
                table += dt.Columns[i].ColumnName + " " + "varchar(max)" + ",";
            else
                table += dt.Columns[i].ColumnName + " " + "varchar(max)";
        }
        table += ") ";
        table += "END";
        InsertQuery(table, strconnection);
        //CopyData(strconnection, dt, tablename);
    }
    public void InsertQuery(string qry, string connection)
    {
        MySqlConnection _connection = new MySqlConnection(connection);
        MySqlCommand cmd = new MySqlCommand();
        cmd.CommandType = CommandType.Text;
        cmd.CommandText = qry;
        cmd.Connection = _connection;
        _connection.Open();
        cmd.ExecuteNonQuery();
        _connection.Close();
    }
    //public static void CopyData(string connStr, DataTable dt, string tablename)
    //{
    //    using (SqlBulkCopy bulkCopy =
    //    new SqlBulkCopy(connStr, SqlBulkCopyOptions.TableLock))
    //    {
    //        bulkCopy.DestinationTableName = tablename;
    //        bulkCopy.WriteToServer(dt);
    //    }
    //}

    public static string CreateTABLE(string tableName, DataTable table)
    {
        string sqlsc;
        sqlsc = "CREATE TABLE " + tableName + "(";
        for (int i = 0; i < table.Columns.Count; i++)
        {
            sqlsc += "\n [" + table.Columns[i].ColumnName + "] ";
            string columnType = table.Columns[i].DataType.ToString();
            switch (columnType)
            {
                case "System.Int32":
                    sqlsc += " int ";
                    break;
                case "System.Int64":
                    sqlsc += " bigint ";
                    break;
                case "System.Int16":
                    sqlsc += " smallint";
                    break;
                case "System.Byte":
                    sqlsc += " tinyint";
                    break;
                case "System.Decimal":
                    sqlsc += " decimal ";
                    break;
                case "System.DateTime":
                    sqlsc += " datetime ";
                    break;
                case "System.String":
                default:
                    sqlsc += string.Format(" nvarchar({0}) ", table.Columns[i].MaxLength == -1 ? "max" : table.Columns[i].MaxLength.ToString());
                    break;
            }
            if (table.Columns[i].AutoIncrement)
                sqlsc += " IDENTITY(" + table.Columns[i].AutoIncrementSeed.ToString() + "," + table.Columns[i].AutoIncrementStep.ToString() + ") ";
            if (!table.Columns[i].AllowDBNull)
                sqlsc += " NOT NULL ";
            sqlsc += ",";
        }
        return sqlsc.Substring(0, sqlsc.Length - 1) + "\n)";
    }

}