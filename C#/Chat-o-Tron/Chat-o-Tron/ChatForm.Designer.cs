﻿namespace Chat_o_Tron
{
	partial class ChatForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose (bool disposing)
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
		private void InitializeComponent ()
		{
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.SendButton = new System.Windows.Forms.Button();
			this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
			this.ResponseLabel = new System.Windows.Forms.Label();
			this.tableLayoutPanel1.SuspendLayout();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(12, 317);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(376, 139);
			this.textBox1.TabIndex = 1;
			// 
			// SendButton
			// 
			this.SendButton.Location = new System.Drawing.Point(12, 463);
			this.SendButton.Name = "SendButton";
			this.SendButton.Size = new System.Drawing.Size(376, 23);
			this.SendButton.TabIndex = 2;
			this.SendButton.Text = "Send";
			this.SendButton.UseVisualStyleBackColor = true;
			this.SendButton.Click += new System.EventHandler(this.SendButton_Click);
			// 
			// tableLayoutPanel1
			// 
			this.tableLayoutPanel1.ColumnCount = 1;
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.tableLayoutPanel1.Controls.Add(this.ResponseLabel, 0, 0);
			this.tableLayoutPanel1.Location = new System.Drawing.Point(12, 12);
			this.tableLayoutPanel1.Name = "tableLayoutPanel1";
			this.tableLayoutPanel1.RowCount = 1;
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.tableLayoutPanel1.Size = new System.Drawing.Size(376, 299);
			this.tableLayoutPanel1.TabIndex = 3;
			// 
			// ResponseLabel
			// 
			this.ResponseLabel.AutoSize = true;
			this.ResponseLabel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.ResponseLabel.Location = new System.Drawing.Point(3, 0);
			this.ResponseLabel.Name = "ResponseLabel";
			this.ResponseLabel.Size = new System.Drawing.Size(370, 299);
			this.ResponseLabel.TabIndex = 0;
			this.ResponseLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// ChatForm
			// 
			this.AcceptButton = this.SendButton;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(400, 498);
			this.Controls.Add(this.tableLayoutPanel1);
			this.Controls.Add(this.SendButton);
			this.Controls.Add(this.textBox1);
			this.Name = "ChatForm";
			this.Text = "ChatForm";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ChatForm_FormClosing);
			this.tableLayoutPanel1.ResumeLayout(false);
			this.tableLayoutPanel1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Button SendButton;
		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
		private System.Windows.Forms.Label ResponseLabel;
	}
}