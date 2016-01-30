Imports System.Drawing
Public Class Form1
    Dim GF As Graphics
    Dim pole(100, 100) As Integer
    Dim user As Integer
    Dim gameover As Boolean
    Dim memory(20) As Boolean


    Sub vivod()
        If gameover = True Then
            PictureBox1.Visible = False
        Else
            PictureBox1.Visible = True
        End If

        GF = Me.CreateGraphics
        Dim point As System.Drawing.Point
        setka()
        For i = 1 To 9
            For j = 1 To 9
                point.X = i * 70
                point.Y = j * 70
                If pole(i, j) = 1 Then
                    GF.DrawImage(RED.Image, point)
                End If
                If pole(i, j) = 2 Then
                    GF.DrawImage(BLUE.Image, point)
                End If
            Next
        Next
        If user = 1 Then
            BLUEUSER.Visible = False
            REDUSER.Visible = True
        End If
        If user = 2 Then
            BLUEUSER.Visible = True
            REDUSER.Visible = False
        End If
    End Sub
    Sub win(x1 As Integer, y1 As Integer, x2 As Integer, y2 As Integer, winner As Integer)
        GF = Me.CreateGraphics
        Dim Pen As New Pen(Color.Yellow, 10)
        vivod()
        GF.DrawLine(Pen, x1 * 70 + 35, y1 * 70 + 35, x2 * 70 + 35, y2 * 70 + 35)
        MsgBox("Поздравляем игрока " + Str(winner) + " с победой!", MsgBoxStyle.Information)
        gameover = True
        PictureBox1.Visible = False
    End Sub
    Sub proverca()
        Dim i As Integer
        Dim j As Integer

        Dim t As Boolean
        t = False
        For i = 1 To 9
            For j = 1 To 8
                If pole(i, j) = 0 Then
                    t = True
                End If
            Next
        Next

        If t = False Then
            vivod()
            MsgBox("Ничья!")
            gameover = True
        End If

        If gameover = False Then


            For i = 1 To 6
                For j = 1 To 8
                    If pole(i, j) = pole(i + 1, j) And pole(i, j) = pole(i + 2, j) And pole(i, j) = pole(i + 3, j) And pole(i, j) > 0 Then
                        win(i, j, i + 3, j, pole(i, j))
                    End If
                Next
            Next
        End If

        If gameover = False Then
            For i = 1 To 9
                For j = 1 To 5
                    If pole(i, j) = pole(i + 1, j + 1) And pole(i, j) = pole(i + 2, j + 2) And pole(i, j) = pole(i + 3, j + 3) And pole(i, j) > 0 Then
                        win(i, j, i + 3, j + 3, pole(i, j))
                    End If
                Next
            Next
        End If

        If gameover = False Then
            For i = 1 To 6
                For j = 1 To 5
                    If pole(i, j) = pole(i, j + 1) And pole(i, j) = pole(i, j + 2) And pole(i, j) = pole(i, j + 3) And pole(i, j) > 0 Then
                        win(i, j, i, j + 3, pole(i, j))
                    End If
                Next
            Next
        End If

        If gameover = False Then
            For i = 4 To 9
                For j = 1 To 5
                    If pole(i, j) = pole(i - 1, j + 1) And pole(i, j) = pole(i - 2, j + 2) And pole(i, j) = pole(i - 3, j + 3) And pole(i, j) > 0 Then
                        win(i, j, i - 3, j + 3, pole(i, j))
                    End If
                Next
            Next
        End If

    End Sub

    Sub setka()

        GF = Me.CreateGraphics
        GF.Clear(Color.White)
        Dim Pen As New Pen(Color.Black, 4)
        For i = 70 To 700 Step 70
            GF.DrawLine(Pen, i, 70, i, 630)
        Next
        For i = 70 To 630 Step 70
            GF.DrawLine(Pen, 70, i, 700, i)
            Dim point As PointF
            Dim Font As New Font("Cambria", 30, FontStyle.Bold)
            point.X = i + 3
            point.Y = 25
            GF.DrawString(Str(i / 70), Font, New SolidBrush(Color.Blue), point)
        Next
    End Sub
    Sub down(g As Integer)
        If gameover = False Then
            Dim i As Integer
            i = 0
            While pole(g, i + 1) = 0 And (i < 8)
                i = i + 1
            End While
            If i <> 0 Then
                pole(g, i) = user
            End If

            proverca()
            If gameover = False Then
                If i > 0 Then
                    user = 3 - user
                End If
                vivod()
            End If
        End If
    End Sub



    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click

        For i = 1 To 9
            For j = 1 To 8
                pole(i, j) = 0
            Next
        Next
        gameover = False
        user = 1
        PictureBox1.Visible = True
        vivod()

        Dim GF As System.Drawing.Graphics
        Dim PenColor As New System.Drawing.Pen(System.Drawing.Color.Red, 20)
        GF = Me.CreateGraphics
        setka()
    End Sub


    Private Sub Button1_KeyDown(sender As Object, e As KeyEventArgs) Handles Button1.KeyDown
        Dim point As System.Drawing.Point
        point = PictureBox1.Location
        'MsgBox(e.KeyValue)

            If (e.KeyValue = 65) And (PictureBox1.Location.X >= 140) Then
                point.X = PictureBox1.Location.X - 70
            Else
                If (e.KeyValue = 68) And (PictureBox1.Location.X <= 560) Then
                    point.X = PictureBox1.Location.X + 70
                Else
                    If (e.KeyValue = 83) Then
                        down((point.X - (point.X Mod 70)) / 70)
                    End If
                End If
        End If
        If e.KeyValue = 82 Then
            Dim r As New Random
            down(r.Next(1, 9))
        End If
     


        PictureBox1.Location = point
    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles Me.Load
        PictureBox1.BackColor = Color.Transparent
        user = 1

    End Sub


    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        MsgBox(" По очереди бросая шашки в столбцы необходимо добиться того, чтобы по горизонтали," + vbCrLf + "вертикали или диагонали оказались 4 ваших шашки подряд. Чтобы перемещать указатель влево" + vbCrLf + "и вправо нажимайте ""A"" и ""D"", чтобы бросить шашку в выбранный столбец, нажмите ""S""." + vbCrLf + vbCrLf + "В верхнем правом углу находится указатель, указавыющий на то, какой игрок сейчас ходит.", MsgBoxStyle.Information, "Краткая информация о игре")
    End Sub

    Private Sub GroupBox1_Enter(sender As Object, e As EventArgs)

    End Sub

    Private Sub Button2_KeyDown(sender As Object, e As KeyEventArgs) Handles Button2.KeyDown
        Dim point As System.Drawing.Point
        point = PictureBox1.Location
        'MsgBox(e.KeyValue)

            If (e.KeyValue = 65) And (PictureBox1.Location.X >= 140) Then
                point.X = PictureBox1.Location.X - 70
            Else
                If (e.KeyValue = 68) And (PictureBox1.Location.X <= 560) Then
                    point.X = PictureBox1.Location.X + 70
                Else
                    If (e.KeyValue = 83) Then
                        down((point.X - (point.X Mod 70)) / 70)
                    End If
                End If
            End If
        If e.KeyValue = 82 Then
            Dim r As New Random
            down(r.Next(1, 9))
        End If


        PictureBox1.Location = point
    End Sub
End Class
