Public Class Form2

    Private Sub Form2_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Dim user As SKYPE4COMLib.User = Form1.user
        TextBox1.Text = user.MoodText
        Dim s As String
        s = ""
        s = "<html>"
        s = s + "<head></head>"
        s = s + "<body bgcolor=""#000000"">"
        s = s + "<img src=""http://api.skype.com/users/" + user.Handle + "/profile/avatar"" " + "alt=""Аватар пользователя"" width=""100%"" height=""100%"" ></img>"
        s = s + " </body>"
        s = s + " </html>"
        WebBrowser1.DocumentText = s
        Label1.Text = user.FullName
        If user.OnlineStatus = SKYPE4COMLib.TOnlineStatus.olsOnline Then
            Label1.ForeColor = Color.Green
        End If
        If user.OnlineStatus = SKYPE4COMLib.TOnlineStatus.olsOffline Then
            Label1.ForeColor = Color.Gray
        End If
        If user.OnlineStatus = SKYPE4COMLib.TOnlineStatus.olsAway Then
            Label1.ForeColor = Color.Orange
        End If
        If user.OnlineStatus = SKYPE4COMLib.TOnlineStatus.olsDoNotDisturb Then
            Label1.ForeColor = Color.Red
        End If
        Label2.Text = "Логин Skype:" + vbCrLf + "Дата рождения:" + vbCrLf + "Возраст:" + vbCrLf + "Пол:" + vbCrLf + "" + vbCrLf + "" + vbCrLf + "" + vbCrLf + ""
    End Sub

   


    Private Sub TextBox1_GotFocus(sender As Object, e As EventArgs) Handles TextBox1.GotFocus
        WebBrowser1.Focus()
    End Sub

    Private Sub Form2_Paint(sender As Object, e As PaintEventArgs) Handles Me.Paint
        MsgBox("11")
    End Sub
End Class