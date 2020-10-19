namespace TicTacToe
{
	partial class StartForm
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
			this.LogInButton = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.UsernameTB = new System.Windows.Forms.TextBox();
			this.PasswordTB = new System.Windows.Forms.TextBox();
			this.HeaderLabel = new System.Windows.Forms.Label();
			this.NewPlayerButton = new System.Windows.Forms.Button();
			this.WrongPassLabel = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// LogInButton
			// 
			this.LogInButton.Location = new System.Drawing.Point(82, 186);
			this.LogInButton.Name = "LogInButton";
			this.LogInButton.Size = new System.Drawing.Size(75, 23);
			this.LogInButton.TabIndex = 0;
			this.LogInButton.Text = "Log in";
			this.LogInButton.UseVisualStyleBackColor = true;
			this.LogInButton.Click += new System.EventHandler(this.LogInButton_Click);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(12, 92);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(55, 13);
			this.label1.TabIndex = 1;
			this.label1.Text = "Username";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(12, 145);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(53, 13);
			this.label2.TabIndex = 2;
			this.label2.Text = "Password";
			// 
			// UsernameTB
			// 
			this.UsernameTB.Location = new System.Drawing.Point(82, 89);
			this.UsernameTB.MaxLength = 20;
			this.UsernameTB.Name = "UsernameTB";
			this.UsernameTB.Size = new System.Drawing.Size(151, 20);
			this.UsernameTB.TabIndex = 3;
			// 
			// PasswordTB
			// 
			this.PasswordTB.Location = new System.Drawing.Point(82, 138);
			this.PasswordTB.MaxLength = 20;
			this.PasswordTB.Name = "PasswordTB";
			this.PasswordTB.PasswordChar = '*';
			this.PasswordTB.Size = new System.Drawing.Size(151, 20);
			this.PasswordTB.TabIndex = 4;
			// 
			// HeaderLabel
			// 
			this.HeaderLabel.AutoSize = true;
			this.HeaderLabel.Location = new System.Drawing.Point(79, 37);
			this.HeaderLabel.Name = "HeaderLabel";
			this.HeaderLabel.Size = new System.Drawing.Size(78, 13);
			this.HeaderLabel.TabIndex = 5;
			this.HeaderLabel.Text = "Tick-Tack-Toe";
			this.HeaderLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// NewPlayerButton
			// 
			this.NewPlayerButton.Location = new System.Drawing.Point(65, 269);
			this.NewPlayerButton.Name = "NewPlayerButton";
			this.NewPlayerButton.Size = new System.Drawing.Size(112, 23);
			this.NewPlayerButton.TabIndex = 6;
			this.NewPlayerButton.Text = "Create new account";
			this.NewPlayerButton.UseVisualStyleBackColor = true;
			this.NewPlayerButton.Click += new System.EventHandler(this.NewPlayerButton_Click);
			// 
			// WrongPassLabel
			// 
			this.WrongPassLabel.AutoSize = true;
			this.WrongPassLabel.Location = new System.Drawing.Point(44, 234);
			this.WrongPassLabel.Name = "WrongPassLabel";
			this.WrongPassLabel.Size = new System.Drawing.Size(151, 13);
			this.WrongPassLabel.TabIndex = 7;
			this.WrongPassLabel.Text = "Wrong Password or Username";
			this.WrongPassLabel.Visible = false;
			// 
			// StartForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(245, 304);
			this.Controls.Add(this.WrongPassLabel);
			this.Controls.Add(this.NewPlayerButton);
			this.Controls.Add(this.HeaderLabel);
			this.Controls.Add(this.PasswordTB);
			this.Controls.Add(this.UsernameTB);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.LogInButton);
			this.Name = "StartForm";
			this.Text = "StartForm";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button LogInButton;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox UsernameTB;
		private System.Windows.Forms.TextBox PasswordTB;
		private System.Windows.Forms.Label HeaderLabel;
		private System.Windows.Forms.Button NewPlayerButton;
		private System.Windows.Forms.Label WrongPassLabel;
	}
}