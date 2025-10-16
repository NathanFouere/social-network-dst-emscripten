# convertedMicroServices - Guide de Compilation et de Lancement

## Table des matières
- [Prérequis](#prérequis)
- [Configuration de l'environnement](#configuration-de-lenvironnement)
- [Compilation du projet](#compilation-du-projet)
- [Lancement du microservice](#lancement-du-microservice)
- [Utilisation](#utilisation)
- [Architecture](#architecture)
- [Dépannage](#dépannage)

## Prérequis

### Système d'exploitation
- macOS (architecture aarch64-darwin)
- Linux (architecture x86_64-linux)

### Logiciels requis
- **Nix** avec les fonctionnalités expérimentales activées
  - `nix-command`
  - `flakes`

## Configuration de l'environnement

Le projet utilise **Nix Flakes** pour gérer les dépendances de manière reproductible. Le fichier `flake.nix` (situé dans le répertoire parent `socialNetwork/`) définit toutes les dépendances nécessaires :

- **Emscripten** : Compilateur C++ vers WebAssembly
- **CMake** : Système de build
- **Node.js** : Runtime JavaScript pour exécuter le module WebAssembly

### Activation de l'environnement Nix

Pour activer l'environnement de développement avec toutes les dépendances :

```bash
cd /path/to/DeathStarBench/socialNetwork/convertedMicroServices
nix --extra-experimental-features 'nix-command flakes' develop
```

Cette commande recherchera automatiquement le `flake.nix` dans le répertoire parent et activera l'environnement.

## Compilation du projet

### Étape 1 : Nettoyage (optionnel mais recommandé)

Avant de compiler, il est recommandé de nettoyer les anciens fichiers de build :

```bash
cd /path/to/DeathStarBench/socialNetwork/convertedMicroServices
rm -rf CMakeCache.txt CMakeFiles/ Makefile cmake_install.cmake *.cjs *.wasm
```

### Étape 2 : Configuration avec CMake et Emscripten

Le projet doit être configuré avec Emscripten pour compiler en WebAssembly :

```bash
nix --extra-experimental-features 'nix-command flakes' develop -c emcmake cmake .
```

**Explication :**
- `emcmake` : Wrapper qui configure CMake pour utiliser Emscripten
- `cmake .` : Configure le projet dans le répertoire courant

**Sortie attendue :**
```
-- Configuring done
-- Generating done
-- Build files have been written to: /path/to/convertedMicroServices
```

### Étape 3 : Compilation

Une fois la configuration terminée, compilez le projet :

```bash
nix --extra-experimental-features 'nix-command flakes' develop -c emmake make
```

**Explication :**
- `emmake` : Wrapper qui configure Make pour utiliser Emscripten
- `make` : Lance la compilation

**Fichiers générés :**
- `convertedMicroServices.js` (~119 KB) : Wrapper JavaScript CommonJS pour charger le module WebAssembly
- `convertedMicroServices.wasm` (~39 KB) : Module WebAssembly compilé contenant le code C++

**Note importante :** Le fichier est généré avec l'extension `.cjs` (CommonJS) au lieu de `.js` pour éviter les conflits avec les modules ES6 dans l'environnement Node.js.

## Lancement du microservice

### Méthode 1 : Exécution simple avec Node.js

Pour lancer le microservice avec Node.js :

```bash
nix --extra-experimental-features 'nix-command flakes' develop -c node convertedMicroServices.js
```

Le microservice se charge et reste en attente. Il est conçu pour être utilisé comme une bibliothèque (voir Méthode 2 et 3).

### Méthode 2 : Utilisation dans un script Node.js

Créez un fichier `test.js` :

```javascript
// test.js
const Module = require('./convertedMicroServices.js');

Module.onRuntimeInitialized = () => {
  console.log('Module WebAssembly chargé avec succès !');

  // Créer une instance du service
  const testService = new Module.TestService();

  // Appeler la méthode TestFunction
  const result = testService.TestFunction();
  console.log('Résultat de TestFunction():', result);

  // Nettoyer
  testService.delete();

  process.exit(0);
};
```

Puis exécutez :

```bash
nix --extra-experimental-features 'nix-command flakes' develop -c node test.js
```

**Sortie attendue :**
```
Module WebAssembly chargé avec succès !
Résultat de TestFunction(): Bonjour
```

### Méthode 3 : Test rapide en une ligne

Pour tester rapidement le microservice sans créer de fichier :

```bash
nix --extra-experimental-features 'nix-command flakes' develop -c node -e "const m = require('./convertedMicroServices.js'); m.onRuntimeInitialized = () => { const s = new m.TestService(); console.log('Résultat:', s.TestFunction()); s.delete(); process.exit(0); };"
```

**Sortie attendue :**
```
Résultat: Bonjour
```

### Méthode 4 : Utilisation dans un navigateur web

Créez un fichier HTML (`index.html`) :

```html
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>convertedMicroServices - Demo</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 50px auto;
            padding: 20px;
        }
        button {
            background-color: #4CAF50;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
        }
        button:hover {
            background-color: #45a049;
        }
        #output {
            margin-top: 20px;
            padding: 15px;
            background-color: #f0f0f0;
            border-radius: 4px;
        }
    </style>
</head>
<body>
    <h1>convertedMicroServices - Démonstration</h1>
    <p>Cliquez sur le bouton pour tester le microservice WebAssembly</p>
    <button id="testBtn">Tester le microservice</button>
    <div id="output"></div>

    <script src="convertedMicroServices.js"></script>
    <script>
        Module.onRuntimeInitialized = () => {
            console.log('Module WebAssembly chargé !');
            document.getElementById('output').innerHTML = '<p style="color: green;">✓ Module WebAssembly chargé et prêt !</p>';

            document.getElementById('testBtn').addEventListener('click', () => {
                const testService = new Module.TestService();
                const result = testService.TestFunction();
                document.getElementById('output').innerHTML = `
                    <p><strong>Résultat de TestFunction():</strong></p>
                    <p style="font-size: 20px; color: #4CAF50;">${result}</p>
                `;
                testService.delete();
            });
        };
    </script>
</body>
</html>
```

Lancez un serveur HTTP local :

```bash
nix --extra-experimental-features 'nix-command flakes' develop -c python3 -m http.server 8080
```

Puis ouvrez votre navigateur à l'adresse : `http://localhost:8080`

## Utilisation

### API du microservice

Le microservice expose la classe `TestService` avec les méthodes suivantes :

#### `TestService()`
Constructeur de la classe.

```javascript
const service = new Module.TestService();
```

#### `TestFunction()`
Retourne une chaîne de caractères "Bonjour".

```javascript
const result = service.TestFunction();
console.log(result); // Output: "Bonjour"
```

#### `delete()`
Libère la mémoire allouée pour l'instance (important en WebAssembly).

```javascript
service.delete();
```

## Architecture

### Structure du projet

```
convertedMicroServices/
├── CMakeLists.txt              # Configuration CMake
├── README.md                   # Ce fichier
├── TestService/
│   ├── TestService.cpp        # Implémentation du service
│   └── TestService.hpp        # En-tête du service
└── UniqueIdHandler/           # (non utilisé actuellement)
```

### Flux de compilation

```
TestService.cpp (C++)
        ↓
  [Emscripten (emcc)]
        ↓
  convertedMicroServices.wasm + convertedMicroServices.js
        ↓
  [Node.js ou Navigateur Web]
        ↓
  Exécution du microservice
```

### Technologies utilisées

- **C++17** : Langage de programmation
- **Emscripten** : Compilateur C++ → WebAssembly
- **WebAssembly (WASM)** : Format binaire portable
- **Embind** : Bibliothèque Emscripten pour les bindings C++ ↔ JavaScript
- **CommonJS** : Format de module pour Node.js

## Dépannage

### Erreur : "experimental Nix feature 'nix-command' is disabled"

**Solution :** Ajoutez toujours les flags suivants :
```bash
nix --extra-experimental-features 'nix-command flakes' develop
```

Ou configurez Nix de manière permanente dans `~/.config/nix/nix.conf` :
```
experimental-features = nix-command flakes
```

### Erreur : "require is not defined in ES module scope"

**Cause :** Un fichier `package.json` dans un répertoire parent contient `"type": "module"`, ce qui force Node.js à traiter tous les fichiers `.js` comme des modules ES6.

**Solution :** Le projet génère maintenant des fichiers `.cjs` (CommonJS) au lieu de `.js`. Si vous avez des anciens fichiers `.js`, renommez-les :
```bash
mv convertedMicroServices.js convertedMicroServices.js
```

### Erreur : "Could NOT find Boost"

**Cause :** L'environnement Nix n'est pas activé ou le `CMakeLists.txt` contient des dépendances Boost inutiles.

**Solution :** Le `CMakeLists.txt` a été simplifié pour ne plus nécessiter Boost. Assurez-vous d'utiliser la dernière version.

### Erreur : "emscripten/bind.h: No such file or directory"

**Cause :** Le projet n'est pas configuré avec Emscripten.

**Solution :** Utilisez `emcmake cmake .` au lieu de `cmake .` seul.

### Le microservice se lance mais ne fait rien

**Cause :** Le code actuel n'a pas de fonction `main()` pour une exécution autonome.

**Solution :** Le microservice est conçu pour être utilisé comme bibliothèque. Utilisez-le dans un script JavaScript comme montré dans la section [Méthode 2](#méthode-2--utilisation-dans-un-script-nodejs) ou testez avec la [Méthode 3](#méthode-3--test-rapide-en-une-ligne).

## Commandes rapides

### Workflow complet (nettoyage + compilation + test)

```bash
# Se placer dans le bon répertoire
cd /path/to/DeathStarBench/socialNetwork/convertedMicroServices

# Nettoyage
rm -rf CMakeCache.txt CMakeFiles/ Makefile cmake_install.cmake *.cjs *.wasm

# Configuration avec Emscripten
nix --extra-experimental-features 'nix-command flakes' develop -c emcmake cmake .

# Compilation
nix --extra-experimental-features 'nix-command flakes' develop -c emmake make

# Test rapide
nix --extra-experimental-features 'nix-command flakes' develop -c node -e "const m = require('./convertedMicroServices.js'); m.onRuntimeInitialized = () => { const s = new m.TestService(); console.log('Résultat:', s.TestFunction()); s.delete(); process.exit(0); };"
```

**Sortie attendue du test :**
```
Résultat: Bonjour
```

### Alias utiles (à ajouter dans votre `.zshrc` ou `.bashrc`)

```bash
alias nix-dev='nix --extra-experimental-features "nix-command flakes" develop'
alias build-wasm='rm -rf CMakeCache.txt CMakeFiles/ *.cjs *.wasm && nix-dev -c emcmake cmake . && nix-dev -c emmake make'
alias test-wasm='nix-dev -c node -e "const m = require(\"./convertedMicroServices.js\"); m.onRuntimeInitialized = () => { const s = new m.TestService(); console.log(\"Résultat:\", s.TestFunction()); s.delete(); process.exit(0); };"'
```

Utilisation :
```bash
nix-dev          # Active l'environnement
build-wasm       # Compile le projet
test-wasm        # Teste le microservice
```

## Résumé rapide

**Pour compiler et tester en 4 commandes :**

```bash
cd /path/to/DeathStarBench/socialNetwork/convertedMicroServices
nix --extra-experimental-features 'nix-command flakes' develop -c emcmake cmake .
nix --extra-experimental-features 'nix-command flakes' develop -c emmake make
nix --extra-experimental-features 'nix-command flakes' develop -c node -e "const m = require('./convertedMicroServices.js'); m.onRuntimeInitialized = () => { const s = new m.TestService(); console.log('Résultat:', s.TestFunction()); s.delete(); process.exit(0); };"
```

## Liens utiles

* Bind.h : https://emscripten.org/docs/api_reference/bind.h.html
* Embind: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html


## Auteur et Licence

Projet : DeathStarBench - Social Network Microservices
Date : Octobre 2025

---

**Note :** Ce projet fait partie du benchmark DeathStarBench et est destiné à des fins d'apprentissage et de recherche sur les architectures microservices.
