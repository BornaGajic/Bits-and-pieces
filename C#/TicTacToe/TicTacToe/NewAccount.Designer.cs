namespace TicTacToe
{
	partial class NewAccount
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
			this.usernamelabel = new System.Windows.Forms.Label();
			this.NewAccountUsernameTB = new System.Windows.Forms.TextBox();
			this.NewAccountAcceptButton = new System.Windows.Forms.Button();
			this.NewPassLabel = new System.Windows.Forms.Label();
			this.NewAccountPasswordTB = new System.Windows.Forms.TextBox();
			this.ErrorLabel = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// usernamelabel
			// 
			this.usernamelabel.AutoSize = true;
			this.usernamelabel.Location = new System.Drawing.Point(12, 45);
			this.usernamelabel.Name = "usernamelabel";
			this.usernamelabel.Size = new System.Drawing.Size(55, 13);
			this.usernamelabel.TabIndex = 0;
			this.usernamelabel.Text = "Username";
			this.usernamelabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// NewAccountUsernameTB
			// 
			this.NewAccountUsernameTB.Location = new System.Drawing.Point(73, 42);
			this.NewAccountUsernameTB.MaxLength = 20;
			this.NewAccountUsernameTB.Name = "NewAccountUsernameTB";
			this.NewAccountUsernameTB.Size = new System.Drawing.Size(152, 20);
			this.NewAccountUsernameTB.TabIndex = 1;
			// 
			// NewAccountAcceptButton
			// 
			this.NewAccountAcceptButton.Location = new System.Drawing.Point(82, 163);
			this.NewAccountAcceptButton.Name = "NewAccountAcceptButton";
			this.NewAccountAcceptButton.Size = new System.Drawing.Size(75, 23);
			this.NewAccountAcceptButton.TabIndex = 2;
			this.NewAccountAcceptButton.Text = "Accept";
			this.NewAccountAcceptButton.UseVisualStyleBackColor = true;
			this.NewAccountAcceptButton.Click += new System.EventHandler(this.NewAccountAcceptButton_Click);
			// 
			// NewPassLabel
			// 
			this.NewPassLabel.AutoSize = true;
			this.NewPassLabel.Location = new System.Drawing.Point(14, 107);
			this.NewPassLabel.Name = "NewPassLabel";
			this.NewPassLabel.Size = new System.Drawing.Size(53, 13);
			this.NewPassLabel.TabIndex = 3;
			this.NewPassLabel.Text = "Password";
			// 
			// NewAccountPasswordTB
			// 
			this.NewAccountPasswordTB.Location = new System.Drawing.Point(73, 100);
			this.NewAccountPasswordTB.MaxLength = 20;
			this.NewAccountPasswordTB.Name = "NewAccountPasswordTB";
			this.NewAccountPasswordTB.PasswordChar = '*';
			this.NewAccountPasswordTB.Size = new System.Drawing.Size(152, 20);
			this.NewAccountPasswordTB.TabIndex = 4;
			// 
			// ErrorLabel
			// 
			this.ErrorLabel.AutoSize = true;
			this.ErrorLabel.Location = new System.Drawing.Point(101, 138);
			this.ErrorLabel.Name = "ErrorLabel";
			this.ErrorLabel.Size = new System.Drawing.Size(0, 13);
			this.ErrorLabel.TabIndex = 5;
			// 
			// NewAccount
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(250, 198);
			this.Controls.Add(this.ErrorLabel);
			this.Controls.Add(this.NewAccountPasswordTB);
			this.Controls.Add(this.NewPassLabel);
			this.Controls.Add(this.NewAccountAcceptButton);
			this.Controls.Add(this.NewAccountUsernameTB);
			this.Controls.Add(this.usernamelabel);
			this.Name = "NewAccount";
			this.Text = "New Account";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label usernamelabel;
		private System.Windows.Forms.TextBox NewAccountUsernameTB;
		private System.Windows.Forms.Button NewAccountAcceptButton;
		private System.Windows.Forms.Label NewPassLabel;
		private System.Windows.Forms.TextBox NewAccountPasswordTB;
		private System.Windows.Forms.Label ErrorLabel;
	}
}