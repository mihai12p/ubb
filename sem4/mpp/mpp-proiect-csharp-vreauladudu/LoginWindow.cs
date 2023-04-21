using mpp_proiect_csharp_vreauladudu.domain;
using System;
using System.Windows.Forms;

namespace mpp_proiect_csharp_vreauladudu
{
    public partial class LoginWindow : Form
    {
        MotoClientController Controller = null;

        public LoginWindow(MotoClientController controller)
        {
            InitializeComponent();
            this.Controller = controller;
        }

        private void button1_Click(object sender, System.EventArgs e)
        {
            try
            {
                this.Controller.login(this.textBox1.Text, this.textBox2.Text);
                this.Hide();

                MotoWindow loggedForm = new MotoWindow(this, this.Controller);
                loggedForm.Text = "Moto Window for " + this.textBox1.Text;
                loggedForm.Show();
            }
            catch (Exception exception)
            {
                MessageBox.Show(this, exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}