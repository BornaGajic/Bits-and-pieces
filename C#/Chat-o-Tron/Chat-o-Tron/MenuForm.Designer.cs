namespace Chat_o_Tron
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
			this.CreateRoomButton = new System.Windows.Forms.Button();
			this.button1 = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.button3 = new System.Windows.Forms.Button();
			this.RefreshButton = new System.Windows.Forms.Button();
			this.tableLayoutPanel1.SuspendLayout();
			this.SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this.tableLayoutPanel1.ColumnCount = 2;
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 71.54472F));
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 28.45528F));
			this.tableLayoutPanel1.Controls.Add(this.CreateRoomButton, 1, 0);
			this.tableLayoutPanel1.Controls.Add(this.button1, 0, 1);
			this.tableLayoutPanel1.Controls.Add(this.button2, 0, 2);
			this.tableLayoutPanel1.Controls.Add(this.button3, 0, 3);
			this.tableLayoutPanel1.Controls.Add(this.RefreshButton, 1, 3);
			this.tableLayoutPanel1.Location = new System.Drawing.Point(12, 12);
			this.tableLayoutPanel1.Name = "tableLayoutPanel1";
			this.tableLayoutPanel1.RowCount = 4;
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 27.94118F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 72.05882F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 126F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 124F));
			this.tableLayoutPanel1.Size = new System.Drawing.Size(492, 409);
			this.tableLayoutPanel1.TabIndex = 0;
			// 
			// CreateRoomButton
			// 
			this.CreateRoomButton.Dock = System.Windows.Forms.DockStyle.Fill;
			this.CreateRoomButton.Location = new System.Drawing.Point(355, 3);
			this.CreateRoomButton.Name = "CreateRoomButton";
			this.CreateRoomButton.Size = new System.Drawing.Size(134, 38);
			this.CreateRoomButton.TabIndex = 0;
			this.CreateRoomButton.Text = "Create Room";
			this.CreateRoomButton.UseVisualStyleBackColor = true;
			this.CreateRoomButton.Click += new System.EventHandler(this.CreateRoomButton_Click);
			// 
			// button1
			// 
			this.button1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.button1.Location = new System.Drawing.Point(3, 47);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(346, 108);
			this.button1.TabIndex = 1;
			this.button1.UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this.button2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.button2.Location = new System.Drawing.Point(3, 161);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(346, 120);
			this.button2.TabIndex = 2;
			this.button2.UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this.button3.Dock = System.Windows.Forms.DockStyle.Fill;
			this.button3.Location = new System.Drawing.Point(3, 287);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(346, 119);
			this.button3.TabIndex = 3;
			this.button3.UseVisualStyleBackColor = true;
			// 
			// RefreshButton
			// 
			this.RefreshButton.Location = new System.Drawing.Point(355, 287);
			this.RefreshButton.Name = "RefreshButton";
			this.RefreshButton.Size = new System.Drawing.Size(134, 58);
			this.RefreshButton.TabIndex = 4;
			this.RefreshButton.Text = "Refresh List";
			this.RefreshButton.UseVisualStyleBackColor = true;
			// 
			// MenuForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(516, 433);
			this.Controls.Add(this.tableLayoutPanel1);
			this.Name = "MenuForm";
			this.Text = "MenuForm";
			this.Shown += new System.EventHandler(this.MenuForm_Shown);
			this.tableLayoutPanel1.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
		private System.Windows.Forms.Button CreateRoomButton;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.Button RefreshButton;
	}
}