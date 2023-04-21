using System.Windows.Forms;
using System;
using System.Collections.Generic;
using System.Linq;
using mpp_proiect_csharp_vreauladudu.domain;

namespace mpp_proiect_csharp_vreauladudu
{
    public partial class MotoWindow : Form
    {
        private Form loggingForm = null;
        private MotoClientController Controller = null;
        private readonly List<Participant> participantsData = new List<Participant>();
        private int participantsCount = 0;

        public MotoWindow(Form loggingForm, MotoClientController controller)
        {
            InitializeComponent();
            log4net.Config.XmlConfigurator.Configure();
            this.loggingForm = loggingForm;
            this.Controller = controller;
            this.Controller.UpdateEvent += userUpdate;

            init();
        }

        public void userUpdate(object sender, MotoUserEvent userEvent)
        {
            if (userEvent.UserEventType == UserEvent.ParticipantAdded)
            {
                this.participantsData.Add((Participant)userEvent.Data);
                listBox2.BeginInvoke(new UpdateListBoxCallback(this.updateListBox), new Object[] { listBox2, this.participantsData });
            }
        }

        private void updateListBox(ListBox listBox, IList<Participant> newData)
        {
            listBox.DataSource = null;
            listBox.DataSource = newData;

            this.participantsCount = newData.Count;
            label4.Text = this.participantsCount.ToString();
        }

        public delegate void UpdateListBoxCallback(ListBox list, IList<Participant> data);

        private void init()
        {
            List<int> capacityList = new List<int>();
            this.Controller.listRaces().ToList().ForEach(race =>
            {
                capacityList.Add(race.Key);
            });

            listBox1.DataSource = capacityList;


            List<Motorcycle> motorcycleList = new List<Motorcycle>();
            this.Controller.listMotorcycles().ToList().ForEach(motorcycle =>
            {
                motorcycleList.Add(motorcycle);
            });

            listBox4.DataSource = motorcycleList;
        }

        private void listBox1_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            if (listBox1.SelectedItem == null)
            {
                return;
            }

            int newValue = (int)listBox1.SelectedItem;
            this.participantsData.Clear();

            this.Controller.listMotorcyclesByCapacity(newValue).ForEach(motorcycle =>
            {
                List<Participant> participants = this.Controller.findParticipantForRace(motorcycle.Id);
                if (participants != null)
                {
                    this.participantsData.AddRange(participants);
                }
            });

            listBox2.DataSource = null;
            listBox2.DataSource = this.participantsData;
            this.participantsCount = this.participantsData.Count;
            label4.Text = this.participantsCount.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            listBox3.Items.Clear();

            List<Participant> participantList = new List<Participant>();
            this.Controller.listMotorcyclesByBrand(textBox1.Text).ForEach(motorcycle =>
            {
                List<Participant> participants = this.Controller.findParticipantForRace(motorcycle.Id);
                if (participants != null)
                {
                    participantList.AddRange(participants);
                }
            });

            foreach (Participant participant in participantList)
            {
                Motorcycle motorcycle = this.Controller.findMotorcycleById(participant.MotorcycleID);
                listBox3.Items.Add("Nume: " + participant.Name + " | Capacitate motocicleta: " + motorcycle.Capacity);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Controller.UpdateEvent -= userUpdate;
            this.Controller.logout();

            this.Hide();
            this.loggingForm.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Controller.addParticipant(textBox3.Text, textBox4.Text, Int32.Parse(textBox2.Text));

            listBox3.Items.Clear();

            List<Participant> participantList = new List<Participant>();
            this.Controller.listMotorcyclesByBrand(textBox4.Text).ForEach(motorcycle =>
            {
                List<Participant> participants = this.Controller.findParticipantForRace(motorcycle.Id);
                if (participants != null)
                {
                    participantList.AddRange(participants);
                }
            });

            foreach (Participant participant in participantList)
            {
                Motorcycle motorcycle = this.Controller.findMotorcycleById(participant.MotorcycleID);
                listBox3.Items.Add("Nume: " + participant.Name + " | Capacitate motocicleta: " + motorcycle.Capacity);
            }
        }

        private void MotoWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing)
            {
                this.Controller.UpdateEvent -= userUpdate;
                this.Controller.logout();

                Application.Exit();
            }
        }
    }
}