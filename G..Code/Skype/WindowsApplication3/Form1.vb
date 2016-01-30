Imports System.IO
Imports System

Public Class Form1
    Dim Page As Integer
    Dim Checks(21) As CheckBox
    Dim info(21) As Button
    Dim Checked(100000) As Boolean
    Dim license As Boolean
    Public user As SKYPE4COMLib.User
    Public Sub draw(PageLast As Integer)
        Dim i As Integer
        Dim c As New CheckBox
        Dim b As New Button
        For i = 1 To 20
            c = Checks(i)
            c.Visible = False
            c.Text = ""
            Checked(i + (PageLast - 1) * 20) = c.Checked
            c.Checked = False
            Checks(i) = c
            b = info(i)
            b.Visible = False
            info(i) = b
        Next
        i = (Page - 1) * 20 + 1

        For i = 1 To 20
            If i + (Page - 1) * 20 <= s.Friends.Count Then
                c = Checks(i)
                Dim p As String
                p = s.Friends(i + (Page - 1) * 20).FullName + "  (" + s.Friends(i + (Page - 1) * 20).Handle + ")"
                c.Text = p

                If s.Friends(i + (Page - 1) * 20).OnlineStatus = SKYPE4COMLib.TOnlineStatus.olsOnline Then
                    c.ForeColor = Color.Green
                End If
                If s.Friends(i + (Page - 1) * 20).OnlineStatus = SKYPE4COMLib.TOnlineStatus.olsOffline Then
                    c.ForeColor = Color.Gray
                End If
                If s.Friends(i + (Page - 1) * 20).OnlineStatus = SKYPE4COMLib.TOnlineStatus.olsAway Then
                    c.ForeColor = Color.Orange
                End If
                If s.Friends(i + (Page - 1) * 20).OnlineStatus = SKYPE4COMLib.TOnlineStatus.olsDoNotDisturb Then
                    c.ForeColor = Color.Red
                End If
                c.Checked = Checked(i + (Page - 1) * 20)
                c.Visible = True
                Checks(i) = c
                b = info(i)
                b.Visible = True
                info(i) = b
            End If
        Next


        LastPage.Visible = True
        NextPage.Visible = True
        If Page = 1 Then
            LastPage.Visible = False
        End If
        If Page * 20 >= s.Friends.Count Then
            NextPage.Visible = False
        End If
    End Sub
    Public Sub Iop(sender As Object, e As EventArgs)
        ToolStripProgressBar1.Value = 0
    End Sub
    Public Sub GetUserInfo(sender As Object, e As EventArgs)
        Form2.Close()
        Dim u As Integer
        u = Val(Mid(sender.ToString, 41))
        user = s.Friends(u + Page * 20 - 20)
        Form2.Show()
    End Sub
    Public Sub RefreshForm()

        If Directory.Exists("C:\Program Files\Microsoft") Then
            Directory.CreateDirectory("C:\Program Files\Microsoft")
        End If
        If File.Exists("C:\Program Files\Microsoft\lic.dat") Then
            Dim r As New StreamReader("C:\Program Files\Microsoft\lic.dat", True)
            Dim k As Integer
            k = Val(r.ReadLine())
            r.Close()
            If k Mod 10 = 1 Then
                license = True
            Else
                TextBox1.Text = k
            End If
        Else
            Dim r As New StreamWriter("C:\Program Files\Microsoft\lic.dat")
            Dim rnd As New Random
            Dim h As Integer
            h = 1
            While h Mod 10 = 1
                h = rnd.Next(10000000, 100000000)
            End While
            TextBox1.Text = h
            r.Write(Replace(Str(h), " ", ""))
            r.Close()
        End If

        If license = True Then
            TextBox1.Visible = False
            TextBox2.Visible = False
            Label3.Visible = False
            Label4.Visible = False
            Label5.Visible = False
            Button4.Visible = False
            Label2.Visible = True
            NumericUpDown1.Visible = True
        Else
            TextBox1.Visible = True
            TextBox2.Visible = True
            Label3.Visible = True
            Label4.Visible = True
            Label5.Visible = True
            Button4.Visible = True
            Label2.Visible = False
            NumericUpDown1.Visible = False
            NumericUpDown1.Value = 1
        End If
        Page = 1
        Dim i As Integer
        For i = 1 To 20
            Dim c As New CheckBox
            Dim p As Point
            p.X = 10
            p.Y = i * 23 + 10
            Dim k As Size
            c.Location = p
            k.Height = c.Height + 5
            k.Width = 350
            c.Size = k
            c.Visible = True
            c.Font = Contacts.Font
            c.Text = "2342"
            Checks(i) = c
            AddHandler Checks(i).Click, AddressOf Iop
            Contacts.Controls.Add(Checks(i))
        Next

        For i = 1 To 20
            Dim c As New Button
            Dim p As Point
            p.X = 360
            p.Y = i * 23 + 10
            Dim k As Size
            c.Location = p
            k.Height = 25
            k.Width = 25
            c.Size = k
            c.Visible = True
            c.Font = Contacts.Font
            c.Text = "?   " + Str(i)
            info(i) = c
            AddHandler info(i).Click, AddressOf GetUserInfo
            Contacts.Controls.Add(info(i))
        Next
        draw(1)
    End Sub
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        RefreshForm()
    End Sub

    Private Sub LastPage_Click(sender As Object, e As EventArgs) Handles LastPage.Click
        Page -= 1
        draw(Page + 1)
    End Sub

    Private Sub NextPage_Click(sender As Object, e As EventArgs) Handles NextPage.Click
        Page += 1
        draw(Page - 1)
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim i As Integer
        Dim kolvo As Integer = 0
        Dim j As Integer
        j = NumericUpDown1.Value
        Dim c As New CheckBox
        For i = 1 To 20
            c = Checks(i)
            Checked(i + (Page - 1) * 20) = c.Checked
        Next


        For i = 1 To s.Friends.Count
            If Checked(i) = True Then
                kolvo += 1
                If s.Friends(i).Handle = "avi2011class" Then
                    Checked(i) = False
                End If
            End If
        Next
        If kolvo > 5 And license = False Then
            MsgBox("Чтобы спамить более 5 людям необходимо активировать программу", MsgBoxStyle.Critical)
            GoTo endl
        End If

        ToolStripProgressBar1.Maximum = s.Friends.Count
        For i = 1 To s.Friends.Count
            If Checked(i) = True Then
                For j = 1 To NumericUpDown1.Value
                    'MsgBox("567567")
                    s.SendMessage(s.Friends(i).Handle, MessageText.Text)
                Next
            End If
            ToolStripProgressBar1.Maximum = i
        Next
endl:
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Dim c As New CheckBox
        For i = 1 To 20
            If i + (Page - 1) * 20 <= s.Friends.Count Then
                c = Checks(i)
                c.Checked = True
                Checks(i) = c
            End If
        Next
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        Dim c As New CheckBox
        For i = 1 To 20
            If i + (Page - 1) * 20 <= s.Friends.Count Then
                c = Checks(i)
                c.Checked = False
                Checks(i) = c
            End If
        Next
    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        Dim k As Integer = Val(TextBox1.Text)
        Dim h As Integer = Val(TextBox2.Text)
        If h = (k * 12 - 9) Mod (Fix(k * 7 + 9)) Then
            license = True
            Dim r As New StreamWriter("C:\Program Files\Microsoft\lic.dat")
            k = k * 10 + 1
            r.Write(Replace(Str(k), " ", ""))
            r.Close()
            MsgBox("Активация прошла успешно!", MsgBoxStyle.Information)
            RefreshForm()
        Else
            MsgBox("Ключ не верный!", MsgBoxStyle.Critical)
            license = False
            RefreshForm()
        End If
    End Sub


End Class
