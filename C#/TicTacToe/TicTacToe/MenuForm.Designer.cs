namespace TicTacToe
{
	partial class MenuForm
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
			this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
			this.LocalButton = new System.Windows.Forms.Button();
			this.OnlineButton = new System.Windows.Forms.Button();
			this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			this.UsernameLabel = new System.Windows.Forms.Label();
			this.WinsLabel = new System.Windows.Forms.Label();
			this.LosesLabel = new System.Windows.Forms.Label();
			this.tableLayoutPanel1.SuspendLayout();
			this.tableLayoutPanel2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
			this.SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this.tableLayoutPanel1.ColumnCount = 3;
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 22.69939F));
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 77.30061F));
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 82F));
			this.tableLayoutPanel1.Controls.Add(this.LocalButton, 1, 1);
			this.tableLayoutPanel1.Controls.Add(this.OnlineButton, 1, 2);
			this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 1, 3);
			this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
			this.tableLayoutPanel1.Name = "tableLayoutPanel1";
			this.tableLayoutPanel1.RowCount = 4;
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 49.46236F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50.53764F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 67F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 342F));
			this.tableLayoutPanel1.Size = new System.Drawing.Size(409, 536);
			this.tableLayoutPanel1.TabIndex = 0;
			// 
			// LocalButton
			// 
			this.LocalButton.Dock = System.Windows.Forms.DockStyle.Fill;
			this.LocalButton.Location = new System.Drawing.Point(77, 65);
			this.LocalButton.Name = "LocalButton";
			this.LocalButton.Size = new System.Drawing.Size(246, 58);
			this.LocalButton.TabIndex = 0;
			this.LocalButton.Text = "Local";
			this.LocalButton.UseVisualStyleBackColor = true;
			this.LocalButton.Click += new System.EventHandler(this.LocalButton_Click);
			// 
			// OnlineButton
			// 
			this.OnlineButton.Dock = System.Windows.Forms.DockStyle.Fill;
			this.OnlineButton.Location = new System.Drawing.Point(77, 129);
			this.OnlineButton.Name = "OnlineButton";
			this.OnlineButton.Size = new System.Drawing.Size(246, 61);
			this.OnlineButton.TabIndex = 1;
			this.OnlineButton.Text = "Online";
			this.OnlineButton.UseVisualStyleBackColor = true;
			// 
			// tableLayoutPanel2
			// 
			this.tableLayoutPanel2.ColumnCount = 2;
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
			this.tableLayoutPanel2.Controls.Add(this.pictureBox1, 0, 0);
			this.tableLayoutPanel2.Controls.Add(this.UsernameLabel, 1, 0);
			this.tableLayoutPanel2.Controls.Add(this.WinsLabel, 0, 1);
			this.tableLayoutPanel2.Controls.Add(this.LosesLabel, 1, 1);
			this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel2.Location = new System.Drawing.Point(77, 196);
			this.tableLayoutPanel2.Name = "tableLayoutPanel2";
			this.tableLayoutPanel2.RowCount = 3;
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 52.08333F));
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 47.91667F));
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 195F));
			this.tableLayoutPanel2.Size = new System.Drawing.Size(246, 337);
			this.tableLayoutPanel2.TabIndex = 2;
			// 
			// pictureBox1
			// 
			this.pictureBox1.Location = new System.Drawing.Point(3, 3);
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size(117, 67);
			this.pictureBox1.TabIndex = 0;
			this.pictureBox1.TabStop = false;
			// 
			// UsernameLabel
			// 
			this.UsernameLabel.AutoSize = true;
			this.UsernameLabel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.UsernameLabel.Location = new System.Drawing.Point(126, 0);
			this.UsernameLabel.Name = "UsernameLabel";
			this.UsernameLabel.Size = new System.Drawing.Size(117, 73);
			this.UsernameLabel.TabIndex = 1;
			this.UsernameLabel.Text = "Player username";
			this.UsernameLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// WinsLabel
			// 
			this.WinsLabel.AutoSize = true;
			this.WinsLabel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.WinsLabel.Location = new System.Drawing.Point(3, 73);
			this.WinsLabel.Name = "WinsLabel";
			this.WinsLabel.Size = new System.Drawing.Size(117, 68);
			this.WinsLabel.TabIndex = 2;
			this.WinsLabel.Text = "Wins: ";
			this.WinsLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// LosesLabel
			// 
			this.LosesLabel.AutoSize = true;
			this.LosesLabel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.LosesLabel.Location = new System.Drawing.Point(126, 73);
			this.LosesLabel.Name = "LosesLabel";
			this.LosesLabel.Size = new System.Drawing.Size(117, 68);
			this.LosesLabel.TabIndex = 3;
			this.LosesLabel.Text = "Loses: ";
			this.LosesLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// MenuForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(409, 536);
			this.Controls.Add(this.tableLayoutPanel1);
			this.Name = "MenuForm";
			this.Text = "MenuForm";
			this.tableLayoutPanel1.ResumeLayout(false);
			this.tableLayoutPanel2.ResumeLayout(false);
			this.tableLayoutPanel2.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
		private System.Windows.Forms.Button LocalButton;
		private System.Windows.Forms.Button OnlineButton;
		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
		private System.Windows.Forms.PictureBox pictureBox1;
		private System.Windows.Forms.Label UsernameLabel;
		private System.Windows.Forms.Label WinsLabel;
		private System.Windows.Forms.Label LosesLabel;
	}
}