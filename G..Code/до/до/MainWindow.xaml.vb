Imports System
Imports System.Net
Imports System.Text
Imports System.Text.RegularExpressions
Imports System.IO
Imports System.Web
Class MainWindow
    Structure people
        Dim LastLogin As String
        Dim Logins As String
        Dim Profile As String
        Dim About As String
        Dim Info As String
        Dim id As String
        Dim LastRefresh As String
    End Structure
    Dim base(100000) As people
    Dim count As Integer
    Dim BaseName As String
    Dim Potoks As Integer = 10
    Dim ProxyList(100000) As WebProxy
    Dim ProxyCount As Integer


    Sub vivod()
        ListOfUsers.Items.Clear()
        Dim i As Integer
        For i = 1 To count
            ListOfUsers.Items.Add(base(i).LastLogin + "  " + base(i).Profile)
        Next
    End Sub
    Function parse(s As String, starts As String, stops As String) As String
        Try
            Dim l As String
            l = s
            If InStr(l, starts) > 0 Then
                l = Mid(l, InStr(l, starts) + Len(starts))
                l = Mid(l, 1, InStr(l, stops) - 1)
                parse = l
            Else
                parse = ""
            End If
        Catch
            parse = ""
        End Try
    End Function
    Sub sort()
        'Dim u As people
        ' For i = 1 To count - 1 ' Где конечное число цикла равно количеству чисел в массиве
        'For j = i To count 'Тут конечное число цикла равно количеству чисел в массиве минус один 
        'If AsciiEncode(Mid(base(j).LastLogin, 1, 1)) > AsciiEncode(Mid(base(i).LastLogin, 1, 1)) Then ' Если предыдущие число больше следущего, то
        'u = base(i) ' Запоминаем предыдущие число в переменную u
        'base(i) = base(j) ' Предыдущие число приравниваем следующему
        'base(j) = u ' А следующие число заменяем числом u
        ' End If
        ' Next
        ' Next
    End Sub
    Sub add(user As people)
        Try
            count = count + 1
            base(count) = user
            sort()
        Catch
        End Try
    End Sub
    Sub Refresh(j As Integer)
        Try
            Dim tmp As people = base(j)

            Dim r As HttpWebRequest = HttpWebRequest.Create(tmp.Profile)
            '  Dim r As Random
            r.Proxy = New WebProxy("127.0.0.1", 8888)
            Dim resp As HttpWebResponse = r.GetResponse()
            Dim reader As StreamReader = New StreamReader(resp.GetResponseStream, Encoding.UTF8)
            Dim s As String = reader.ReadToEnd
            Dim Tmplastlogin As String = parse(s, "<img src=""/do_img/global/text.esg?l=ru&s=13&t=", "&f=ship_name")

            If Tmplastlogin <> tmp.LastLogin Then
                tmp.Logins = tmp.LastLogin + "; " + tmp.Logins
                tmp.LastLogin = Tmplastlogin
            End If
            Dim id As String
            id = parse(s, "userKeyId     :", ",")
            tmp.id = Val(id)
            s = parse(s, "<div class=""personalInfoInfo"">", "<div id=""videoPlayer""></div>")
            s = Regex.Replace(s, "(<[^>]*>)+", "", RegexOptions.IgnoreCase)
            While InStr(s, "  ") > 0
                s = Replace(s, "  ", " ")
                s = Replace(s, vbLf + " ", vbLf)
            End While
            s = Replace(s, ":" + vbLf, ": ")
            While InStr(s, vbLf + vbLf) > 0
                s = Replace(s, vbLf + vbLf, vbLf)
            End While
            tmp.Info = s
            tmp.LastRefresh = Now.ToString
            base(j) = tmp
        Catch

        End Try
    End Sub
    Function AsciiEncode(ByVal value As String) As Integer
        Try
            Dim encValue As New System.Text.StringBuilder(value.Length * 6)
            Dim c As Char
            ' encode each char to its ASCII representation
            For Each c In value
                'encValue.Append("&#")
                encValue.Append(Convert.ToInt32(c))
                'encValue.Append(";")
            Next
            Return Val(encValue.ToString())
        Catch
            Return 0
        End Try
    End Function
    Private Sub MainWindow_Closed(sender As Object, e As EventArgs) Handles Me.Closed
        savebase()
    End Sub
    Private Sub MainWindow_Loaded(sender As Object, e As RoutedEventArgs) Handles Me.Loaded
        'Dim u As people = New people
        ' u.Profile = "http://ru2.darkorbit.bigpoint.com/index.es?profile=4X3sH&profileCheck=A885F&lang=ru"
        'add(u)
        'u = New people
        'u.Profile = "http://ru2.darkorbit.bigpoint.com/index.es?profile=2uIZn&profileCheck=5Feif&lang=ru"
        ' add(u)
        'u = New people
        'u.Profile = "http://ru2.darkorbit.bigpoint.com/index.es?profile=1yokT&profileCheck=37Vcn&lang=ru"
        ' add(u)


        openbase()
        vivod()
       
    End Sub
    Private Sub ListOfUsers_SelectionChanged(sender As Object, e As SelectionChangedEventArgs) Handles ListOfUsers.SelectionChanged
        Try
            Dim tmp As people = base(ListOfUsers.SelectedIndex + 1)
            Dim info As String
            info = "Последняя проверка: " + tmp.LastRefresh + vbCrLf
            info = info + "Логин: " + tmp.LastLogin + "   ID: " + tmp.id + vbCrLf
            info = info + "Последние логины: " + vbCrLf + tmp.Logins + vbCrLf
            info = info + "Об аккаунте: " + tmp.Info + vbCrLf
            info = info + "Примечания: " + vbCrLf + tmp.About + vbCrLf
            info = info + "Профиль: " + tmp.Profile + vbCrLf
            UserInfo.Text = info
            Up.Visibility = Windows.Visibility.Visible
            Down.Visibility = Windows.Visibility.Visible

            If ListOfUsers.SelectedIndex = 0 Then Up.Visibility = Windows.Visibility.Hidden
            If ListOfUsers.SelectedIndex = count - 1 Then Down.Visibility = Windows.Visibility.Hidden
        Catch
        End Try
    End Sub
    Private Sub Save_Click(sender As Object, e As RoutedEventArgs) Handles Save.Click
        Dim tmp As people = base(ListOfUsers.SelectedIndex + 1)
        tmp.About = Edit_Account.Text
        base(ListOfUsers.SelectedIndex + 1) = tmp
        ln456.Visibility = Windows.Visibility.Hidden
        Edit_Account.Visibility = Windows.Visibility.Hidden
        Save.Visibility = Windows.Visibility.Hidden
    End Sub
    Private Sub Button_Click_1(sender As Object, e As RoutedEventArgs)
        ln456.Visibility = Windows.Visibility.Visible
        Edit_Account.Visibility = Windows.Visibility.Visible
        Save.Visibility = Windows.Visibility.Visible
        Edit_Account.Text = base(ListOfUsers.SelectedIndex + 1).About
    End Sub
    Private Sub Delete_Click(sender As Object, e As RoutedEventArgs) Handles Delete.Click
        For i = ListOfUsers.SelectedIndex + 1 To count
            base(i) = base(i + 1)
        Next
        count -= 1
        vivod()
    End Sub
    Private Sub Delete_Copy_Click(sender As Object, e As RoutedEventArgs) Handles Delete_Copy.Click
        Refresh(ListOfUsers.SelectedIndex + 1)
        vivod()
    End Sub


    Private Sub Delete_Copy2_Click(sender As Object, e As RoutedEventArgs) Handles Delete_Copy2.Click

        For i = 1 To potoks
            Dim p1 As New System.Threading.Thread(AddressOf RefreshAcync)
            p1.Start(i)
        Next
        '  For i = 1 To count
        'Refresh(i)
        '  System.Threading.Thread.Sleep(4)
        '  Next
        vivod()
    End Sub
    Sub savebase()
        Dim msg As MsgBoxResult = MsgBox("Сохранить изменения?", MsgBoxStyle.YesNo, "Сохрание при выходе")
        If msg = MsgBoxResult.Yes Then

            Dim s As String
            s = Str(count) + "♫↨"
            For i = 1 To count
                s = s + base(i).LastLogin + "♫↨" + base(i).id + "♫↨" + base(i).Logins + "♫↨" + base(i).Profile + "♫↨" + base(i).Info + "♫↨" + base(i).About + "♫↨" + base(i).LastRefresh + "♫↨"
            Next
            Dim writer As New StreamWriter(BaseName, False, System.Text.Encoding.Unicode)
            writer.Write(s)
            writer.Close()
        End If

    End Sub
    Sub openbase()
        Try
            Dim dialog As Microsoft.Win32.OpenFileDialog = New Microsoft.Win32.OpenFileDialog
            dialog.Filter = "Файлы базы данных|*.atl"
            dialog.ShowDialog()
            'If IO.File.Exists("Base.atl") Then
            BaseName = dialog.FileName
            Dim reader As New StreamReader(BaseName, System.Text.Encoding.Unicode)
            Dim s As String = reader.ReadToEnd
            Dim tmp As String
            tmp = Mid(s, 1, InStr(s, "♫↨") - 1)
            s = Mid(s, InStr(s, "♫↨") + 2)
            count = Val(tmp)
            For i = 1 To count
                Dim p As people = New people()
                p.LastLogin = Mid(s, 1, InStr(s, "♫↨") - 1)
                s = Mid(s, InStr(s, "♫↨") + 2)
                p.id = Mid(s, 1, InStr(s, "♫↨") - 1)
                s = Mid(s, InStr(s, "♫↨") + 2)
                p.Logins = Mid(s, 1, InStr(s, "♫↨") - 1)
                s = Mid(s, InStr(s, "♫↨") + 2)
                p.Profile = Mid(s, 1, InStr(s, "♫↨") - 1)
                s = Mid(s, InStr(s, "♫↨") + 2)
                p.Info = Mid(s, 1, InStr(s, "♫↨") - 1)
                s = Mid(s, InStr(s, "♫↨") + 2)
                p.About = Mid(s, 1, InStr(s, "♫↨") - 1)
                s = Mid(s, InStr(s, "♫↨") + 2)
                p.LastRefresh = Mid(s, 1, InStr(s, "♫↨") - 1)
                s = Mid(s, InStr(s, "♫↨") + 2)
                base(i) = p
            Next
            vivod()
            'End If
        Catch
        End Try
    End Sub

    Private Sub adduser_Click(sender As Object, e As RoutedEventArgs) Handles adduser.Click
        ln23.Visibility = Windows.Visibility.Visible
        NewUserProfile.Visibility = Windows.Visibility.Visible
        NewUserProfile.Text = ""
        OK.Visibility = Windows.Visibility.Visible
    End Sub
    Private Sub OK_Click(sender As Object, e As RoutedEventArgs) Handles OK.Click
        ln23.Visibility = Windows.Visibility.Hidden
        NewUserProfile.Visibility = Windows.Visibility.Hidden
        OK.Visibility = Windows.Visibility.Hidden
        Dim u As people = New people
        u.Profile = NewUserProfile.Text
        add(u)
        sort()
        vivod()
    End Sub

    Private Sub Up_Click(sender As Object, e As RoutedEventArgs) Handles Up.Click
        Dim _Last As Integer = ListOfUsers.SelectedIndex + 1
        Dim _New As Integer = ListOfUsers.SelectedIndex
        Dim _tmp As people = base(_New)
        base(_New) = base(_Last)
        base(_Last) = _tmp
        vivod()
        ListOfUsers.SelectedIndex = _New - 1
    End Sub
    Private Sub Down_Click(sender As Object, e As RoutedEventArgs) Handles Down.Click
        Dim _Last As Integer = ListOfUsers.SelectedIndex + 1
        Dim _New As Integer = ListOfUsers.SelectedIndex + 2
        Dim _tmp As people = base(_New)
        base(_New) = base(_Last)
        base(_Last) = _tmp
        vivod()
        ListOfUsers.SelectedIndex = _New - 1
    End Sub
    Sub RefreshAcync(j As Integer)
        For i = j To count Step potoks
            Refresh(i)
        Next
    End Sub

End Class
