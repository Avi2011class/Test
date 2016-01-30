Public Class Form1
    Public WithEvents s As SKYPE4COMLib.Skype = New SKYPE4COMLib.Skype
    Structure pupil
        Dim Name As String
        Dim Addres As String
        Dim NowQuestion As Integer
        Dim Result As Integer
        Dim Good() As Boolean
        Dim iseng As Boolean
    End Structure
    Structure problem
        Dim Name As String
        Dim Body As String
        Dim Answer As String
    End Structure
    Dim U(10000) As pupil
    Dim Problems(1000) As problem
    Dim CountU As Integer = 0
    Dim CountP As Integer = 0
    Dim MaxAttempt As Integer = 1
    Dim started As Boolean = False

    Sub OutU()
        ListBox1.Items.Clear()
        For i = 0 To CountU - 1
            ListBox1.Items.Add(U(i).Result.ToString + "  " + U(i).Name + " Задача №" + U(i).NowQuestion.ToString)
        Next

    End Sub
    Sub OutP()
        ListBox2.Items.Clear()
        For i = 0 To CountP - 1
            ListBox2.Items.Add(i.ToString + ". " + Problems(i).Name)
        Next
    End Sub
    Sub send(user As Integer, number As Integer)
        s.SendMessage(U(user).Addres, number.ToString + " " + Problems(number).Name + vbCrLf + "---------------" + vbCrLf + Problems(number).Body)
        's.SendMessage(U(user).Addres, "!say " + Problems(number).Answer)
    End Sub
    Private Sub s_MessageStatus(pMessage As SKYPE4COMLib.ChatMessage, Status As SKYPE4COMLib.TChatMessageStatus) Handles s.MessageStatus
        If started = False Then
            If Status = SKYPE4COMLib.TChatMessageStatus.cmsReceived And InStr(pMessage.Body, "//reg") <> 0 And pMessage.Sender.Handle <> s.User.Handle Then
                Dim P As pupil = New pupil
                P.Name = Mid(pMessage.Body, InStr(pMessage.Body, "//reg") + 6)
                s.SendMessage(pMessage.Sender.Handle, "Вы зарегистрированы!")
                P.Addres = pMessage.Sender.Handle
                U(CountU) = P
                CountU += 1
                OutU()
            End If
        Else
            If Status = SKYPE4COMLib.TChatMessageStatus.cmsReceived And pMessage.Sender.Handle <> s.User.Handle Then
                Dim user As Integer = 0
                While U(user).Addres <> pMessage.Sender.Handle And user < 2000
                    user += 1
                End While
                If user <> 2000 Then

                    If Problems(U(user).NowQuestion).Answer = pMessage.Body Then
                        Dim us As pupil = U(user)
                        us.Result += 1
                        us.Good(us.NowQuestion) = True

                        U(user) = us

                        OutU()
                        Logs.Text += "Пользователь <" + U(user).Name + "> дал правильный ответ<" + pMessage.Body + "> на задачу <" + U(user).NowQuestion.ToString + ">" + vbCrLf
                    Else
                        Logs.Text += "Пользователь <" + U(user).Name + "> дал неправильный ответ<" + pMessage.Body + "> на задачу <" + U(user).NowQuestion.ToString + ">" + vbCrLf
                    End If

                    If U(user).NowQuestion = CountP - 1 Then
                        s.SendMessage(U(user).Addres, "Завершено! " + vbCrLf)
                        s.SendMessage(U(user).Addres, "Ваш результат: ")
                        Dim str As String = ""
                        For i = 1 To CountP
                            str += i.ToString + ". "
                            If U(user).Good(i - 1) Then
                                str = str + "+"
                            Else
                                str = str + "-"
                            End If
                            str += vbCrLf
                        Next
                        str += "Всего " + U(user).Result.ToString + " задач"
                        s.SendMessage(U(user).Addres, str)
                        OutU()
                    Else
                        Dim us1 As pupil = U(user)
                        us1.NowQuestion += 1
                        U(user) = us1
                        send(user, us1.NowQuestion)
                        OutU()
                    End If
                End If
            End If
        End If
    End Sub
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        s.Attach()
        ' Dim us1 As pupil = New pupil
        ' us1.Addres = "zmei1997"
        ' us1.Name = "Sasha"
        '  U(0) = us1
        '  CountU += 1
        OutU()
    End Sub

    Private Sub Add_Click(sender As Object, e As EventArgs) Handles Add.Click
        Dim p As problem = New problem
        Problems(CountP) = p
        CountP += 1
        OutP()
    End Sub

    Private Sub ListBox2_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ListBox2.SelectedIndexChanged
        If ListBox2.SelectedIndex <> -1 Then
            TextBox1.Text = Problems(ListBox2.SelectedIndex).Name
            TextBox2.Text = Problems(ListBox2.SelectedIndex).Body
            TextBox3.Text = Problems(ListBox2.SelectedIndex).Answer
        End If
        
    End Sub

    Private Sub Delete_Click(sender As Object, e As EventArgs) Handles Delete.Click
        For i = ListBox2.SelectedIndex To CountP - 1
            Problems(i) = Problems(i + 1)
        Next
        CountP -= 1
        OutP()
    End Sub

    Private Sub Save_Click(sender As Object, e As EventArgs) Handles Save.Click
        If ListBox2.SelectedIndex <> -1 Then
            Dim p As problem
            p.Name = TextBox1.Text
            p.Body = TextBox2.Text
            p.Answer = TextBox3.Text
            TextBox1.Text = ""
            TextBox2.Text = ""
            TextBox3.Text = ""
            Problems(ListBox2.SelectedIndex) = p
            OutP()
        End If
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        started = True
        For i = 0 To CountU - 1
            s.SendMessage(U(i).Addres, "Олимпиада началась!" + vbCrLf)
        Next
        For i = 0 To CountU - 1
            send(i, 0)
        Next
        Dim b(1000) As Boolean
        For i = 0 To 1000
            b(i) = False
        Next
        For i = 0 To CountU - 1
            U(i).iseng = False
            U(i).Good = b
        Next
    End Sub
End Class