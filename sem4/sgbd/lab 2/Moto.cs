using System.Windows.Forms;
using System.Data.SqlClient;
using System.Data;
using System;
using System.Configuration;
using System.Collections.Generic;

namespace sgbd
{
    public partial class Moto : Form
    {
        private static string connectionInfo = ConfigurationManager.ConnectionStrings["ConnectionInfo"].ConnectionString;
        private SqlConnection Connection = new SqlConnection(connectionInfo);

        private string ParentTableName = ConfigurationManager.AppSettings["ParentTableName"];
        private string ParentTableFilterCriteria = ConfigurationManager.AppSettings["ParentTableFilterCriteria"];

        private string ChildTableName = ConfigurationManager.AppSettings["ChildTableName"];
        private string ChildNumberOfColumns = ConfigurationManager.AppSettings["ChildNumberOfColumns"];
        private string ChildColumnNames = ConfigurationManager.AppSettings["ChildColumnNames"];
        private string ColumnNamesInsertParameters = ConfigurationManager.AppSettings["ColumnNamesInsertParameters"];
        private string InsertQuery = ConfigurationManager.AppSettings["InsertQuery"];
        private string UpdateQuery = ConfigurationManager.AppSettings["UpdateQuery"];
        private string DeleteQuery = ConfigurationManager.AppSettings["DeleteQuery"];

        private SqlDataAdapter Adapter = new SqlDataAdapter();
        private DataSet CategoriiMoto = new DataSet();
        private DataSet Motociclete = new DataSet();
        private DataSet MotocicleteIDs = new DataSet();

        public Moto()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, System.EventArgs e)
        {
            Adapter.SelectCommand = new SqlCommand("SELECT * FROM " + this.ParentTableName, Connection);
            CategoriiMoto.Clear();
            Adapter.Fill(CategoriiMoto);
            dataGridView1.DataSource = CategoriiMoto.Tables[0];
        }

        private void CategoriiMoto_selectionChanged(object sender, System.EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count != 1)
            {
                return;
            }

            string tipMotocicleta = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
            LoadMotocicleteByTip(tipMotocicleta);
            List<string> list = new List<string>();
            for (int i = 0; i < Int32.Parse(this.ChildNumberOfColumns) - 1; ++i)
            {
                list.Add("");
            }
            list.Add(tipMotocicleta);
            LoadMotocicletaToTextbox(list);
        }

        private void LoadMotocicleteByTip(string TipMotocicleta)
        {
            Adapter.SelectCommand = new SqlCommand("SELECT * FROM " + this.ChildTableName + " WHERE " + this.ParentTableFilterCriteria +  " = @" + this.ParentTableFilterCriteria, Connection);
            Adapter.SelectCommand.Parameters.Add("@" + this.ParentTableFilterCriteria, SqlDbType.VarChar).Value = TipMotocicleta;
            Motociclete.Clear();
            Adapter.Fill(Motociclete);
            dataGridView2.DataSource = Motociclete.Tables[0];
        }

        private void LoadMotocicletaToTextbox(List<string> args)
        {
            this.panel1.Controls.Clear();

            List<string> ColumnNamesList = new List<string>(this.ChildColumnNames.Split(','));
            for (int i = 0; i < ColumnNamesList.Count; ++i)
            {
                Label label = new Label();
                label.Text = ColumnNamesList[i];
                label.Top = this.panel1.Controls.Count * (label.Height - 9) + 15;

                TextBox textBox = new TextBox();
                textBox.Top = this.panel1.Controls.Count * (textBox.Height - 6) + 12;
                textBox.Left += 105;
                textBox.Text = args[i];

                this.panel1.Controls.Add(label);
                this.panel1.Controls.Add(textBox);
            }
        }

        private void Motociclete_selectionChanged(object sender, EventArgs e)
        {
            if (dataGridView2.SelectedRows.Count != 1)
            {
                return;
            }

            List<string> list = new List<string>();
            for (int i = 0; i < Int32.Parse(this.ChildNumberOfColumns); ++i)
            {
                list.Add(dataGridView2.SelectedRows[0].Cells[i].Value.ToString());
            }
            LoadMotocicletaToTextbox(list);
        }

        private void inserare_Clicked(object sender, EventArgs e)
        {
            try
            {
                MotocicleteIDs.Clear();

                List<string> ColumnNamesList = new List<string>(this.ChildColumnNames.Split(','));
                Adapter.SelectCommand = new SqlCommand("SELECT MAX(" + ColumnNamesList[0] + ") FROM " + this.ChildTableName, Connection);
                Adapter.Fill(MotocicleteIDs);


                Adapter.InsertCommand = new SqlCommand(this.InsertQuery, Connection);

                List<string> ColumnNamesInsertParameters = new List<string>(this.ColumnNamesInsertParameters.Split(','));
                Adapter.InsertCommand.Parameters.AddWithValue(ColumnNamesInsertParameters[0], Int32.Parse(MotocicleteIDs.Tables[0].Rows[0][0].ToString()) + 1);
                for (int i = 1; i < ColumnNamesInsertParameters.Count; ++i)
                {
                    int n = -1;
                    var isNumeric = int.TryParse(this.panel1.Controls[2 * i + 1].Text, out n);
                    if (isNumeric)
                    {
                        Adapter.InsertCommand.Parameters.AddWithValue(ColumnNamesInsertParameters[i], n);
                    }
                    else
                    {
                        Adapter.InsertCommand.Parameters.AddWithValue(ColumnNamesInsertParameters[i], this.panel1.Controls[2 * i + 1].Text);
                    }
                }

                Connection.Open();
                Adapter.InsertCommand.ExecuteNonQuery();
                Connection.Close();

                LoadMotocicleteByTip(this.panel1.Controls[2 * (ColumnNamesInsertParameters.Count - 1) + 1].Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                Connection.Close();
            }
        }

        private void actualizare_clicked(object sender, EventArgs e)
        {
            try
            {
                if (dataGridView2.SelectedRows.Count != 1)
                {
                    return;
                }

                Adapter.UpdateCommand = new SqlCommand(this.UpdateQuery, Connection);

                List<string> ColumnNamesInsertParameters = new List<string>(this.ColumnNamesInsertParameters.Split(','));
                for (int i = 0; i < ColumnNamesInsertParameters.Count - 1; ++i)
                {
                    int n = -1;
                    var isNumeric = int.TryParse(this.panel1.Controls[2 * i + 1].Text, out n);
                    if (isNumeric)
                    {
                        Adapter.UpdateCommand.Parameters.AddWithValue(ColumnNamesInsertParameters[i], n);
                    }
                    else
                    {
                        Adapter.UpdateCommand.Parameters.AddWithValue(ColumnNamesInsertParameters[i], this.panel1.Controls[2 * i + 1].Text);
                    }
                }

                Connection.Open();
                Adapter.UpdateCommand.ExecuteNonQuery();
                Connection.Close();

                Motociclete.Clear();
                Adapter.Fill(Motociclete);
                dataGridView2.DataSource = Motociclete.Tables[0];
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                Connection.Close();
            }
        }

        private void stergere_Clicked(object sender, EventArgs e)
        {
            try
            {
                if (dataGridView2.SelectedRows.Count != 1)
                {
                    return;
                }

                Adapter.DeleteCommand = new SqlCommand(this.DeleteQuery, Connection);

                List<string> ColumnNamesInsertParameters = new List<string>(this.ColumnNamesInsertParameters.Split(','));
                Adapter.DeleteCommand.Parameters.AddWithValue(ColumnNamesInsertParameters[0], this.panel1.Controls[1].Text);

                Connection.Open();
                Adapter.DeleteCommand.ExecuteNonQuery();
                Connection.Close();

                Motociclete.Clear();
                Adapter.Fill(Motociclete);
                dataGridView2.DataSource = Motociclete.Tables[0];
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                Connection.Close();
            }
        }
    }
}
