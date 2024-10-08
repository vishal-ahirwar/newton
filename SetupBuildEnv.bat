@echo [Important] Make sure run this command with administrator privileges
@echo This will install MinGW-13 Compiler and CMake 3.30
@echo Installing Choco xd...
@echo off
powershell -Command Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
choco install mingw
choco install cmake
@echo on
@echo All done
@echo You may need to run this script again :xd