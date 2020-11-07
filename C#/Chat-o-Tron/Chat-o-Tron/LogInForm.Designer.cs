namespace Chat_o_Tron
{
	partial class LogInForm
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
			this.AcceptButton = new System.Windows.Forms.Button();
			this.Username = new System.Windows.Forms.Label();
			this.Password = new System.Windows.Forms.Label();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.textBox2 = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// AcceptButton
			// 
			this.AcceptButton.Location = new System.Drawing.Point(90, 212);
			this.AcceptButton.Name = "AcceptButton";
			this.AcceptButton.Size = new System.Drawing.Size(75, 23);
			this.AcceptButton.TabIndex = 0;
			this.AcceptButton.Text = "Log in";
			this.AcceptButton.UseVisualStyleBackColor = true;
			this.AcceptButton.Click += new System.EventHandler(this.AcceptButton_Click);
			// 
			// Username
			// 
			this.Username.AutoSize = true;
			this.Username.Location = new System.Drawing.Point(39, 71);
			this.Username.Name = "Username";
			this.Username.Size = new System.Drawing.Size(55, 13);
			this.Username.TabIndex = 2;
			this.Username.Text = "Username";
			// 
			// Password
			// 
			this.Password.AutoSize = true;
			this.Password.Location = new System.Drawing.Point(39, 143);
			this.Password.Name = "Password";
			this.Password.Size = new System.Drawing.Size(53, 13);
			this.Password.TabIndex = 3;
			this.Password.Text = "Password";
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(116, 71);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(100, 20);
			this.textBox1.TabIndex = 4;
			// 
			// textBox2
			// 
			this.textBox2.Location = new System.Drawing.Point(116, 140);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new System.Drawing.Size(100, 20);
			this.textBox2.TabIndex = 5;
			// 
			// LogInForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(278, 341);
			this.Controls.Add(this.textBox2);
			this.Controls.Add(this.textBox1);
			this.Controls.Add(this.Password);
			this.Controls.Add(this.Username);
			this.Controls.Add(this.AcceptButton);
			this.Name = "LogInForm";
			this.Text = "Log in";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button AcceptButton;
		private System.Windows.Forms.Label Username;
		private System.Windows.Forms.Label Password;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.TextBox textBox2;
	}
}

