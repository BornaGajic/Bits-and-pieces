namespace TicTacToe
{
	partial class NewSaveForm
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
			this.newsavetextbox = new System.Windows.Forms.TextBox();
			this.newsaveaccept = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// usernamelabel
			// 
			this.usernamelabel.AutoSize = true;
			this.usernamelabel.Location = new System.Drawing.Point(71, 28);
			this.usernamelabel.Name = "usernamelabel";
			this.usernamelabel.Size = new System.Drawing.Size(41, 13);
			this.usernamelabel.TabIndex = 0;
			this.usernamelabel.Text = "Name: ";
			// 
			// newsavetextbox
			// 
			this.newsavetextbox.Location = new System.Drawing.Point(118, 28);
			this.newsavetextbox.MaxLength = 20;
			this.newsavetextbox.Name = "newsavetextbox";
			this.newsavetextbox.Size = new System.Drawing.Size(136, 20);
			this.newsavetextbox.TabIndex = 1;
			// 
			// newsaveaccept
			// 
			this.newsaveaccept.Location = new System.Drawing.Point(127, 75);
			this.newsaveaccept.Name = "newsaveaccept";
			this.newsaveaccept.Size = new System.Drawing.Size(75, 23);
			this.newsaveaccept.TabIndex = 2;
			this.newsaveaccept.Text = "Accept";
			this.newsaveaccept.UseVisualStyleBackColor = true;
			this.newsaveaccept.Click += new System.EventHandler(this.newsaveaccept_Click);
			// 
			// NewSaveForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(334, 126);
			this.Controls.Add(this.newsaveaccept);
			this.Controls.Add(this.newsavetextbox);
			this.Controls.Add(this.usernamelabel);
			this.Name = "NewSaveForm";
			this.Text = "NewSaveForm";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label usernamelabel;
		private System.Windows.Forms.TextBox newsavetextbox;
		private System.Windows.Forms.Button newsaveaccept;
	}
}