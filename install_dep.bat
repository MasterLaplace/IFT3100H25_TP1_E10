@echo off
set URL=https://github.com/openframeworks/openFrameworks/releases/download/0.12.0/of_v0.12.0_vs_release.zip
set DEST_DIR=ThirdParty
set ZIP_FILE=openFrameworks.zip

echo Téléchargement de OpenFrameworks...
curl -L -o %ZIP_FILE% %URL%

echo Décompression...
powershell -Command "Expand-Archive -Path %ZIP_FILE% -DestinationPath %DEST_DIR% -Force"

echo Suppression de l'archive...
del %ZIP_FILE%

set IMGUI_REPO=https://github.com/jvcleave/ofxImGui.git
set IMGUI_DEST_DIR=ThirdParty\openFrameworks\addons\ofxImGui

echo Clonage du dépôt ofxImGui (branche develop)...
git clone --branch develop --depth 1 %IMGUI_REPO% %IMGUI_DEST_DIR%

echo Installation terminée.
pause
