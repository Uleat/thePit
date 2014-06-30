Imports System.IO
Imports System.Diagnostics
Public Class Form1
    ' There are currently no handlers assigned to clear running processes...
    ' You will need to manually kill these processes in 'Task Manager' is you choose to run this program
    ' (right-click the solution to build..no need to publish)

    ' This program captures message traffic from the process instead of letting a console display it.
    ' Obviously, the downfall is that messages the console would normally catch do not appear in the
    ' IO stream. My research into this indicates the it has to do with the way that a console is implemented.
    ' My 'guess' is that background thread pipes are not tapped..but I don't know for sure...

    ' This is a proof of concept program only. It is considered open source, if anyone would like to develop it.
    ' The AsyncCallback code is third-party and will need to be modified from its current state or appropriate
    ' consent given/acknowledged before public distribution is allowed.

    ' Place this program in your eqemu directory and execute in place of your serverstart.bat file.

    ' -----

    ' Will probably change most controls to late-bound objects to help with memory use

    Dim ConsoleMenuStrip As New MenuStrip With {.Dock = DockStyle.Top}
    Dim ConsoleStatusStrip As New StatusStrip With {.Dock = DockStyle.Bottom}
    Dim ConsoleTabControl As New TabControl With {.Dock = DockStyle.Fill,
                                                  .Appearance = TabAppearance.Buttons}

    Dim MainTab As New TabPage With {.Name = "Tab_ConsoleMain",
                                     .Text = "Main",
                                     .BorderStyle = BorderStyle.Fixed3D}
    Dim WithEvents StartButton As New Button With {.Name = "btn_StartServer",
                                                   .Text = "Start Server",
                                                   .Font = New Font(System.Drawing.FontFamily.GenericSansSerif, 12),
                                                   .Size = New Size(120, 50),
                                                   .Location = New Point((MainTab.Width / 2) - 60,
                                                                         (MainTab.Height / 2) - 25),
                                                   .Anchor = AnchorStyles.None}


    Dim LoginServerTab As New Shell_TabPage With {.Name = "Tab_ConsoleLoginServer",
                                                  .Text = "Login Server Echo",
                                                  .BorderStyle = BorderStyle.Fixed3D}
    Dim WorldServerTab As New Shell_TabPage With {.Name = "Tab_ConsoleWorldServer",
                                                  .Text = "World Server Echo",
                                                  .BorderStyle = BorderStyle.Fixed3D}
    Dim UCSServerTab As New Shell_TabPage With {.Name = "Tab_ConsoleUCSServer",
                                                  .Text = "UCS Server Echo",
                                                  .BorderStyle = BorderStyle.Fixed3D}
    Dim QueryServerTab As New Shell_TabPage With {.Name = "Tab_ConsoleQueryServer",
                                                  .Text = "Query Server Echo",
                                                  .BorderStyle = BorderStyle.Fixed3D}
    Dim LauncherTab As New Shell_TabPage With {.Name = "Tab_ConsoleLauncher",
                                               .Text = "Launcher Echo",
                                               .BorderStyle = BorderStyle.Fixed3D}

    Dim WithEvents WorldStartTimer As New Timer With {.Interval = 1000} ' Used for testing init methods
    Dim WithEvents UCSStartTimer As New Timer With {.Interval = 10000}
    Dim WithEvents QueryStartTimer As New Timer With {.Interval = 3000}
    Dim WithEvents ZoneStartTimer As New Timer With {.Interval = 3000}

    Private Sub Me_Shown() Handles Me.Shown
        'Me.SuspendLayout()

        Me.Text = "Emulator Console"
        Me.MinimumSize = New Size(640, 480)

        Me.Controls.Add(ConsoleTabControl)
        Me.Controls.Add(ConsoleMenuStrip)
        Me.Controls.Add(ConsoleStatusStrip)


        MainTab.Controls.Add(StartButton)
        ConsoleTabControl.TabPages.Add(MainTab)

        ConsoleTabControl.TabPages.Add(LoginServerTab)
        ConsoleTabControl.TabPages.Add(WorldServerTab)
        ConsoleTabControl.TabPages.Add(UCSServerTab)
        ConsoleTabControl.TabPages.Add(QueryServerTab)
        ConsoleTabControl.TabPages.Add(LauncherTab)

        'Me.ResumeLayout()
    End Sub

    Private Sub btn_StartServer_Click(sender As System.Object, e As System.EventArgs) Handles StartButton.Click
        sender.Enabled = False

        LoginServerTab.ShellProgram = "loginserver.exe"
        LoginServerTab.ShellStart()

        WorldStartTimer.Start()
    End Sub

    Private Sub WorldStartTimer_Tick() Handles WorldStartTimer.Tick
        WorldStartTimer.Stop()

        WorldServerTab.ShellProgram = "world.exe"
        WorldServerTab.ShellStart()

        UCSStartTimer.Start()
    End Sub

    Private Sub UCSStartTimer_Tick() Handles UCSStartTimer.Tick
        UCSStartTimer.Stop()

        UCSServerTab.ShellProgram = "ucs.exe"
        UCSServerTab.ShellStart()

        QueryStartTimer.Start()
    End Sub

    Private Sub QueryStartTimer_Tick() Handles QueryStartTimer.Tick
        QueryStartTimer.Stop()

        QueryServerTab.ShellProgram = "queryserv.exe"
        QueryServerTab.ShellStart()

        ZoneStartTimer.Start()
    End Sub

    Private Sub ZoneStartTimer_Tick() Handles ZoneStartTimer.Tick
        ZoneStartTimer.Stop()

        LauncherTab.ShellProgram = "eqlaunch.exe zone"
        LauncherTab.ShellStart()
    End Sub


    Public Class Shell_TabPage
        Inherits TabPage

        ' Program termination results in processes being orphaned..
        ' Multiple restarts of program results in multiple copies of orphaned processes..
        ' Need to find proper exit method for process upon form/me.disposing

        ' Larger buffers seem to be 'locking' process and causing initialization issues..
        ' Launcher.exe appears to be restarting zone (1) in excess of 100 times..
        ' Server appears to operate normally regardless of initialization issues..
        ' Trying smaller buffers..may need to adjust callback process

        ' Need to add method/handler for window title

        Dim _titlewindow As New TextBox
        Dim _outputwindow As New TextBox

        Dim _isrunning As Boolean
        Dim _executable As String = vbNullString

        Public Event IsUpdating(ByVal sender As Object)
        Public Event HasTerminated(ByVal sender As Object)

        Public Property ShellProgram() As String
            Get
                Return _executable
            End Get
            Set(ByVal value As String)
                If _isrunning Then
                    ' Already running message
                    Exit Property
                    'ElseIf _executable.Equals(Not Nothing) Then
                    ' Already assigned message
                    ' Exit Property
                Else
                    _executable = value
                End If
            End Set
        End Property

        Private Sub TabPage_Initialize() Handles Me.HandleCreated
            Me.SuspendLayout()

            Me.Controls.Add(_titlewindow)
            Me.Controls.Add(_outputwindow)

            With _titlewindow
                .ReadOnly = True
                .Multiline = False
                .BorderStyle = Windows.Forms.BorderStyle.None
                .Location = New Point(0, 0)
                .Width = Me.ClientSize.Width
                .Anchor = AnchorStyles.Left Or AnchorStyles.Top Or AnchorStyles.Right
            End With

            With _outputwindow
                .ReadOnly = True
                .Multiline = True
                .ScrollBars = ScrollBars.Vertical
                .Location = New Point(0, _titlewindow.Bottom)
                .Width = Me.ClientSize.Width
                .Height = Me.ClientSize.Height - _outputwindow.Top
                .Anchor = AnchorStyles.Left Or AnchorStyles.Top Or AnchorStyles.Right Or AnchorStyles.Bottom
            End With

            Me.ResumeLayout()
        End Sub

        Private Sub TabPage_Finalize() Handles Me.Disposed
            ' Reserverd
        End Sub

        Public Sub ShellStart()
            'If Not _executable Then
            '_outputwindow.Text = "[Console_Error] No executable has been assigned!"
            'Exit Sub
            'End If

            _isrunning = True

            _titlewindow.Text = _executable
            _outputwindow.Text = "Starting: " & _executable & vbCrLf & vbCrLf

            Dim cmd As New CmdProcessor
            AddHandler cmd.TextReceived, AddressOf Me.cmd_TextReceived
            cmd.Execute(_executable)
        End Sub

        Public Sub ShellStop()
            ' Reserverd
            ' _isrunning = False
        End Sub

        Public Sub ShellKill()
            ' Reserved
            ' _isrunning = False
        End Sub

        Private Sub cmd_TextReceived(ByVal sender As Object, ByVal e As CmdProcessorEventArgs)

            If (Me.InvokeRequired) Then
                Me.Invoke(New CmdProcessorEventHandler(AddressOf Me.cmd_TextReceived), New Object() {sender, e})
            Else
                _outputwindow.AppendText(e.Output)
            End If
        End Sub

        Public Class CmdProcessor

            Public Sub Execute(ByVal command As String)

                _process = Me.InitializeProcess(command)
                _executing = True
                _process.Start()

                Me.AttachStreams()
                Me.PrepareAsyncState()

                _standardOutput.BaseStream.BeginRead _
                    (_outputBuffer,
                     0,
                     _outputBuffer.Length,
                     _outputReady,
                     _outputState)

                _standardError.BaseStream.BeginRead _
                    (_errorBuffer,
                     0,
                     _errorBuffer.Length,
                     _errorReady,
                     _errorState)

            End Sub

            Public Event TextReceived As CmdProcessorEventHandler

            Private Function GetStartInfo(ByVal command As String) As ProcessStartInfo
                Dim psi As New ProcessStartInfo
                psi.FileName = "cmd.exe"

                psi.Arguments = "/c " + command
                psi.UseShellExecute = False
                psi.RedirectStandardError = True
                psi.RedirectStandardOutput = True
                psi.CreateNoWindow = True

                Return psi
            End Function

            Private Function InitializeProcess(ByVal command As String) As Process
                If (_executing) Then
                    Throw New ApplicationException("Another process is currently executing")
                End If

                _process = New Process
                _process.StartInfo = GetStartInfo(command)
                _process.EnableRaisingEvents = True
                AddHandler _process.Exited, AddressOf _process_Exited

                Return _process
            End Function

            Private Sub _process_Exited(ByVal sender As Object, ByVal e As EventArgs)

                Dim exitCode As Integer
                exitCode = _process.ExitCode


                RaiseEvent TextReceived(Me,
                                        New CmdProcessorEventArgs(exitCode.ToString()))

                _process.Dispose()
                _process = Nothing
                _executing = False

            End Sub

            Private Sub AttachStreams()
                _standardOutput = _process.StandardOutput
                _standardError = _process.StandardError
            End Sub

            Private Sub OutputCallback(ByVal ar As IAsyncResult)

                Dim state As Asyncstate
                state = DirectCast(ar.AsyncState, 
                                   Asyncstate)

                Dim count As Integer
                count = state.Stream.BaseStream.EndRead(ar)

                If (count > 0) Then
                    Dim text As String
                    text = System.Text.Encoding.ASCII.GetString(state.buffer, 0, count)
                    RaiseEvent TextReceived(Me,
                                            New CmdProcessorEventArgs(text))

                    state.Stream.BaseStream.BeginRead _
                        (state.buffer,
                         0,
                         state.buffer.Length,
                         _outputReady,
                         state)
                End If
            End Sub

            Private Sub PrepareAsyncState()
                _outputReady = New AsyncCallback(AddressOf OutputCallback)
                _outputState = New Asyncstate(_standardOutput, _outputBuffer)
                _errorReady = New AsyncCallback(AddressOf OutputCallback)
                _errorState = New Asyncstate(_standardError, _errorBuffer)
            End Sub

            Private _executing As Boolean
            Private _process As Process
            Private _standardOutput As StreamReader
            Private _standardError As StreamReader

            ' Larger buffers seem to make problems worse
            Private _errorBuffer(512) As Byte ' default size = 512B
            Private _outputBuffer(512) As Byte ' default size = 512B

            Private _outputReady As AsyncCallback
            Private _outputState As Asyncstate
            Private _errorReady As AsyncCallback
            Private _errorState As Asyncstate

            Class Asyncstate

                Public Sub New(ByVal stream As StreamReader, ByVal buffer As Byte())
                    _stream = stream
                    _buffer = buffer
                End Sub

                Public ReadOnly Property Stream() As StreamReader
                    Get
                        Return _stream
                    End Get
                End Property

                Public ReadOnly Property buffer() As Byte()
                    Get
                        Return _buffer
                    End Get
                End Property

                Protected _stream As StreamReader
                Protected _buffer As Byte()
            End Class

        End Class

        Public Delegate Sub CmdProcessorEventHandler(ByVal sender As Object, ByVal e As CmdProcessorEventArgs)

        Public Class CmdProcessorEventArgs

            Public Sub New(ByVal text As String)
                _text = text
            End Sub

            Public Property Output() As String
                Get
                    Return _text
                End Get

                Set(ByVal value As String)
                    _text = value
                End Set
            End Property

            Protected _text As String
        End Class
    End Class


End Class
