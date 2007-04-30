using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace TestPolygon
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        const String RETURN_CODE = "\r\n";
        private void button1_Click(object sender, EventArgs e)
        {
            //ボタンをクリックしたらいろいろする
            textBox2.Text = "hogepiyo";
        }
    }
}