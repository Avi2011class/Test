﻿#ExternalChecksum("..\..\MainWindow.xaml","{406ea660-64cf-4c82-b6f0-42d48172a799}","30580A3CFDFCE0B0ADDDB490B5498A2D")
'------------------------------------------------------------------------------
' <auto-generated>
'     This code was generated by a tool.
'     Runtime Version:4.0.30319.34014
'
'     Changes to this file may cause incorrect behavior and will be lost if
'     the code is regenerated.
' </auto-generated>
'------------------------------------------------------------------------------

Option Strict Off
Option Explicit On

Imports System
Imports System.Diagnostics
Imports System.Windows
Imports System.Windows.Automation
Imports System.Windows.Controls
Imports System.Windows.Controls.Primitives
Imports System.Windows.Data
Imports System.Windows.Documents
Imports System.Windows.Ink
Imports System.Windows.Input
Imports System.Windows.Markup
Imports System.Windows.Media
Imports System.Windows.Media.Animation
Imports System.Windows.Media.Effects
Imports System.Windows.Media.Imaging
Imports System.Windows.Media.Media3D
Imports System.Windows.Media.TextFormatting
Imports System.Windows.Navigation
Imports System.Windows.Shapes
Imports System.Windows.Shell


'''<summary>
'''MainWindow
'''</summary>
<Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>  _
Partial Public Class MainWindow
    Inherits System.Windows.Window
    Implements System.Windows.Markup.IComponentConnector
    
    
    #ExternalSource("..\..\MainWindow.xaml",68)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents UserLogin As System.Windows.Controls.TextBox
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\MainWindow.xaml",73)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents UserPassword As System.Windows.Controls.TextBox
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\MainWindow.xaml",78)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents SaveToFile As System.Windows.Controls.CheckBox
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\MainWindow.xaml",79)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Next1 As System.Windows.Controls.Button
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\MainWindow.xaml",90)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Captcha As System.Windows.Controls.WebBrowser
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\MainWindow.xaml",92)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents CaptchaResult As System.Windows.Controls.TextBox
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\MainWindow.xaml",97)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Next2 As System.Windows.Controls.Button
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\MainWindow.xaml",102)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Refresh As System.Windows.Controls.Button
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\MainWindow.xaml",107)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents Label32 As System.Windows.Controls.Label
    
    #End ExternalSource
    
    
    #ExternalSource("..\..\MainWindow.xaml",157)
    <System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")>  _
    Friend WithEvents my As System.Windows.Controls.TextBox
    
    #End ExternalSource
    
    Private _contentLoaded As Boolean
    
    '''<summary>
    '''InitializeComponent
    '''</summary>
    <System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")>  _
    Public Sub InitializeComponent() Implements System.Windows.Markup.IComponentConnector.InitializeComponent
        If _contentLoaded Then
            Return
        End If
        _contentLoaded = true
        Dim resourceLocater As System.Uri = New System.Uri("/GP;component/mainwindow.xaml", System.UriKind.Relative)
        
        #ExternalSource("..\..\MainWindow.xaml",1)
        System.Windows.Application.LoadComponent(Me, resourceLocater)
        
        #End ExternalSource
    End Sub
    
    <System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0"),  _
     System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never),  _
     System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes"),  _
     System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity"),  _
     System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")>  _
    Sub System_Windows_Markup_IComponentConnector_Connect(ByVal connectionId As Integer, ByVal target As Object) Implements System.Windows.Markup.IComponentConnector.Connect
        If (connectionId = 1) Then
            Me.UserLogin = CType(target,System.Windows.Controls.TextBox)
            Return
        End If
        If (connectionId = 2) Then
            Me.UserPassword = CType(target,System.Windows.Controls.TextBox)
            Return
        End If
        If (connectionId = 3) Then
            Me.SaveToFile = CType(target,System.Windows.Controls.CheckBox)
            Return
        End If
        If (connectionId = 4) Then
            Me.Next1 = CType(target,System.Windows.Controls.Button)
            Return
        End If
        If (connectionId = 5) Then
            Me.Captcha = CType(target,System.Windows.Controls.WebBrowser)
            Return
        End If
        If (connectionId = 6) Then
            Me.CaptchaResult = CType(target,System.Windows.Controls.TextBox)
            Return
        End If
        If (connectionId = 7) Then
            Me.Next2 = CType(target,System.Windows.Controls.Button)
            Return
        End If
        If (connectionId = 8) Then
            Me.Refresh = CType(target,System.Windows.Controls.Button)
            Return
        End If
        If (connectionId = 9) Then
            Me.Label32 = CType(target,System.Windows.Controls.Label)
            Return
        End If
        If (connectionId = 10) Then
            Me.my = CType(target,System.Windows.Controls.TextBox)
            Return
        End If
        Me._contentLoaded = true
    End Sub
End Class
