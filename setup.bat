@echo off
chcp 65001 >nul
title 🌻 SUNNY WORLD - Auto Setup & Launcher
color 0A

:: ================================================================
::  SUNNY WORLD - Auto Setup Script
::  Tự động cài: Git, MinGW (GCC), Raylib → Build → Chạy game
::  Repo: https://github.com/hbui74727-pixel/OSG202_Project
:: ================================================================

set "REPO_URL=https://github.com/hbui74727-pixel/OSG202_Project.git"
set "GAME_DIR=%~dp0OSG202_Project"
set "TOOLS_DIR=%~dp0tools"
set "MINGW_DIR=%TOOLS_DIR%\mingw64"
set "RAYLIB_DIR=%TOOLS_DIR%\raylib"
set "RAYLIB_VER=5.0"
set "MINGW_URL=https://github.com/niXman/mingw-builds-binaries/releases/download/13.2.0-rt_v11-rev1/x86_64-13.2.0-release-posix-seh-msvcrt-rt_v11-rev1.7z"
set "RAYLIB_URL=https://github.com/raysan5/raylib/releases/download/5.0/raylib-5.0_win64_mingw-w64.zip"
set "SEVENZIP_URL=https://www.7-zip.org/a/7zr.exe"

echo.
echo  ╔══════════════════════════════════════════════════════╗
echo  ║        🌻  SUNNY WORLD  -  FARM SIMULATOR  🌻        ║
echo  ║              Auto Setup ^& Launcher v1.0              ║
echo  ╚══════════════════════════════════════════════════════╝
echo.

:: ── Kiểm tra quyền Admin ────────────────────────────────────────
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo  [!] Script cần quyền Administrator để cài đặt.
    echo  [!] Đang yêu cầu quyền Admin...
    powershell -Command "Start-Process '%~f0' -Verb RunAs"
    exit /b
)

:: ── Tạo thư mục tools ───────────────────────────────────────────
if not exist "%TOOLS_DIR%" mkdir "%TOOLS_DIR%"

:: ================================================================
::  BƯỚC 1 - Kiểm tra / Cài đặt 7-Zip portable
:: ================================================================
echo  [1/5] Kiểm tra công cụ giải nén...
set "SEVENZIP=%TOOLS_DIR%\7zr.exe"
if not exist "%SEVENZIP%" (
    echo       Đang tải 7-Zip portable...
    powershell -Command "& {[Net.ServicePointManager]::SecurityProtocol='Tls12'; Invoke-WebRequest -Uri '%SEVENZIP_URL%' -OutFile '%SEVENZIP%' -UseBasicParsing}" >nul 2>&1
    if not exist "%SEVENZIP%" (
        echo  [LỖI] Không tải được 7-Zip. Kiểm tra kết nối internet!
        pause & exit /b 1
    )
    echo       ✓ 7-Zip đã sẵn sàng.
) else (
    echo       ✓ 7-Zip đã có.
)

:: ================================================================
::  BƯỚC 2 - Kiểm tra / Cài đặt Git
:: ================================================================
echo.
echo  [2/5] Kiểm tra Git...
git --version >nul 2>&1
if %errorlevel% neq 0 (
    echo       Git chưa có. Đang tải Git portable...
    set "GIT_INSTALLER=%TOOLS_DIR%\git_installer.exe"
    set "GIT_URL=https://github.com/git-for-windows/git/releases/download/v2.44.0.windows.1/Git-2.44.0-64-bit.exe"
    powershell -Command "& {[Net.ServicePointManager]::SecurityProtocol='Tls12'; Invoke-WebRequest -Uri '%GIT_URL%' -OutFile '%TOOLS_DIR%\git_installer.exe' -UseBasicParsing}" >nul 2>&1
    if exist "%TOOLS_DIR%\git_installer.exe" (
        echo       Đang cài Git (tự động, không cần thao tác)...
        "%TOOLS_DIR%\git_installer.exe" /VERYSILENT /NORESTART /NOCANCEL /SP- /CLOSEAPPLICATIONS /RESTARTAPPLICATIONS /COMPONENTS="icons,ext\reg\shellhere,assoc,assoc_sh" >nul 2>&1
        del /f /q "%TOOLS_DIR%\git_installer.exe" >nul 2>&1
        :: Cập nhật PATH
        set "PATH=%PATH%;C:\Program Files\Git\cmd;C:\Program Files\Git\bin"
        git --version >nul 2>&1
        if %errorlevel% equ 0 (
            echo       ✓ Git đã cài xong.
        ) else (
            echo  [LỖI] Cài Git thất bại. Hãy tải thủ công tại: https://git-scm.com
            pause & exit /b 1
        )
    ) else (
        echo  [LỖI] Không tải được Git. Kiểm tra kết nối internet!
        pause & exit /b 1
    )
) else (
    for /f "tokens=*" %%v in ('git --version 2^>nul') do echo       ✓ %%v
)

:: ================================================================
::  BƯỚC 3 - Kiểm tra / Cài đặt MinGW (GCC)
:: ================================================================
echo.
echo  [3/5] Kiểm tra MinGW (GCC compiler)...

:: Tìm GCC trong nhiều vị trí
set "GCC_FOUND=0"
gcc --version >nul 2>&1
if %errorlevel% equ 0 set "GCC_FOUND=1"

if "%GCC_FOUND%"=="0" (
    if exist "%MINGW_DIR%\bin\gcc.exe" (
        set "PATH=%MINGW_DIR%\bin;%PATH%"
        set "GCC_FOUND=1"
    )
)

if "%GCC_FOUND%"=="0" (
    :: Tìm mingw64 trong các vị trí phổ biến
    if exist "C:\mingw64\bin\gcc.exe" (
        set "PATH=C:\mingw64\bin;%PATH%"
        set "MINGW_DIR=C:\mingw64"
        set "GCC_FOUND=1"
    ) else if exist "C:\msys64\mingw64\bin\gcc.exe" (
        set "PATH=C:\msys64\mingw64\bin;%PATH%"
        set "MINGW_DIR=C:\msys64\mingw64"
        set "GCC_FOUND=1"
    ) else if exist "C:\Program Files\mingw-w64\x86_64-13.2.0-posix-seh-rt_v11-rev1\mingw64\bin\gcc.exe" (
        set "PATH=C:\Program Files\mingw-w64\x86_64-13.2.0-posix-seh-rt_v11-rev1\mingw64\bin;%PATH%"
        set "GCC_FOUND=1"
    )
)

if "%GCC_FOUND%"=="0" (
    echo       MinGW chưa có. Đang tải MinGW-w64 (~50MB)...
    echo       (Quá trình này mất vài phút, vui lòng chờ...)
    set "MINGW_ARCHIVE=%TOOLS_DIR%\mingw64.7z"
    powershell -Command "& {[Net.ServicePointManager]::SecurityProtocol='Tls12'; $ProgressPreference='SilentlyContinue'; Invoke-WebRequest -Uri '%MINGW_URL%' -OutFile '%MINGW_ARCHIVE%' -UseBasicParsing}" >nul 2>&1
    if exist "%MINGW_ARCHIVE%" (
        echo       Đang giải nén MinGW...
        "%SEVENZIP%" x "%MINGW_ARCHIVE%" -o"%TOOLS_DIR%" -y >nul 2>&1
        del /f /q "%MINGW_ARCHIVE%" >nul 2>&1
        :: Tìm thư mục mingw64 vừa giải nén
        for /d %%d in ("%TOOLS_DIR%\mingw64*") do set "MINGW_DIR=%%d"
        if exist "%MINGW_DIR%\bin\gcc.exe" (
            set "PATH=%MINGW_DIR%\bin;%PATH%"
            set "GCC_FOUND=1"
            echo       ✓ MinGW đã cài xong.
        ) else (
            echo  [LỖI] Giải nén MinGW thất bại!
            pause & exit /b 1
        )
    ) else (
        echo  [LỖI] Không tải được MinGW. Kiểm tra kết nối internet!
        echo  [GỢI Ý] Tải thủ công tại: https://winlibs.com
        pause & exit /b 1
    )
) else (
    for /f "tokens=*" %%v in ('gcc --version 2^>nul ^| findstr /i "gcc"') do echo       ✓ %%v
)

:: ================================================================
::  BƯỚC 4 - Kiểm tra / Cài đặt Raylib
:: ================================================================
echo.
echo  [4/5] Kiểm tra Raylib...

set "RAYLIB_FOUND=0"
if exist "%RAYLIB_DIR%\include\raylib.h" set "RAYLIB_FOUND=1"
if exist "%MINGW_DIR%\include\raylib.h" set "RAYLIB_FOUND=1"

:: Tìm raylib trong include system
if "%RAYLIB_FOUND%"=="0" (
    if exist "C:\raylib\include\raylib.h" (
        set "RAYLIB_DIR=C:\raylib"
        set "RAYLIB_FOUND=1"
    )
)

if "%RAYLIB_FOUND%"=="0" (
    echo       Raylib chưa có. Đang tải Raylib %RAYLIB_VER%...
    set "RAYLIB_ARCHIVE=%TOOLS_DIR%\raylib.zip"
    powershell -Command "& {[Net.ServicePointManager]::SecurityProtocol='Tls12'; $ProgressPreference='SilentlyContinue'; Invoke-WebRequest -Uri '%RAYLIB_URL%' -OutFile '%RAYLIB_ARCHIVE%' -UseBasicParsing}" >nul 2>&1
    if exist "%RAYLIB_ARCHIVE%" (
        echo       Đang giải nén Raylib...
        powershell -Command "Expand-Archive -Path '%RAYLIB_ARCHIVE%' -DestinationPath '%TOOLS_DIR%\raylib_temp' -Force" >nul 2>&1
        del /f /q "%RAYLIB_ARCHIVE%" >nul 2>&1

        :: Tìm và di chuyển thư mục raylib
        for /d %%d in ("%TOOLS_DIR%\raylib_temp\raylib*") do (
            if not exist "%RAYLIB_DIR%" mkdir "%RAYLIB_DIR%"
            xcopy "%%d\*" "%RAYLIB_DIR%\" /e /i /q /y >nul 2>&1
        )
        rd /s /q "%TOOLS_DIR%\raylib_temp" >nul 2>&1

        if exist "%RAYLIB_DIR%\include\raylib.h" (
            :: Copy raylib vào mingw để compiler tìm thấy tự động
            copy /y "%RAYLIB_DIR%\include\raylib.h" "%MINGW_DIR%\include\" >nul 2>&1
            copy /y "%RAYLIB_DIR%\include\raymath.h" "%MINGW_DIR%\include\" >nul 2>&1
            copy /y "%RAYLIB_DIR%\include\rlgl.h" "%MINGW_DIR%\include\" >nul 2>&1
            copy /y "%RAYLIB_DIR%\lib\libraylib.a" "%MINGW_DIR%\lib\" >nul 2>&1
            echo       ✓ Raylib %RAYLIB_VER% đã cài xong.
            set "RAYLIB_FOUND=1"
        ) else (
            echo  [LỖI] Giải nén Raylib thất bại!
            pause & exit /b 1
        )
    ) else (
        echo  [LỖI] Không tải được Raylib. Kiểm tra kết nối internet!
        pause & exit /b 1
    )
) else (
    echo       ✓ Raylib đã có.
)

:: ================================================================
::  BƯỚC 5 - Clone / Update repo và Build game
:: ================================================================
echo.
echo  [5/5] Chuẩn bị source code và build game...

if exist "%GAME_DIR%\.git" (
    echo       Repo đã có. Đang cập nhật (git pull)...
    cd /d "%GAME_DIR%"
    git pull origin main >nul 2>&1
    echo       ✓ Đã cập nhật code mới nhất.
) else (
    echo       Đang clone repo từ GitHub...
    git clone "%REPO_URL%" "%GAME_DIR%" >nul 2>&1
    if not exist "%GAME_DIR%\src" (
        echo  [LỖI] Clone repo thất bại! Kiểm tra link: %REPO_URL%
        pause & exit /b 1
    )
    echo       ✓ Clone xong.
)

cd /d "%GAME_DIR%"

:: Kiểm tra xem có .exe sẵn không
if exist "%GAME_DIR%\sunny_world.exe" (
    echo.
    echo  ╔══════════════════════════════════════════════════════╗
    echo  ║   ✅  Tìm thấy sunny_world.exe - Sẵn sàng chạy!    ║
    echo  ╚══════════════════════════════════════════════════════╝
    goto :RUN_GAME
)

:: Build từ source
echo       Đang compile game (có thể mất 30-60 giây)...
echo.

:: Tạo danh sách source files
set "SRCS="
set "SRCS=%SRCS% src/main.c"
set "SRCS=%SRCS% src/account_manager.c"
set "SRCS=%SRCS% src/audio_manager.c"
set "SRCS=%SRCS% src/access_control.c"
set "SRCS=%SRCS% src/achievement_system.c"
set "SRCS=%SRCS% src/admin_commands.c"
set "SRCS=%SRCS% src/data_manager.c"
set "SRCS=%SRCS% src/entity_manager.c"
set "SRCS=%SRCS% src/event_system.c"
set "SRCS=%SRCS% src/game_logic.c"
set "SRCS=%SRCS% src/quest_system.c"
set "SRCS=%SRCS% src/renderer.c"
set "SRCS=%SRCS% src/textures.c"
set "SRCS=%SRCS% src/font_manager.c"
set "SRCS=%SRCS% src/tree_system.c"
set "SRCS=%SRCS% src/draw/draw_animal.c"
set "SRCS=%SRCS% src/draw/draw_building.c"
set "SRCS=%SRCS% src/draw/draw_crop.c"
set "SRCS=%SRCS% src/draw/draw_debug.c"
set "SRCS=%SRCS% src/draw/draw_hud.c"
set "SRCS=%SRCS% src/draw/draw_player.c"
set "SRCS=%SRCS% src/draw/draw_tile.c"
set "SRCS=%SRCS% src/draw/draw_ui.c"

set "INCLUDE_FLAGS=-Iinclude -Isrc -Isrc/draw"
if exist "%RAYLIB_DIR%\include" set "INCLUDE_FLAGS=%INCLUDE_FLAGS% -I%RAYLIB_DIR%\include"

set "LIB_FLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm"
if exist "%RAYLIB_DIR%\lib" set "LIB_FLAGS=-L%RAYLIB_DIR%\lib %LIB_FLAGS%"

:: Thử dùng Makefile trước
where mingw32-make >nul 2>&1
if %errorlevel% equ 0 (
    echo       Dùng Makefile để build...
    mingw32-make build 2>&1
) else (
    echo       Dùng GCC trực tiếp để build...
    gcc %SRCS% -o sunny_world.exe %INCLUDE_FLAGS% %LIB_FLAGS% -O2 2>&1
)

if exist "sunny_world.exe" (
    echo.
    echo  ╔══════════════════════════════════════════════════════╗
    echo  ║          ✅  BUILD THÀNH CÔNG! Game sẵn sàng.       ║
    echo  ╚══════════════════════════════════════════════════════╝
) else (
    echo.
    echo  ╔══════════════════════════════════════════════════════╗
    echo  ║     ❌  BUILD THẤT BẠI - Xem lỗi ở trên            ║
    echo  ╚══════════════════════════════════════════════════════╝
    echo.
    echo  Gợi ý xử lý lỗi phổ biến:
    echo    - "raylib.h not found" : Raylib chưa copy vào include
    echo    - "undefined reference": Thiếu file .c hoặc lib
    echo    - "cannot find -lraylib": Thiếu libraylib.a
    echo.
    pause
    exit /b 1
)

:: ================================================================
:RUN_GAME
:: ================================================================
echo.
echo  ════════════════════════════════════════════════════════
echo   🌻  Đang khởi động SUNNY WORLD...
echo   📁  Thư mục game: %GAME_DIR%
echo   🎮  Điều khiển: WASD di chuyển, Shift chạy nhanh
echo   🔑  Phím I: Túi đồ  ^|  B: Cửa hàng  ^|  Q: Nhiệm vụ
echo  ════════════════════════════════════════════════════════
echo.
timeout /t 2 /nobreak >nul

start "" "%GAME_DIR%\sunny_world.exe"

echo  ✅ Game đã khởi động! Chúc bạn chơi vui vẻ! 🌾
echo.
echo  (Cửa sổ này sẽ tự đóng sau 5 giây...)
timeout /t 5 /nobreak >nul
exit /b 0
