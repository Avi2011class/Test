Imports System
Imports System.IO
Imports System.Net
Imports System.Text
Class MainWindow
    Dim cookies As String
    Dim t As String
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
    Private Sub MainWindow_Loaded(sender As Object, e As RoutedEventArgs) Handles Me.Loaded
        Dim r As HttpWebRequest = HttpWebRequest.Create("http://goldpride.ru/")
        Dim resp As HttpWebResponse = r.GetResponse()
        cookies = String.Format("bblastvisit={0}; bblastactivity={1}", parse(resp.GetResponseHeader("Set-Cookie"), "bblastvisit=", ";"), parse(resp.GetResponseHeader("Set-Cookie"), "bblastactivity=", ";"))
        my.Text = cookies
    End Sub

    Private Sub Next1_Click(sender As Object, e As RoutedEventArgs) Handles Next1.Click
        Dim r As HttpWebRequest = HttpWebRequest.Create("http://goldpride.ru/login.php?do=login")
        r.Method = "POST"
        r.ContentType = "application/x-www-form-urlencoded"
        r.Headers.Add("Cookie", cookies)
        Dim s As String = "vb_login_username=" + UserLogin.Text + "&cookieuser=1&vb_login_password=" + UserPassword.Text + "&s=&securitytoken=guest&do=login&vb_login_md5password=&vb_login_md5password_utf="
        Dim bytearr() As Byte = System.Text.Encoding.UTF8.GetBytes(s)
        r.ContentLength = bytearr.Length()
        r.GetRequestStream().Write(bytearr, 0, bytearr.Length)
        Dim resp As HttpWebResponse = r.GetResponse()
        Dim reader As StreamReader = New StreamReader(resp.GetResponseStream())
        Dim tmp As String = reader.ReadToEnd()
        t = tmp
        r = HttpWebRequest.Create("http://www.google.com/recaptcha/api/challenge?k=6LdcI-ISAAAAACwefcixTSsvDl8tK77VN6BqmAeC")
        r.Referer = "http://goldpride.ru/login.php?do=login"
        r.KeepAlive = True
        resp = r.GetResponse()
        reader = New StreamReader(resp.GetResponseStream(), Encoding.UTF8)
        tmp = reader.ReadToEnd
        Dim picture As String = "http://www.google.com/recaptcha/api/image?c=" + parse(tmp, " challenge : '", "'")
        Captcha.Navigate(picture)
        Captcha.Opacity = 1
    End Sub

    Private Sub Refresh_Click(sender As Object, e As RoutedEventArgs) Handles Refresh.Click
        Dim r As HttpWebRequest
        Dim resp As HttpWebResponse
        Dim reader As StreamReader
        r = HttpWebRequest.Create("http://www.google.com/recaptcha/api/challenge?k=6LdcI-ISAAAAACwefcixTSsvDl8tK77VN6BqmAeC")
        r.ServicePoint.Expect100Continue = False
        r.Referer = "http://goldpride.ru/login.php?do=login"
        r.KeepAlive = True
        resp = r.GetResponse()
        reader = New StreamReader(resp.GetResponseStream(), Encoding.UTF8)
        Dim picture As String = "http://www.google.com/recaptcha/api/image?c=" + parse(reader.ReadToEnd, " challenge : '", "'")
        Captcha.Navigate(picture)
        Captcha.Opacity = 1
    End Sub

    Private Sub Next2_Click(sender As Object, e As RoutedEventArgs) Handles Next2.Click
        Dim req As HttpWebRequest

        req = HttpWebRequest.Create("http://goldpride.ru/login.php?do=dologin")
        req.ServicePoint.Expect100Continue = False
        req.Method = "POST"
        req.UserAgent = "Opera/9.80 (Windows NT 6.1) Presto/2.12.388 Version/12.15"
        req.Accept = "text/html, application/xml;q=0.9, application/xhtml+xml, image/png, image/webp, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1"
        req.Headers.Add("Accept-Language", "ru-RU,ru;q=0.9,en;q=0.8")
        req.Headers.Add("Cookie", cookies)
        req.Headers.Add("Accept-Encoding", "utf-8")
        req.Referer = "http://goldpride.ru/login.php?do=login"
        req.KeepAlive = True
        req.ContentType = "application/x-www-form-urlencoded"
        Dim sQueryString As String = "humanverify%5Bhash%5D=" + parse(t, "<input id=""hash"" type=""hidden"" name=""humanverify[hash]"" value=""", """") + "&recaptcha_challenge_field=" + parse(t, " challenge : '", "'")
        sQueryString = sQueryString + "&recaptcha_response_field=" + Replace(CaptchaResult.Text, " ", "+") + "&s=&securitytoken=guest&do=dologin&"
        sQueryString = sQueryString + "vb_login_password=" + parse(t, "<input type=""hidden"" name=""vb_login_password"" value=""", """") + "&vb_login_username=" + parse(t, "<input type=""hidden"" name=""vb_login_username"" value=""", """")
        sQueryString = sQueryString + "&url=http%3A%2F%2Fgoldpride.ru%2Flogin.php%3Fdo%3Dlogin&cookieuser=1&postvars=&logintype=&cssprefs="
        Dim ByteArr As Byte() = Encoding.UTF8.GetBytes(sQueryString)
        req.ContentLength = ByteArr.Length()
        req.GetRequestStream().Write(ByteArr, 0, ByteArr.Length)
        Dim resp As HttpWebResponse = req.GetResponse()

        Dim reader As StreamReader = New StreamReader(resp.GetResponseStream(), Encoding.UTF8)
        Dim tmp As String = reader.ReadToEnd()
        If InStr(tmp, "Введённая вами строка не совпадает с той, которая была указана на проверочном изображении.") Then
            Label32.Content = "Введённая вами строка не совпадает с той, которая была указана на проверочном изображении."
        Else
            If InStr(tmp, "Вы ввели неправильное имя или пароль.") Then
                Label32.Content = "Вы ввели неправильное имя или пароль!"
            Else
                t = resp.GetResponseHeader("Set-Cookie")
                cookies = cookies + "; " + String.Format("bbuserid={0}; bbpassword={1}; bbsessionhash={2}", parse(t, "bbuserid=", ";"), parse(t, "bbpassword=", ";"), parse(t, "bbsessionhash=", ";"))
                Label32.Content = "Успешно!"
                my.Text = cookies
            End If
        End If
    End Sub
End Class

