@echo off
set "RAYLIB_DLL_PATH=%~dp0raylib.dll"
chcp 65001 >nul
title 🌻 SUNNY WORLD - Launcher
color 0A

:: ================================================================
::  SUNNY WORLD - Smart Launcher
::  Tự kiểm tra môi trường và chạy game ngay
::  Không cần cài đặt gì thêm!
:: ================================================================

set "GAME_EXE=%~dp0sunny_world.exe"
set "RAYLIB_DLL=%~dp0raylib.dll"
set "RAYLIB_DLL_URL=https://github.com/raysan5/raylib/releases/download/5.0/raylib-5.0_win64_msvc16.zip"

echo.
echo  ╔══════════════════════════════════════════════════════╗
echo  ║        🌻  SUNNY WORLD  -  FARM SIMULATOR  🌻        ║
echo  ║                    Smart Launcher                    ║
echo  ╚══════════════════════════════════════════════════════╝
echo.

:: ── Kiểm tra file .exe ──────────────────────────────────────────
if not exist "%GAME_EXE%" (
    echo  ❌ Không tìm thấy sunny_world.exe!
    echo.
    echo  Hãy đảm bảo file check_and_run.bat nằm CÙNG THƯ MỤC
    echo  với sunny_world.exe
    echo.
    echo  📁 Cấu trúc đúng:
    echo     📂 OSG202_Project\
    echo        ├── sunny_world.exe   ✅
    echo        ├── check_and_run.bat ✅
    echo        └── assets\           ✅
    echo.
    pause & exit /b 1
)

:: ── Thử chạy game ngay (nếu linked static thì không cần DLL) ───
echo  🔍 Đang kiểm tra game...

:: Kiểm tra xem exe có import raylib.dll không
powershell -Command "$b=[System.IO.File]::ReadAllBytes('%GAME_EXE%'); $s=[System.Text.Encoding]::ASCII.GetString($b); if($s -match 'raylib\.dll'){exit 1}else{exit 0}" >nul 2>&1
if %errorlevel% equ 0 (
    echo  ✅ Game được link tĩnh - không cần raylib.dll
    goto :RUN_GAME
)

:: ── Cần DLL - kiểm tra có sẵn chưa ─────────────────────────────
echo  ℹ️  Game cần raylib.dll để chạy...

if exist "%RAYLIB_DLL%" (
    echo  ✅ raylib.dll đã có sẵn.
    goto :RUN_GAME
)

:: ── Tải raylib.dll tự động ──────────────────────────────────────
echo  📥 Đang tải raylib.dll (lần đầu duy nhất ~1MB)...

:: Tải zip raylib
set "TEMP_ZIP=%TEMP%\raylib_temp.zip"
powershell -Command "& {[Net.ServicePointManager]::SecurityProtocol='Tls12'; $ProgressPreference='SilentlyContinue'; Invoke-WebRequest -Uri '%RAYLIB_DLL_URL%' -OutFile '%TEMP_ZIP%' -UseBasicParsing}" >nul 2>&1

if not exist "%TEMP_ZIP%" (
    echo.
    echo  ❌ Không tải được raylib.dll - Kiểm tra internet!
    echo.
    echo  Tải thủ công tại:
    echo  %RAYLIB_DLL_URL%
    echo  Giải nén → lấy file raylib.dll → đặt vào cùng thư mục với game
    echo.
    pause & exit /b 1
)

:: Giải nén và lấy raylib.dll
powershell -Command "& { Add-Type -AssemblyName System.IO.Compression.FileSystem; $zip=[System.IO.Compression.ZipFile]::OpenRead('%TEMP_ZIP%'); foreach($e in $zip.Entries){ if($e.Name -eq 'raylib.dll'){ [System.IO.Compression.ZipFileExtensions]::ExtractToFile($e,'%RAYLIB_DLL%',$true) } }; $zip.Dispose() }" >nul 2>&1
del /f /q "%TEMP_ZIP%" >nul 2>&1

if exist "%RAYLIB_DLL%" (
    echo  ✅ raylib.dll đã tải xong!
) else (
    echo  ❌ Không lấy được raylib.dll từ zip!
    pause & exit /b 1
)

:: ================================================================
:RUN_GAME
:: ================================================================

:: Kiểm tra thư mục assets
if not exist "%~dp0assets" (
    echo.
    echo  ⚠️  CẢNH BÁO: Không tìm thấy thư mục assets\
    echo  Game có thể bị lỗi thiếu hình ảnh/âm thanh!
    echo  Hãy đảm bảo clone đầy đủ repo từ GitHub.
    echo.
    timeout /t 3 /nobreak >nul
)

echo.
echo  ════════════════════════════════════════════════════════
echo   🌻 Đang khởi động SUNNY WORLD...
echo.
echo   🎮 ĐIỀU KHIỂN:
echo      WASD       - Di chuyển        Shift  - Chạy nhanh
echo      1~6        - Chọn công cụ     I      - Túi đồ
echo      B          - Cửa hàng         N      - Chuồng trại
echo      Q          - Nhiệm vụ         F2     - Thành tựu
echo  ════════════════════════════════════════════════════════
echo.

cd /d "%~dp0"
start "" "%GAME_EXE%"

echo  ✅ SUNNY WORLD đã khởi động! Chúc bạn chơi vui! 🌾
timeout /t 3 /nobreak >nul
exit /b 0
