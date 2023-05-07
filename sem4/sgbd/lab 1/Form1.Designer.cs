namespace sgbd
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.dataGridView2 = new System.Windows.Forms.DataGridView();
            this.btnConectare = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.denumireTextbox = new System.Windows.Forms.TextBox();
            this.producator = new System.Windows.Forms.Label();
            this.producatorTextbox = new System.Windows.Forms.TextBox();
            this.pret = new System.Windows.Forms.Label();
            this.pretTextbox = new System.Windows.Forms.TextBox();
            this.stoc = new System.Windows.Forms.Label();
            this.stocTextbox = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.tip = new System.Windows.Forms.Label();
            this.tipTextbox = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(12, 80);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersWidth = 51;
            this.dataGridView1.RowTemplate.Height = 24;
            this.dataGridView1.Size = new System.Drawing.Size(337, 457);
            this.dataGridView1.TabIndex = 0;
            this.dataGridView1.SelectionChanged += new System.EventHandler(this.CategoriiMoto_selectionChanged);
            // 
            // dataGridView2
            // 
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Location = new System.Drawing.Point(355, 80);
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.RowHeadersWidth = 51;
            this.dataGridView2.RowTemplate.Height = 24;
            this.dataGridView2.Size = new System.Drawing.Size(672, 457);
            this.dataGridView2.TabIndex = 1;
            this.dataGridView2.SelectionChanged += new System.EventHandler(this.Motociclete_selectionChanged);
            // 
            // btnConectare
            // 
            this.btnConectare.Location = new System.Drawing.Point(12, 12);
            this.btnConectare.Name = "btnConectare";
            this.btnConectare.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btnConectare.Size = new System.Drawing.Size(182, 62);
            this.btnConectare.TabIndex = 2;
            this.btnConectare.Text = "Conectare";
            this.btnConectare.UseVisualStyleBackColor = true;
            this.btnConectare.Click += new System.EventHandler(this.button1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(1054, 98);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 16);
            this.label1.TabIndex = 3;
            this.label1.Text = "Denumire";
            // 
            // denumireTextbox
            // 
            this.denumireTextbox.Location = new System.Drawing.Point(1140, 95);
            this.denumireTextbox.Name = "denumireTextbox";
            this.denumireTextbox.Size = new System.Drawing.Size(202, 22);
            this.denumireTextbox.TabIndex = 4;
            // 
            // producator
            // 
            this.producator.AutoSize = true;
            this.producator.Location = new System.Drawing.Point(1046, 147);
            this.producator.Name = "producator";
            this.producator.Size = new System.Drawing.Size(73, 16);
            this.producator.TabIndex = 6;
            this.producator.Text = "Producator";
            // 
            // producatorTextbox
            // 
            this.producatorTextbox.Location = new System.Drawing.Point(1140, 141);
            this.producatorTextbox.Name = "producatorTextbox";
            this.producatorTextbox.Size = new System.Drawing.Size(202, 22);
            this.producatorTextbox.TabIndex = 7;
            // 
            // pret
            // 
            this.pret.AutoSize = true;
            this.pret.Location = new System.Drawing.Point(1088, 192);
            this.pret.Name = "pret";
            this.pret.Size = new System.Drawing.Size(31, 16);
            this.pret.TabIndex = 8;
            this.pret.Text = "Pret";
            // 
            // pretTextbox
            // 
            this.pretTextbox.Location = new System.Drawing.Point(1140, 186);
            this.pretTextbox.Name = "pretTextbox";
            this.pretTextbox.Size = new System.Drawing.Size(202, 22);
            this.pretTextbox.TabIndex = 9;
            // 
            // stoc
            // 
            this.stoc.AutoSize = true;
            this.stoc.Location = new System.Drawing.Point(1085, 236);
            this.stoc.Name = "stoc";
            this.stoc.Size = new System.Drawing.Size(34, 16);
            this.stoc.TabIndex = 10;
            this.stoc.Text = "Stoc";
            // 
            // stocTextbox
            // 
            this.stocTextbox.Location = new System.Drawing.Point(1140, 230);
            this.stocTextbox.Name = "stocTextbox";
            this.stocTextbox.Size = new System.Drawing.Size(202, 22);
            this.stocTextbox.TabIndex = 11;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(1067, 321);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(116, 51);
            this.button1.TabIndex = 12;
            this.button1.Text = "Inserare";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.inserare_Clicked);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(1226, 321);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(116, 51);
            this.button2.TabIndex = 13;
            this.button2.Text = "Actualizare";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.actualizare_clicked);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(1067, 407);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(116, 51);
            this.button3.TabIndex = 14;
            this.button3.Text = "Stergere";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.stergere_Clicked);
            // 
            // tip
            // 
            this.tip.AutoSize = true;
            this.tip.Location = new System.Drawing.Point(1092, 282);
            this.tip.Name = "tip";
            this.tip.Size = new System.Drawing.Size(27, 16);
            this.tip.TabIndex = 15;
            this.tip.Text = "Tip";
            // 
            // tipTextbox
            // 
            this.tipTextbox.Location = new System.Drawing.Point(1140, 276);
            this.tipTextbox.Name = "tipTextbox";
            this.tipTextbox.Size = new System.Drawing.Size(202, 22);
            this.tipTextbox.TabIndex = 16;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1382, 549);
            this.Controls.Add(this.tipTextbox);
            this.Controls.Add(this.tip);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.stocTextbox);
            this.Controls.Add(this.stoc);
            this.Controls.Add(this.pretTextbox);
            this.Controls.Add(this.pret);
            this.Controls.Add(this.producatorTextbox);
            this.Controls.Add(this.producator);
            this.Controls.Add(this.denumireTextbox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnConectare);
            this.Controls.Add(this.dataGridView2);
            this.Controls.Add(this.dataGridView1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridView dataGridView2;
        private System.Windows.Forms.Button btnConectare;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox denumireTextbox;
        private System.Windows.Forms.Label producator;
        private System.Windows.Forms.TextBox producatorTextbox;
        private System.Windows.Forms.Label pret;
        private System.Windows.Forms.TextBox pretTextbox;
        private System.Windows.Forms.Label stoc;
        private System.Windows.Forms.TextBox stocTextbox;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Label tip;
        private System.Windows.Forms.TextBox tipTextbox;
    }
}

