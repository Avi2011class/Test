<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.Button1 = New System.Windows.Forms.Button()
        Me.PictureBox1 = New System.Windows.Forms.PictureBox()
        Me.RED = New System.Windows.Forms.PictureBox()
        Me.BLUE = New System.Windows.Forms.PictureBox()
        Me.BLUEUSER = New System.Windows.Forms.PictureBox()
        Me.REDUSER = New System.Windows.Forms.PictureBox()
        Me.Button2 = New System.Windows.Forms.Button()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.RED, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.BLUE, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.BLUEUSER, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.REDUSER, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'Button1
        '
        Me.Button1.Font = New System.Drawing.Font("Monotype Corsiva", 12.0!, CType((System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Italic), System.Drawing.FontStyle), System.Drawing.GraphicsUnit.Point, CType(204, Byte))
        Me.Button1.Location = New System.Drawing.Point(100, 658)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(309, 24)
        Me.Button1.TabIndex = 0
        Me.Button1.Text = "Начать игру сначала."
        Me.Button1.UseVisualStyleBackColor = True
        '
        'PictureBox1
        '
        Me.PictureBox1.BackColor = System.Drawing.Color.Transparent
        Me.PictureBox1.Image = CType(resources.GetObject("PictureBox1.Image"), System.Drawing.Image)
        Me.PictureBox1.Location = New System.Drawing.Point(70, -8)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(70, 40)
        Me.PictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.PictureBox1.TabIndex = 1
        Me.PictureBox1.TabStop = False
        Me.PictureBox1.Visible = False
        '
        'RED
        '
        Me.RED.Image = CType(resources.GetObject("RED.Image"), System.Drawing.Image)
        Me.RED.Location = New System.Drawing.Point(737, 602)
        Me.RED.Name = "RED"
        Me.RED.Size = New System.Drawing.Size(70, 70)
        Me.RED.TabIndex = 2
        Me.RED.TabStop = False
        Me.RED.Visible = False
        '
        'BLUE
        '
        Me.BLUE.Image = CType(resources.GetObject("BLUE.Image"), System.Drawing.Image)
        Me.BLUE.Location = New System.Drawing.Point(737, 502)
        Me.BLUE.Name = "BLUE"
        Me.BLUE.Size = New System.Drawing.Size(70, 70)
        Me.BLUE.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.BLUE.TabIndex = 3
        Me.BLUE.TabStop = False
        Me.BLUE.Visible = False
        '
        'BLUEUSER
        '
        Me.BLUEUSER.Image = CType(resources.GetObject("BLUEUSER.Image"), System.Drawing.Image)
        Me.BLUEUSER.Location = New System.Drawing.Point(737, 91)
        Me.BLUEUSER.Name = "BLUEUSER"
        Me.BLUEUSER.Size = New System.Drawing.Size(70, 70)
        Me.BLUEUSER.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.BLUEUSER.TabIndex = 4
        Me.BLUEUSER.TabStop = False
        Me.BLUEUSER.Visible = False
        '
        'REDUSER
        '
        Me.REDUSER.Image = CType(resources.GetObject("REDUSER.Image"), System.Drawing.Image)
        Me.REDUSER.Location = New System.Drawing.Point(737, 12)
        Me.REDUSER.Name = "REDUSER"
        Me.REDUSER.Size = New System.Drawing.Size(70, 70)
        Me.REDUSER.TabIndex = 5
        Me.REDUSER.TabStop = False
        Me.REDUSER.Visible = False
        '
        'Button2
        '
        Me.Button2.Font = New System.Drawing.Font("Monotype Corsiva", 9.75!, CType((System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Italic), System.Drawing.FontStyle), System.Drawing.GraphicsUnit.Point, CType(204, Byte))
        Me.Button2.Location = New System.Drawing.Point(722, 678)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(98, 28)
        Me.Button2.TabIndex = 7
        Me.Button2.Text = "Инфо"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.Color.White
        Me.ClientSize = New System.Drawing.Size(832, 707)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.REDUSER)
        Me.Controls.Add(Me.BLUEUSER)
        Me.Controls.Add(Me.BLUE)
        Me.Controls.Add(Me.RED)
        Me.Controls.Add(Me.PictureBox1)
        Me.Controls.Add(Me.Button1)
        Me.Name = "Form1"
        Me.Text = "Четыре в ряд"
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.RED, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.BLUE, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.BLUEUSER, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.REDUSER, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents PictureBox1 As System.Windows.Forms.PictureBox
    Friend WithEvents RED As System.Windows.Forms.PictureBox
    Friend WithEvents BLUE As System.Windows.Forms.PictureBox
    Friend WithEvents BLUEUSER As System.Windows.Forms.PictureBox
    Friend WithEvents REDUSER As System.Windows.Forms.PictureBox
    Friend WithEvents Button2 As System.Windows.Forms.Button

End Class
