; Spacify NSIS Installer
; Built by GitHub Actions — do not edit version strings manually

!define APP_NAME    "Spacify"
!define APP_EXE     "spacify-client.exe"
!define PUBLISHER   "Spacify"
!define BUNDLE_ID   "com.spacify.App"
!define INSTALL_DIR "$PROGRAMFILES64\${APP_NAME}"

; Passed in from CI:
;   -DAPP_VERSION=x.y.z
;   -DFOUR_PART_VERSION=x.y.z.0   (required by VIProductVersion)
;   -DARTIFACT_BASE=Spacify-vX.Y.Z-windows
;   -DICONS_DIR=resources\icons    (relative to where makensis runs, i.e. repo root)
!ifndef APP_VERSION
  !define APP_VERSION "1.0.0"
!endif
!ifndef FOUR_PART_VERSION
  !define FOUR_PART_VERSION "1.0.0.0"
!endif
!ifndef ARTIFACT_BASE
  !define ARTIFACT_BASE "Spacify-windows"
!endif
!ifndef ICONS_DIR
  !define ICONS_DIR "resources\icons"
!endif

Name          "${APP_NAME} ${APP_VERSION}"
OutFile       "${ARTIFACT_BASE}-setup.exe"
InstallDir    "${INSTALL_DIR}"
InstallDirRegKey HKLM "Software\${APP_NAME}" "Install_Dir"
RequestExecutionLevel admin
SetCompressor /SOLID lzma

;-------------------------------------------------
; Modern UI
;-------------------------------------------------
!include "MUI2.nsh"

!define MUI_ABORTWARNING
!define MUI_ICON    "${ICONS_DIR}\app.ico"
!define MUI_UNICON  "${ICONS_DIR}\app.ico"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"

;-------------------------------------------------
; Version metadata
;-------------------------------------------------
VIProductVersion "${FOUR_PART_VERSION}"
VIAddVersionKey "ProductName"     "${APP_NAME}"
VIAddVersionKey "ProductVersion"  "${APP_VERSION}"
VIAddVersionKey "CompanyName"     "${PUBLISHER}"
VIAddVersionKey "FileDescription" "${APP_NAME} Installer"
VIAddVersionKey "FileVersion"     "${APP_VERSION}"

;-------------------------------------------------
; Install
;-------------------------------------------------
Section "Install"
  SetOutPath "$INSTDIR"
  File /r "dist\Spacify\*.*"

  ; Registry: uninstall entry
  WriteRegStr HKLM \
    "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
    "DisplayName"    "${APP_NAME}"
  WriteRegStr HKLM \
    "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
    "UninstallString" "$INSTDIR\uninstall.exe"
  WriteRegStr HKLM \
    "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
    "Publisher"       "${PUBLISHER}"
  WriteRegStr HKLM \
    "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
    "DisplayVersion"  "${APP_VERSION}"
  WriteRegStr HKLM \
    "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
    "DisplayIcon"     "$INSTDIR\${APP_EXE}"

  ; Shortcuts
  CreateDirectory "$SMPROGRAMS\${APP_NAME}"
  CreateShortcut  "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk" \
    "$INSTDIR\${APP_EXE}" "" "$INSTDIR\${APP_EXE}"
  CreateShortcut  "$DESKTOP\${APP_NAME}.lnk" \
    "$INSTDIR\${APP_EXE}" "" "$INSTDIR\${APP_EXE}"

  WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

;-------------------------------------------------
; Uninstall
;-------------------------------------------------
Section "Uninstall"
  RMDir /r "$INSTDIR"

  Delete "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk"
  RMDir  "$SMPROGRAMS\${APP_NAME}"
  Delete "$DESKTOP\${APP_NAME}.lnk"

  DeleteRegKey HKLM \
    "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"
SectionEnd
