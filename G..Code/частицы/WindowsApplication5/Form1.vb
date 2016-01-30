Public Class Form1
    Dim Vector(10000) As System.Drawing.Point
    Dim BrounVector(10000) As System.Drawing.Point
    Dim Buttons(10000) As PictureBox
    Dim BrounButtons(10000) As PictureBox
    Dim Broun As Boolean
    Dim N As Integer
    Dim BrounN As Integer
    Dim razm As Integer
    Dim BrounRazm As Integer
    Function rast(i As Integer, j As Integer) As Integer
        Dim t As Integer
        Dim x1 As Integer = Buttons(i).Location.X
        Dim x2 As Integer = BrounButtons(j).Location.X
        Dim y1 As Integer = Buttons(i).Location.Y
        Dim y2 As Integer = BrounButtons(j).Location.Y
        t = ((x1 - x2) ^ 2 + (y1 - y2) ^ 2) ^ 0.5
        Return t
    End Function
    Sub start()
        GroupBox2.Controls.Clear()
        N = NumericUpDown1.Value
        razm = TrackBar2.Value

        Dim k As Integer = TrackBar1.Value * 2
        Dim r As New Random
        Dim p As System.Drawing.Point
        Dim i As Integer
        For i = 0 To N
            p.X = r.Next(-k, k)
            p.Y = r.Next(-k, k)
            Vector(i) = p
        Next

        For i = 0 To N
            Dim b As New PictureBox
            p.X = r.Next(0, GroupBox2.Width - razm)
            p.Y = r.Next(0, GroupBox2.Width - razm)
            b.Location = p
            b.Width = razm
            b.Height = razm
            b.Text = ""
            b.Visible = True
            k = r.Next(1, 5)
            If k = 1 Then b.Image = PictureBox1.Image
            If k = 2 Then b.Image = PictureBox2.Image
            If k = 3 Then b.Image = PictureBox3.Image
            If k = 4 Then b.Image = PictureBox4.Image
            b.SizeMode = PictureBoxSizeMode.StretchImage
            Buttons(i) = b
            GroupBox2.Controls.Add(Buttons(i))
        Next
        Broun = CheckBox1.Checked
        If Broun = True Then
            BrounRazm = TrackBar3.Value
            BrounN = NumericUpDown2.Value
            k = TrackBar4.Value * 2
            For i = 0 To BrounN
                p.X = r.Next(-k, k)
                p.Y = r.Next(-k, k)
                BrounVector(i) = p
            Next
            For i = 0 To BrounN
                Dim b As New PictureBox
                p.X = r.Next(0, GroupBox2.Width - BrounRazm)
                p.Y = r.Next(0, GroupBox2.Width - BrounRazm)
                b.Location = p
                b.Width = BrounRazm
                b.Height = BrounRazm
                b.Text = ""
                b.Visible = True
                k = r.Next(1, 5)
                If k = 1 Then b.Image = PictureBox1.Image
                If k = 2 Then b.Image = PictureBox2.Image
                If k = 3 Then b.Image = PictureBox3.Image
                If k = 4 Then b.Image = PictureBox4.Image
                b.SizeMode = PictureBoxSizeMode.StretchImage
                BrounButtons(i) = b
                GroupBox2.Controls.Add(BrounButtons(i))
            Next
        End If
        Timer1.Enabled = True
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Dim mem As System.Drawing.Point
        Dim b As New PictureBox
        Dim p As System.Drawing.Point
        If Broun = True Then
            For i = 0 To N
                For j = 0 To BrounN
                    If rast(i, j) < BrounRazm Then
                        mem = Vector(i)
                        Vector(i) = BrounVector(j)
                        BrounVector(j) = mem
                        BrounVector(j).X *= razm / BrounRazm
                        BrounVector(j).Y *= razm / BrounRazm
                        Vector(i).X /= razm / BrounRazm
                        Vector(i).Y /= razm / BrounRazm
                    End If
                Next
            Next
        End If


        For i = 0 To N

            b = Buttons(i)
            p = b.Location
            If p.X > GroupBox2.Width - razm - 20 Then
                Vector(i).X = -((Vector(i).X * Vector(i).X) ^ 0.5)
            End If
            If p.Y > GroupBox2.Height - razm - 20 Then
                Vector(i).Y = -((Vector(i).Y * Vector(i).Y) ^ 0.5)
            End If
            If p.X < 20 Then
                Vector(i).X = ((Vector(i).X * Vector(i).X) ^ 0.5)
            End If
            If p.Y < 20 Then
                Vector(i).Y = ((Vector(i).Y * Vector(i).Y) ^ 0.5)
            End If

            For j = i + 1 To N
                If Buttons(i).Location.X - Buttons(j).Location.X < razm And Buttons(i).Location.X - Buttons(j).Location.X > -razm And Buttons(i).Location.Y - Buttons(j).Location.Y < razm And Buttons(i).Location.Y - Buttons(j).Location.Y > -razm Then
                    ' If (buttons(i).Location.X - buttons(j).Location.X) * (vector(j).X - vector(i).X) > 0 And (buttons(i).Location.Y - buttons(j).Location.Y) * (vector(j).Y - vector(i).Y) > 0 Then
                    mem = Vector(i)
                    Vector(i) = Vector(j)
                    Vector(j) = mem
                    'End If
                    p.X += Vector(i).X
                    p.Y += Vector(i).Y
                End If
                p.X += Vector(i).X
                p.Y += Vector(i).Y
            Next

            b.Location = p
            Buttons(i) = b
        Next
        If Broun = True Then
            For i = 0 To BrounN

                b = BrounButtons(i)
                p = b.Location
                If p.X > GroupBox2.Width - BrounRazm - 20 Then
                    BrounVector(i).X = -((BrounVector(i).X * BrounVector(i).X) ^ 0.5)
                End If
                If p.Y > GroupBox2.Height - BrounRazm - 20 Then
                    BrounVector(i).Y = -((BrounVector(i).Y * BrounVector(i).Y) ^ 0.5)
                End If
                If p.X < 20 Then
                    BrounVector(i).X = ((BrounVector(i).X * BrounVector(i).X) ^ 0.5)
                End If
                If p.Y < 20 Then
                    BrounVector(i).Y = ((BrounVector(i).Y * BrounVector(i).Y) ^ 0.5)
                End If

                For j = i + 1 To BrounN
                    If BrounButtons(i).Location.X - BrounButtons(j).Location.X < BrounRazm And BrounButtons(i).Location.X - BrounButtons(j).Location.X > -BrounRazm And BrounButtons(i).Location.Y - BrounButtons(j).Location.Y < BrounRazm And BrounButtons(i).Location.Y - BrounButtons(j).Location.Y > -BrounRazm Then
                        ' If (buttons(i).Location.X - buttons(j).Location.X) * (vector(j).X - vector(i).X) > 0 And (buttons(i).Location.Y - buttons(j).Location.Y) * (vector(j).Y - vector(i).Y) > 0 Then
                        mem = BrounVector(i)
                        BrounVector(i) = BrounVector(j)
                        BrounVector(j) = mem
                        'End If
                        p.X += BrounVector(i).X
                        p.Y += BrounVector(i).Y
                    End If
                Next
                p.X += BrounVector(i).X
                p.Y += BrounVector(i).Y
                b.Location = p
                BrounButtons(i) = b
            Next
        End If




    End Sub

   
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        start()
        Button2.Visible = True
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click

        Timer1.Enabled = Not Timer1.Enabled

    End Sub




    Private Sub Timer2_Tick(sender As Object, e As EventArgs) Handles Timer2.Tick
        GroupBox2.Height = Me.Height - 53
        GroupBox2.Width = Me.Width - 170
        Dim l As System.Drawing.Point
        l.X = GroupBox2.Width + 15
        l.Y = GroupBox2.Location.Y
        GroupBox1.Location = l
    End Sub

    Private Sub CheckBox1_CheckedChanged(sender As Object, e As EventArgs) Handles CheckBox1.CheckedChanged
        TrackBar3.Enabled = Not TrackBar3.Enabled
        TrackBar4.Enabled = Not TrackBar4.Enabled
        NumericUpDown2.Enabled = Not NumericUpDown2.Enabled
        Label4.Enabled = Not Label4.Enabled
        Label5.Enabled = Not Label5.Enabled
        Label6.Enabled = Not Label6.Enabled
    End Sub
End Class
