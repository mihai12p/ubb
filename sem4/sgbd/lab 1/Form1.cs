using System.Windows.Forms;
using System.Data.SqlClient;
using System.Data;
using System;

namespace sgbd
{
    public partial class Form1 : Form
    {
        SqlConnection Connection = new SqlConnection("Server=--\\SQLEXPRESS;Database=Motorshop;Integrated Security=true;");
        SqlDataAdapter Adapter = new SqlDataAdapter();
        DataSet CategoriiMoto = new DataSet();
        DataSet Motociclete = new DataSet();
        DataSet InformatiiMotociclete = new DataSet();
        DataSet MotocicleteIDs = new DataSet();

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, System.EventArgs e)
        {
            Adapter.SelectCommand = new SqlCommand("SELECT * FROM Categorii_moto", Connection);
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
            LoadMotocicletaToTextbox("", "", "", "", tipMotocicleta);
        }

        private void LoadMotocicleteByTip(string TipMotocicleta)
        {
            Adapter.SelectCommand = new SqlCommand("SELECT * FROM Motociclete WHERE Tip = @Tip", Connection);
            Adapter.SelectCommand.Parameters.Add("@Tip", SqlDbType.VarChar).Value = TipMotocicleta;
            Motociclete.Clear();
            Adapter.Fill(Motociclete);
            dataGridView2.DataSource = Motociclete.Tables[0];
        }

        private void LoadMotocicletaToTextbox(string DenumireMotocicleta, string ProducatorMotocicleta, string PretMotocicleta, string StocMotocicleta, string TipMotocicleta)
        {
            InformatiiMotociclete.Tables.Clear();

            DataTable informatiiMotocicleta = new DataTable("informatiiMotocicleta");
            informatiiMotocicleta.Columns.Add("denumire");
            informatiiMotocicleta.Columns.Add("producator");
            informatiiMotocicleta.Columns.Add("pret");
            informatiiMotocicleta.Columns.Add("stoc");
            informatiiMotocicleta.Columns.Add("tip");
            informatiiMotocicleta.Rows.Add(DenumireMotocicleta, ProducatorMotocicleta, PretMotocicleta, StocMotocicleta, TipMotocicleta);
            InformatiiMotociclete.Tables.Add(informatiiMotocicleta);
            denumireTextbox.Text = DenumireMotocicleta;
            producatorTextbox.Text = ProducatorMotocicleta;
            pretTextbox.Text = PretMotocicleta;
            stocTextbox.Text = StocMotocicleta;
            tipTextbox.Text = TipMotocicleta;
        }

        private void Motociclete_selectionChanged(object sender, EventArgs e)
        {
            if (dataGridView2.SelectedRows.Count != 1)
            {
                return;
            }

            string denumireMotocicleta = dataGridView2.SelectedRows[0].Cells[1].Value.ToString();
            string producatorMotocicleta = dataGridView2.SelectedRows[0].Cells[2].Value.ToString();
            string pretMotocicleta = dataGridView2.SelectedRows[0].Cells[3].Value.ToString();
            string stocMotocicleta = dataGridView2.SelectedRows[0].Cells[4].Value.ToString();
            string tipMotocicleta = dataGridView2.SelectedRows[0].Cells[5].Value.ToString();
            LoadMotocicletaToTextbox(denumireMotocicleta, producatorMotocicleta, pretMotocicleta, stocMotocicleta, tipMotocicleta);
        }

        private void inserare_Clicked(object sender, EventArgs e)
        {
            try
            {
                MotocicleteIDs.Clear();
                Adapter.SelectCommand = new SqlCommand("SELECT MAX(mID) FROM Motociclete", Connection);
                Adapter.Fill(MotocicleteIDs);

                Adapter.InsertCommand = new SqlCommand("INSERT INTO Motociclete(mID, Denumire, Producator, Pret, Stoc, Tip) VALUES (@mID, @Denumire, @Producator, @Pret, @Stoc, @Tip)", Connection);
                Adapter.InsertCommand.Parameters.Add("@Tip", SqlDbType.VarChar).Value = tipTextbox.Text;
                Adapter.InsertCommand.Parameters.Add("@mID", SqlDbType.Int).Value = Int32.Parse(MotocicleteIDs.Tables[0].Rows[0][0].ToString()) + 1;
                Adapter.InsertCommand.Parameters.Add("@Denumire", SqlDbType.VarChar).Value = denumireTextbox.Text;
                Adapter.InsertCommand.Parameters.Add("@Producator", SqlDbType.VarChar).Value = producatorTextbox.Text;
                Adapter.InsertCommand.Parameters.Add("@Pret", SqlDbType.Int).Value = Int32.Parse(pretTextbox.Text);
                Adapter.InsertCommand.Parameters.Add("@Stoc", SqlDbType.VarChar).Value = stocTextbox.Text;
                Connection.Open();
                Adapter.InsertCommand.ExecuteNonQuery();
                Connection.Close();

                LoadMotocicleteByTip(tipTextbox.Text);
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

                Adapter.UpdateCommand = new SqlCommand("UPDATE Motociclete SET Denumire = @Denumire, Producator = @Producator, Pret = @Pret, Stoc = @Stoc WHERE mID = @mID", Connection);
                Adapter.UpdateCommand.Parameters.Add("@mID", SqlDbType.Int).Value = Int32.Parse(dataGridView2.SelectedRows[0].Cells[0].Value.ToString());
                Adapter.UpdateCommand.Parameters.Add("@Denumire", SqlDbType.VarChar).Value = denumireTextbox.Text;
                Adapter.UpdateCommand.Parameters.Add("@Producator", SqlDbType.VarChar).Value = producatorTextbox.Text;
                Adapter.UpdateCommand.Parameters.Add("@Pret", SqlDbType.Int).Value = Int32.Parse(pretTextbox.Text);
                Adapter.UpdateCommand.Parameters.Add("@Stoc", SqlDbType.VarChar).Value = stocTextbox.Text;
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

                Adapter.DeleteCommand = new SqlCommand("DELETE FROM Motociclete WHERE mID = @mID", Connection);
                Adapter.DeleteCommand.Parameters.Add("@mID", SqlDbType.Int).Value = Int32.Parse(dataGridView2.SelectedRows[0].Cells[0].Value.ToString());
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
