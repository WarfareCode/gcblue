; GCB2.nsi
;
; This script is based on example2.nsi -- it remembers the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install files into a directory that the user selects,
;--------------------------------


;--------------------------------
!define RELEASE_VERSION ; define to include all maps, etc for release
;--------------------------------




!define FILEROOT "install_gcb2_126_23OCT"

; Set filename to write
!ifdef RELEASE_VERSION
    OutFile "${FILEROOT}_full.exe"
!else
    OutFile "${FILEROOT}_patch.exe"
!endif


; The name of the installer
Name "install_gcb2_126"


; The default installation directory
InstallDir $PROGRAMFILES\GCB2

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\GCB2" "Install_Dir"


;--------------------------------
!define PROGRAM_NAME "GCB2"
;--------------------------------

!macro BackupFile FILE_DIR FILE BACKUP_DIR BACKUP_FILE
 IfFileExists "${BACKUP_DIR}\*.*" +2
  CreateDirectory "${BACKUP_DIR}"
 IfFileExists "${FILE_DIR}\${FILE}" 0 +2
  CopyFiles "${FILE_DIR}\${FILE}" "${BACKUP_DIR}\${BACKUP_FILE}"
!macroend

!macro RestoreFile BUP_DIR FILE RESTORE_TO RESTORE_FILE
 IfFileExists "${BUP_DIR}\${FILE}" 0 +2
  CopyFiles "${BUP_DIR}\${FILE}" "${RESTORE_TO}\${RESTORE_FILE}"
!macroend

Function GetDXVersion
	Push $0
	Push $1

	ReadRegStr $0 HKLM "Software\Microsoft\DirectX" "Version"
	IfErrors noDirectX

	StrCpy $1 $0 2 5    ; get the minor version
	StrCpy $0 $0 2 2    ; get the major version
	IntOp $0 $0 * 100   ; $0 = major * 100 + minor
	IntOp $0 $0 + $1
	Goto done

	noDirectX:
	  StrCpy $0 0

	done:
	  Pop $1
	  Exch $0
FunctionEnd

Function .onInit

  Call GetDXVersion
  Pop $R3
  
  IntCmp $R3 900 +3 +1 +1
    MessageBox "MB_OK" "Requires DirectX 9.0c. Update DirectX and try again."
    Abort
	

  ; -- don't bother checking for uninstall for patch install
  !ifdef RELEASE_VERSION

  ReadRegStr $R0 HKLM \
  "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PROGRAM_NAME}" \
  "UninstallString"
  StrCmp $R0 "" done
 


  MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
  "${PROGRAM_NAME} is already installed. $\n$\nClick `OK` to upgrade and overwrite the \
  previous version or `Cancel` to cancel this upgrade.\n\nPlease backup scenario, \
  database, save files, etc from previous installation before proceeding. Installer \
  will copy most old files to install_backup directory." \
  IDOK done
  Abort
  
  
;Run the uninstaller
uninst:
  ClearErrors
  ExecWait '$R0 _?=$INSTDIR' ;Do not copy the uninstaller to a temp file
 
  IfErrors no_remove_uninstaller
    ;You can either use Delete /REBOOTOK in the uninstaller or add some code
    ;here to remove to remove the uninstaller. Use a registry key to check
    ;whether the user has chosen to uninstall. If you are using an uninstaller
    ;components page, make sure all sections are uninstalled.
  no_remove_uninstaller:

  !endif  


done:
 
FunctionEnd





;--------------------------------

LicenseText "License Agreement"
LicenseData "LICENSE.txt"

; Pages

Page license
Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "GCB2 (required)"

  SectionIn RO
  

; ----- 3d directory -----
  SetOutPath $INSTDIR\3d

;  !ifdef RELEASE_VERSION
  File "3d\*.xml"  
  File "3d\*.bmp"
  File "3d\*.gif"
  File "3d\*.jpg"
  File "3d\*.png"
  File "3d\*.tvm"
;  !endif
  
  SetOutPath $INSTDIR\3d\fonts

  File "3d\fonts\*.ttf"

  SetOutPath $INSTDIR\3d\shaders

  File "3d\shaders\*.vert"
  File "3d\shaders\*.frag"

  SetOutPath $INSTDIR\3d\particle

  File "3d\particle\*.tvp"
  File "3d\particle\*.dds"
  File "3d\particle\*.png"  
  
; ----- bin directory -----
  SetOutPath $INSTDIR\bin


  File "bin\boost_python-vc110-mt-1_57.dll"
;  File "bin\iconv.dll"
;  File "bin\libxml2.dll"
  File "bin\oalpp_gcb.dll"
  File "bin\ot13-OpenThreads.dll"
  File "bin\TV3D65.dll"
  File "bin\alut.dll"
  File "bin\oalinst.exe"
  File "bin\vcredist_x86.exe"
  
  File "bin\BlueII.exe"
  
  !ifdef RELEASE_VERSION
  File "bin\dxwebsetup.exe"
  File "bin\python27.dll"
  
  SetOutPath $INSTDIR\bin\Lib
  File /r "bin\Lib\*.pyc"
  !else
;  File "bin\blue.map"
  !endif
  


;  SetOutPath $INSTDIR\bin\Microsoft.VC80.CRT

;  File "bin\x86redist\*.*"


; ----- database directory -----
  SetOutPath $INSTDIR\database
  !insertmacro BackupFile $INSTDIR\database "*.*" $INSTDIR\install_backup\database ""
 
  File "database\database.db"
  File "database\accounts.db"
  File "database\test_addon.db"
  File "database\atmosphere.csv"
;  File "database\*.exe" ; Include database editor file

  SetOutPath $INSTDIR\database\text

  File "database\text\*.txt"

; ----- help directory -----
;  SetOutPath $INSTDIR\help

;  File "help\*.*"

; ----- images directory -----
  SetOutPath $INSTDIR\images
  !insertmacro BackupFile $INSTDIR\images "*.*" $INSTDIR\install_backup\images ""
  
  File "images\*.jpg"
  File "images\*.bmp"
  File "images\*.png"
  File "images\*.dds"

; ----- images\symbology directory -----
  SetOutPath $INSTDIR\images\symbology\m2525

  File "images\symbology\m2525\*.png"

  SetOutPath $INSTDIR\images\symbology\ntds

  File "images\symbology\ntds\*.png"

; ----- images\icons directory -----
  SetOutPath $INSTDIR\images\icons

  File "images\icons\*.jpg"

  SetOutPath $INSTDIR\images\icons\air

  File "images\icons\air\*.jpg"

  SetOutPath $INSTDIR\images\icons\mis

  File "images\icons\mis\*.jpg"

  SetOutPath $INSTDIR\images\icons\torp

  File "images\icons\torp\*.jpg"

  SetOutPath $INSTDIR\images\icons\ball

  File "images\icons\ball\*.jpg"

  SetOutPath $INSTDIR\images\db

  File "images\db\*.*"

  SetOutPath $INSTDIR\images\dbviewer

  File "images\dbviewer\*.png"
  
  SetOutPath $INSTDIR\images\flags

  File "images\flags\*.png"


; ----- log director -----
  SetOutPath $INSTDIR\log

  File "log\stderr.txt"

; ----- aar directory -----
  SetOutPath $INSTDIR\aar
  !insertmacro BackupFile $INSTDIR\aar "*.*" $INSTDIR\install_backup\aar ""

; ----- manual directory -----
  SetOutPath $INSTDIR\manual
  
  File "manual\GCB2_Manual_v125.pdf"


; ----- scenarios directories -----

  SetOutPath $INSTDIR\scenarios
  !insertmacro BackupFile $INSTDIR\scenarios "*.*" $INSTDIR\install_backup\scenarios ""

;  SetOutPath $INSTDIR\scenarios\MultiPlayer
  
;  File "scenarios\MultiPlayer\*.py"

; ----- START single player scenarios -----

  SetOutPath $INSTDIR\scenarios\SinglePlayer
  
  File "scenarios\SinglePlayer\*.py"

  SetOutPath $INSTDIR\scenarios\SinglePlayer\ColdWar

  File "scenarios\SinglePlayer\ColdWar\*.py"

  SetOutPath $INSTDIR\scenarios\SinglePlayer\Germany

  File "scenarios\SinglePlayer\Germany\*.py"

  SetOutPath $INSTDIR\scenarios\SinglePlayer\Iran

  File "scenarios\SinglePlayer\Iran\*.py"

  SetOutPath $INSTDIR\scenarios\SinglePlayer\Japan

  File "scenarios\SinglePlayer\Japan\*.py"


;  SetOutPath $INSTDIR\scenarios\SinglePlayer\Taiwan
 
;  File "scenarios\SinglePlayer\Taiwan\*.py"
  

;  SetOutPath $INSTDIR\scenarios\SinglePlayer\Venezuela

;  File "scenarios\SinglePlayer\Venezuela\*.py"

;  SetOutPath $INSTDIR\scenarios\SinglePlayer\Vietnam

;  File "scenarios\SinglePlayer\Vietnam\*.py"


;  SetOutPath $INSTDIR\scenarios\SinglePlayer\Libya

;  File "scenarios\SinglePlayer\Libya\*.py"




; ----- END single player scenarios -----

  SetOutPath $INSTDIR\scenarios\Saved

  File "scenarios\Saved\__init__.py"
  
  SetOutPath $INSTDIR\scenarios\Saved\backup

  SetOutPath $INSTDIR\scenarios\EditorSaved

  File "scenarios\EditorSaved\__init__.py"

;  SetOutPath $INSTDIR\scenarios\Test

;  File "scenarios\Test\*.py"

;  SetOutPath $INSTDIR\scenarios\Tutorial

;  File "scenarios\Tutorial\*.py"


; ----- scripts directory -----
  SetOutPath $INSTDIR\scripts
  !insertmacro BackupFile $INSTDIR\scripts "*.*" $INSTDIR\install_backup\scripts ""
  
  File "scripts\*.py"
  File "scripts\*.txt"

  SetOutPath $INSTDIR\scripts\Amram_Script_Data
  File "scripts\Amram_Script_Data\*.py"
  
  SetOutPath $INSTDIR\scripts\Amram_Script_Data\Aircraft
  File "scripts\Amram_Script_Data\Aircraft\*.csv"

  SetOutPath $INSTDIR\scripts\Amram_Script_Data\CSVs
  File "scripts\Amram_Script_Data\CSVs\*.csv"

  !ifdef RELEASE_VERSION
; ----- sound\ogg directory -----
  SetOutPath $INSTDIR\sound\ogg

  File "sound\ogg\*.ogg"

; ----- sound\wav directory -----
  SetOutPath $INSTDIR\sound\wav

  File "sound\wav\*.wav"
  !endif

; ----- xml directory -----
  SetOutPath $INSTDIR\xml
  !insertmacro BackupFile $INSTDIR\xml "*.*" $INSTDIR\install_backup\xml ""
  
  File "xml\*.xml"


; ----- db editor -----
!ifdef _INSTALL_DBEDIT_
  SetOutPath $INSTDIR\dbedit
  SetOutPath $INSTDIR\dbedit\bin
  
  File "dbeditor\dbeditor\bin\EditGCB.exe"
  File "dbeditor\dbeditor\bin\sqlite.dll"
  File "dbeditor\dbeditor\bin\boost_python-vc110-1_55.dll"
  File "dbeditor\dbeditor\bin\oalpp_gcb.dll"
  File "dbeditor\dbeditor\bin\OpenThreadsWin32.dll"
  File "dbeditor\dbeditor\bin\python27.dll"
  File "dbeditor\dbeditor\bin\TV3D65.dll"
  File "dbeditor\dbeditor\bin\alut.dll"

  SetOutPath $INSTDIR\dbedit\config
  File /x config*.xml "dbeditor\config\*.xml"
  File "/oname=config.xml" "dbeditor\config\config_deploy.xml"
  File "dbeditor\config\*.txt"
  
  SetOutPath $INSTDIR\dbedit\database
  File "dbeditor\database\atmosphere.csv"

  SetOutPath $INSTDIR\dbedit\backup
  !insertmacro BackupFile $INSTDIR\dbedit\backup "*.*" $INSTDIR\install_backup\dbedit\backup ""  
!endif

; ----- general -----
  SetOutPath $INSTDIR

  File "LICENSE.txt"

;  File "bin\BlueII.lic"

  CreateShortCut "Play GCB2.lnk" "$INSTDIR\bin\BlueII.exe"
  ;CreateShortCut "Database Editor.lnk" "$INSTDIR\dbedit\bin\EditGCB.exe"



  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\GCB2 "Install_Dir" "$INSTDIR"
  
  ; set dll path
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\App Paths\BlueII.exe" "" '"$INSTDIR\BlueII.exe"'
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\App Paths\BlueII.exe" "Path" '"$INSTDIR\bin"'

  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\GCB2" "DisplayName" "Global Conflict Blue 2 1.26"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\GCB2" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\GCB2" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\GCB2" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  

SectionEnd

Section "Install Maps"
  !ifdef RELEASE_VERSION
; ----- maps directory -----
  SetOutPath $INSTDIR\maps

  File "maps\*.dat"

; ----- maps\tiles directory -----
  SetOutPath $INSTDIR\maps\tiles
  
  File "maps\tiles\tiles.7z"
  Nsis7z::Extract "tiles.7z"
  Delete "$INSTDIR\maps\tiles\tiles.7z"
  
;  File "maps\tiles\*.dat"

  SetOutPath $INSTDIR\maps\tiles\lowres

  File "maps\tiles\lowres\*.dat"

  SetOutPath $INSTDIR\maps\tiles\lowres10

  File "maps\tiles\lowres10\*.dat"  
  
  SetOutPath $INSTDIR\maps\tiles\medres

  File "maps\tiles\medres\*.dat"  
  
  !endif
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"
  SetShellVarContext all
  
  CreateDirectory "$SMPROGRAMS\GCB2"
  CreateShortCut "$SMPROGRAMS\GCB2\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\GCB2\Play GCB2.lnk" "$INSTDIR\bin\BlueII.exe" "" "$INSTDIR\bin\BlueII.exe" 0
  CreateShortCut "$SMPROGRAMS\GCB2\Game manual.lnk" "$INSTDIR\manual\GCB2_Manual_v125.pdf" "" "$INSTDIR\manual\GCB2_Manual_v125.pdf" 0
  
  SetOutPath "$INSTDIR\dbedit\bin"
  CreateShortCut "$SMPROGRAMS\GCB2\Database editor.lnk" "$INSTDIR\dbedit\bin\EditGCB.exe" "" "$INSTDIR\dbedit\bin\EditGCB.exe" 0

SectionEnd

!ifdef RELEASE_VERSION

Section "Install OpenAL files"

  Exec '"$INSTDIR\bin\oalinst.exe" '

SectionEnd


Section "Install VC++ binaries"

  Exec '"$INSTDIR\bin\vcredist_x86.exe" '

SectionEnd

Section "Update DirectX 9.0c (dxwebsetup.exe)"

  Exec '"$INSTDIR\bin\dxwebsetup.exe" '

SectionEnd

!endif

;--------------------------------

; Uninstaller

Section "Uninstall"
  SetShellVarContext all
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\GCB2"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\App Paths\BlueII.exe"
  DeleteRegKey HKLM SOFTWARE\NSIS_GCB2

  ; Remove files and uninstaller
  Delete $INSTDIR\*.lic
  Delete $INSTDIR\*.txt
  Delete $INSTDIR\*.lnk
  Delete $INSTDIR\*.exe
  
  RMDir /r $INSTDIR\aar
  RMDir /r $INSTDIR\bin
  RMDir /r $INSTDIR\3d
  RMDir /r $INSTDIR\database
  RMDir /r $INSTDIR\dbedit
  RMDir /r $INSTDIR\images
  RMDir /r $INSTDIR\log
  RMDir /r $INSTDIR\manual
  RMDir /r $INSTDIR\maps
  RMDir /r $INSTDIR\scenarios
  RMDir /r $INSTDIR\sound
  RMDir /r $INSTDIR\xml
  RMDir /r $INSTDIR\scripts
  RMDir /r $INSTDIR\dbedit

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\GCB2\*.*"

  ; Remove directories used
  RMDir /r "$SMPROGRAMS\GCB2"
  ;RMDir /r "$INSTDIR"


SectionEnd

