#!/bin/bash

URL="https://github.com/openframeworks/openFrameworks/releases/download/0.12.0/of_v0.12.0_vs_release.zip"
DEST_DIR="ThirdParty"
ZIP_FILE="openFrameworks.zip"

echo "Téléchargement de OpenFrameworks..."
curl -L -o "$ZIP_FILE" "$URL"

echo "Décompression..."
mkdir -p "$DEST_DIR"
unzip -q "$ZIP_FILE" -d "$DEST_DIR"

echo "Suppression de l'archive..."
rm "$ZIP_FILE"

IMGUI_REPO="https://github.com/jvcleave/ofxImGui.git"
IMGUI_DEST_DIR="ThirdParty/openFrameworks/addons/ofxImGui"

echo "Clonage du dépôt ofxImGui (branche develop)..."
git clone --branch develop --depth 1 "$IMGUI_REPO" "$IMGUI_DEST_DIR"

echo "Installation terminée."
