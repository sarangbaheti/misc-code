namespace ScreenCaptureApp
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.StartButton = new System.Windows.Forms.Button();
            this.StopButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.AppListComboBox = new System.Windows.Forms.ComboBox();
            this.DimensionsLabel = new System.Windows.Forms.Label();
            this.NewWidthTextBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.NewHeightTextBox = new System.Windows.Forms.TextBox();
            this.ReSizeButton = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.DataRateComboBox = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.FrameRateComboBox = new System.Windows.Forms.ComboBox();
            this.AudioComboBox = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.ResolutionComboBox = new System.Windows.Forms.ComboBox();
            this.MarkerWindowButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // StartButton
            // 
            this.StartButton.Image = ((System.Drawing.Image)(resources.GetObject("StartButton.Image")));
            this.StartButton.Location = new System.Drawing.Point(12, 252);
            this.StartButton.Name = "StartButton";
            this.StartButton.Size = new System.Drawing.Size(64, 61);
            this.StartButton.TabIndex = 7;
            this.StartButton.UseVisualStyleBackColor = true;
            this.StartButton.Click += new System.EventHandler(this.StartButton_Click);
            // 
            // StopButton
            // 
            this.StopButton.Enabled = false;
            this.StopButton.Image = ((System.Drawing.Image)(resources.GetObject("StopButton.Image")));
            this.StopButton.Location = new System.Drawing.Point(82, 252);
            this.StopButton.Name = "StopButton";
            this.StopButton.Size = new System.Drawing.Size(64, 61);
            this.StopButton.TabIndex = 8;
            this.StopButton.UseVisualStyleBackColor = true;
            this.StopButton.Click += new System.EventHandler(this.StopButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(9, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 19);
            this.label1.TabIndex = 2;
            this.label1.Text = "App:";
            // 
            // AppListComboBox
            // 
            this.AppListComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.AppListComboBox.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold);
            this.AppListComboBox.FormattingEnabled = true;
            this.AppListComboBox.Location = new System.Drawing.Point(54, 12);
            this.AppListComboBox.Name = "AppListComboBox";
            this.AppListComboBox.Size = new System.Drawing.Size(320, 27);
            this.AppListComboBox.TabIndex = 0;
            this.AppListComboBox.DropDown += new System.EventHandler(this.AppListComboBox_DropDown);
            this.AppListComboBox.SelectedIndexChanged += new System.EventHandler(this.AppListComboBox_SelectedIndexChanged);
            // 
            // DimensionsLabel
            // 
            this.DimensionsLabel.AutoSize = true;
            this.DimensionsLabel.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.DimensionsLabel.Location = new System.Drawing.Point(8, 48);
            this.DimensionsLabel.Name = "DimensionsLabel";
            this.DimensionsLabel.Size = new System.Drawing.Size(147, 19);
            this.DimensionsLabel.TabIndex = 2;
            this.DimensionsLabel.Text = "Current Dimensions:";
            // 
            // NewWidthTextBox
            // 
            this.NewWidthTextBox.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold);
            this.NewWidthTextBox.Location = new System.Drawing.Point(65, 111);
            this.NewWidthTextBox.Name = "NewWidthTextBox";
            this.NewWidthTextBox.Size = new System.Drawing.Size(70, 27);
            this.NewWidthTextBox.TabIndex = 1;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(9, 114);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(56, 19);
            this.label3.TabIndex = 2;
            this.label3.Text = "Width:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(141, 114);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(58, 19);
            this.label4.TabIndex = 2;
            this.label4.Text = "Height:";
            // 
            // NewHeightTextBox
            // 
            this.NewHeightTextBox.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold);
            this.NewHeightTextBox.Location = new System.Drawing.Point(201, 111);
            this.NewHeightTextBox.Name = "NewHeightTextBox";
            this.NewHeightTextBox.Size = new System.Drawing.Size(70, 27);
            this.NewHeightTextBox.TabIndex = 2;
            // 
            // ReSizeButton
            // 
            this.ReSizeButton.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold);
            this.ReSizeButton.Location = new System.Drawing.Point(284, 111);
            this.ReSizeButton.Name = "ReSizeButton";
            this.ReSizeButton.Size = new System.Drawing.Size(90, 28);
            this.ReSizeButton.TabIndex = 3;
            this.ReSizeButton.Text = "Resize";
            this.ReSizeButton.UseVisualStyleBackColor = true;
            this.ReSizeButton.Click += new System.EventHandler(this.Resize_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(10, 154);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(113, 19);
            this.label5.TabIndex = 2;
            this.label5.Text = "Max Data Rate:";
            this.label5.Click += new System.EventHandler(this.label5_Click);
            // 
            // DataRateComboBox
            // 
            this.DataRateComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.DataRateComboBox.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold);
            this.DataRateComboBox.FormattingEnabled = true;
            this.DataRateComboBox.Location = new System.Drawing.Point(128, 151);
            this.DataRateComboBox.Name = "DataRateComboBox";
            this.DataRateComboBox.Size = new System.Drawing.Size(246, 27);
            this.DataRateComboBox.TabIndex = 4;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(32, 187);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(90, 19);
            this.label2.TabIndex = 2;
            this.label2.Text = "Frame Rate:";
            // 
            // FrameRateComboBox
            // 
            this.FrameRateComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FrameRateComboBox.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold);
            this.FrameRateComboBox.FormattingEnabled = true;
            this.FrameRateComboBox.Location = new System.Drawing.Point(128, 184);
            this.FrameRateComboBox.Name = "FrameRateComboBox";
            this.FrameRateComboBox.Size = new System.Drawing.Size(246, 27);
            this.FrameRateComboBox.TabIndex = 5;
            // 
            // AudioComboBox
            // 
            this.AudioComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.AudioComboBox.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold);
            this.AudioComboBox.FormattingEnabled = true;
            this.AudioComboBox.Location = new System.Drawing.Point(128, 217);
            this.AudioComboBox.Name = "AudioComboBox";
            this.AudioComboBox.Size = new System.Drawing.Size(246, 27);
            this.AudioComboBox.TabIndex = 6;
            this.AudioComboBox.DropDown += new System.EventHandler(this.AudioComboBox_DropDown);
            this.AudioComboBox.SelectedIndexChanged += new System.EventHandler(this.AudioComboBox_SelectedIndexChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(68, 220);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(54, 19);
            this.label6.TabIndex = 6;
            this.label6.Text = "Audio:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(9, 78);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(85, 19);
            this.label7.TabIndex = 2;
            this.label7.Text = "Resolution:";
            // 
            // ResolutionComboBox
            // 
            this.ResolutionComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ResolutionComboBox.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold);
            this.ResolutionComboBox.FormattingEnabled = true;
            this.ResolutionComboBox.Location = new System.Drawing.Point(103, 75);
            this.ResolutionComboBox.Name = "ResolutionComboBox";
            this.ResolutionComboBox.Size = new System.Drawing.Size(271, 27);
            this.ResolutionComboBox.TabIndex = 4;
            this.ResolutionComboBox.SelectedIndexChanged += new System.EventHandler(this.ResolutionComboBox_SelectedIndexChanged);
            // 
            // MarkerWindowButton
            // 
            this.MarkerWindowButton.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold);
            this.MarkerWindowButton.Location = new System.Drawing.Point(152, 252);
            this.MarkerWindowButton.Name = "MarkerWindowButton";
            this.MarkerWindowButton.Size = new System.Drawing.Size(222, 28);
            this.MarkerWindowButton.TabIndex = 3;
            this.MarkerWindowButton.Text = "Use Marker Window";
            this.MarkerWindowButton.UseVisualStyleBackColor = true;
            this.MarkerWindowButton.Click += new System.EventHandler(this.MarkerWindow_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(386, 325);
            this.Controls.Add(this.AudioComboBox);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.NewHeightTextBox);
            this.Controls.Add(this.NewWidthTextBox);
            this.Controls.Add(this.FrameRateComboBox);
            this.Controls.Add(this.ResolutionComboBox);
            this.Controls.Add(this.DataRateComboBox);
            this.Controls.Add(this.AppListComboBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.DimensionsLabel);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.MarkerWindowButton);
            this.Controls.Add(this.ReSizeButton);
            this.Controls.Add(this.StopButton);
            this.Controls.Add(this.StartButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Direct Video Capture";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button StartButton;
        private System.Windows.Forms.Button StopButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox AppListComboBox;
        private System.Windows.Forms.Label DimensionsLabel;
        private System.Windows.Forms.TextBox NewWidthTextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox NewHeightTextBox;
        private System.Windows.Forms.Button ReSizeButton;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox DataRateComboBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox FrameRateComboBox;
        private System.Windows.Forms.ComboBox AudioComboBox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox ResolutionComboBox;
        private System.Windows.Forms.Button MarkerWindowButton;
    }
}

