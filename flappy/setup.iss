[Setup]
AppName=Flappy Bird
AppVersion=1.0
DefaultDirName={autopf}\Flappy Bird
DefaultGroupName=Flappy Bird
UninstallDisplayIcon={app}\icon.ico
; Add your .ico file here to change the installer's icon
SetupIconFile=icon.ico
Compression=lzma2
SolidCompression=yes
OutputDir=.
OutputBaseFilename=FlappyBird_Installer

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "flappybird.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "icon.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "FlappyBird.png"; DestDir: "{app}"; Flags: ignoreversion
Source: "audio\*"; DestDir: "{app}\audio"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "sprites\*"; DestDir: "{app}\sprites"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "highscore.dat"; DestDir: "{app}"; Flags: ignoreversion onlyifdoesntexist

[Icons]
Name: "{group}\Flappy Bird"; Filename: "{app}\flappybird.exe"; IconFilename: "{app}\icon.ico"
Name: "{group}\{cm:UninstallProgram,Flappy Bird}"; Filename: "{uninstallexe}"; IconFilename: "{app}\icon.ico"
Name: "{autodesktop}\Flappy Bird"; Filename: "{app}\flappybird.exe"; Tasks: desktopicon; IconFilename: "{app}\icon.ico"

[Run]
Filename: "{app}\flappybird.exe"; Description: "{cm:LaunchProgram,Flappy Bird}"; Flags: nowait postinstall skipifsilent
