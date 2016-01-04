using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
namespace WindowsFormsApplication2
{

    public partial class Form1 : Form
    {
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
            this.Graph = new System.Windows.Forms.PictureBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.Graph)).BeginInit();
            this.SuspendLayout();
            // 
            // Graph
            // 
            this.Graph.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Graph.Location = new System.Drawing.Point(12, 12);
            this.Graph.Name = "Graph";
            this.Graph.Size = new System.Drawing.Size(840, 620);
            this.Graph.TabIndex = 0;
            this.Graph.TabStop = false;
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.button1.Location = new System.Drawing.Point(860, 35);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(133, 48);
            this.button1.TabIndex = 1;
            this.button1.Text = "Отрисовка";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.button2.Location = new System.Drawing.Point(860, 89);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(133, 48);
            this.button2.TabIndex = 2;
            this.button2.Text = "Отрисовка";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(1005, 642);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.Graph);
            this.Name = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.Graph)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.PictureBox Graph;
        private System.Windows.Forms.Button button1;

        double f(double x)
        {
            return 100 * 1 / (1 - 0.5 * Math.Cos(x));
        }
      
        public Form1()
        {
            InitializeComponent();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            System.Drawing.Graphics g = Graph.CreateGraphics();
            for (double j = 0; j < 1; j += 0.0833)
            {
                double i=j*3.141590;
                Point p1 = new Point((int)(Graph.Size.Width / 2 - 1000 * Math.Cos(i)), (int)(Graph.Size.Height / 2 - 1000 * Math.Sin(i)));
                Point p2 = new Point((int)(Graph.Size.Width / 2 + 1000 * Math.Cos(i)), (int)(Graph.Size.Height / 2 + 1000 * Math.Sin(i)));
                Pen p = new Pen(Color.Black);
                if((j==0)||(Math.Abs(j-0.5)<0.02)) p.Width=3; 
                g.DrawLine(p, p1, p2);
            }
            for (int j = 1; j < 40; j ++)
            {
                Pen p = new Pen(Color.Black);
                if(j%4==0) p.Width = 2; 
                g.DrawEllipse(p,(int)(Graph.Size.Width / 2 - j * 25), (int)(Graph.Size.Height / 2) - j * 25,j * 50, j * 50);
            }
            double start=-30, stop=30,step=0.01;

            Point PS = new Point((int)((Graph.Size.Width / 2) + f(start) * Math.Cos(start)), (int)((Graph.Size.Height / 2) - f(start) * Math.Sin(start)));
            Point PT;
            for (double j = start+step; j < stop; j += step)
            {
                Pen p = new Pen(Color.Red);
                p.Width = 2;
                PT = new Point((int)((Graph.Size.Width / 2) + f(j) * Math.Cos(j)), (int)((Graph.Size.Height / 2) - f(j) * Math.Sin(j)));
                if(Math.Abs(f(j)-f(j-step))<10000) g.DrawLine(p, PS, PT);
           
                PS = PT;

               // System.Threading.Thread.Sleep(1);
            }
        }

      
        }
    }

