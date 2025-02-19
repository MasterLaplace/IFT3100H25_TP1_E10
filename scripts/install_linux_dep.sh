# Description: Script d'installation des dépendances pour Linux
# Version: 1.0
#!/bin/bash

cd ThirdParty

# Téléchargez l'archive openFrameworks avec curl
curl -L -o of_v0.12.0_linux64gcc6_release.tar.gz https://github.com/openframeworks/openFrameworks/releases/download/0.12.0/of_v0.12.0_linux64gcc6_release.tar.gz

# Extrayez l'archive téléchargée
tar -xzf of_v0.12.0_linux64gcc6_release.tar.gz

# Déplacez-vous dans le répertoire extrait
cd of_v0.12.0_linux64gcc6_release

git clone --branch develop --depth 1 https://github.com/jvcleave/ofxImGui.git addons/ofxImGui

# Installez les dépendances nécessaires
sudo ./scripts/linux/ubuntu/install_dependencies.sh

# Compilez les bibliothèques openFrameworks
cd libs/openFrameworksCompiled/project
make

# Revenez au répertoire racine d'openFrameworks
cd ../../..

./scripts/linux/compileOF.sh -j3
./scripts/linux/compilePG.sh

cd ../..

make -j3
