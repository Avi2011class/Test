Imports System
Imports System.Security
Imports System.Drawing
Imports System.Text
Imports System.IO
Public Class Form1
    Structure Group
        Dim All As GroupBox
        Dim URL As TextBox
        Dim PassURL As TextBox
        Dim Mail As TextBox
        Dim PassMail As TextBox
    End Structure
    Dim Base(10000) As Group
    Dim count As Integer

    Private Sub Form1_FormClosed(sender As Object, e As FormClosedEventArgs) Handles Me.FormClosed
        save()
    End Sub



    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        count = 0
        open()
    End Sub
    Sub vivod()


        Dim pen As Pen
        pen = New Pen(Brushes.Lime)
        pen.Width = 3
        Dim i As Integer

        For i = 1 To count
            Me.Controls.Add(Base(i).All)
            Base(i).All.Controls.Add(Base(i).URL)
            Base(i).All.Controls.Add(Base(i).PassURL)
            Base(i).All.Controls.Add(Base(i).Mail)
            Base(i).All.Controls.Add(Base(i).PassMail)
        Next

    End Sub
    Function code(s As String)
        Return s + Replace(Str(Fix(Rnd() * 5000) + 2000), " ", "")
    End Function
    Sub open()
        Try
            Dim i As Integer
            Dim h As Integer
            Dim r As New StreamReader("Base.xmt")
            Dim s As String = r.ReadLine
            s = Encoding.UTF8.GetString(Convert.FromBase64String(s))
            h = Val(s)
            For i = 1 To h
                s = r.ReadLine()
                s = Encoding.UTF8.GetString((Convert.FromBase64String(s)))
                add()
                Base(count).URL.Text = Mid(s, 1, InStr(s, "↓") - 5)
                s = Mid(s, InStr(s, "↓") + 1)

                Base(count).PassURL.Text = Mid(s, 1, InStr(s, "↓") - 5)
                s = Mid(s, InStr(s, "↓") + 1)

                Base(count).Mail.Text = Mid(s, 1, InStr(s, "↓") - 5)
                s = Mid(s, InStr(s, "↓") + 1)

                Base(count).PassMail.Text = Mid(s, 1, InStr(s, "↓") - 5)
                s = Mid(s, InStr(s, "↓") + 1)
            Next
            r.Close()
            r.Dispose()
        Catch e As Exception
            MsgBox(e.ToString)
        End Try
    End Sub

    Sub save()
        Try
            Dim i As Integer
            Dim wr As New StreamWriter("Base.xmt")
            wr.WriteLine(Convert.ToBase64String(Encoding.UTF8.GetBytes(Str(count))))
            For i = 1 To count
                Dim s As String
                s = code(Base(i).URL.Text) + "↓" + code(Base(i).PassURL.Text) + "↓" + code(Base(i).Mail.Text) + "↓" + code(Base(i).PassMail.Text) + "↓" + "end"
                wr.WriteLine(Convert.ToBase64String(Encoding.UTF8.GetBytes(s)))
            Next
            For i = 1 To 1000 - count

                Dim s As String
                s = Str(Rnd() * 234423423) + Str(Rnd) + Str(23432423423)
                wr.WriteLine(Convert.ToBase64String(Encoding.UTF8.GetBytes(s)))
            Next

            wr.Close()
        Catch e As Exception
            MsgBox(e.ToString)
        End Try
    End Sub
    Sub add()
        Dim g As Group
        Dim text1 As New TextBox
        Dim text2 As New TextBox
        Dim text3 As New TextBox
        Dim text4 As New TextBox
        text1.Font = TB.Font
        text2.Font = TB.Font
        text3.Font = TB.Font
        text4.Font = TB.Font
        text1.Visible = True
        text2.Visible = True
        text3.Visible = True
        text4.Visible = True

        text1.ForeColor = TB.ForeColor
        text2.ForeColor = TB.ForeColor
        text3.ForeColor = TB.ForeColor
        text4.ForeColor = TB.ForeColor

        text1.BackColor = TB.BackColor
        text2.BackColor = TB.BackColor
        text3.BackColor = TB.BackColor
        text4.BackColor = TB.BackColor


        text1.Location = New Point(9, 10)
        text1.Size = New Size(145, 20)
        text1.Visible = True
        g.URL = text1


        text2.Location = New Point(160, 10)
        text2.Size = New Size(145, 20)
        text2.Visible = True
        g.PassURL = text2


        text3.Location = New Point(311, 10)
        text3.Size = New Size(145, 20)
        text3.Visible = True
        g.Mail = text3

        text4.Location = New Point(462, 10)
        text4.Size = New Size(145, 20)
        text4.Visible = True
        g.PassMail = text4


        g.URL.BorderStyle = BorderStyle.FixedSingle
        g.PassURL.BorderStyle = BorderStyle.FixedSingle
        g.Mail.BorderStyle = BorderStyle.FixedSingle
        g.PassMail.BorderStyle = BorderStyle.FixedSingle
        Dim group As New GroupBox
        group.Size = New Size(622, text1.Size.Height + text1.Location.Y + 5)
        group.Location = New Point(50, count * (group.Size.Height) + 50)
        group.Visible = True
        g.All = group
        count = count + 1
        Base(count) = g
        vivod()
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        add()
    End Sub




    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        count = count - 1
        If count >= 0 Then
            Me.Controls.Remove(Base(count + 1).All)
        End If
        vivod()
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs)
        save()
    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs)
        open()
    End Sub

End Class


