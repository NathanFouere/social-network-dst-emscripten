# Comment fonctionne le WASM dans convertedMicroServices ?

## 🤔 Votre question : Le WASM est-il intégré au .cjs ?

**Réponse courte :** **Non**, le fichier `.wasm` n'est **pas intégré** dans le fichier `.cjs`. Ce sont deux fichiers **séparés** qui travaillent ensemble.

## 📦 Les deux fichiers générés

Quand vous compilez avec Emscripten, vous obtenez **2 fichiers distincts** :

```
convertedMicroServices.js    (~119 KB)  ← Wrapper JavaScript
convertedMicroServices.wasm   (~39 KB)   ← Code binaire WebAssembly
```

### 1. **convertedMicroServices.wasm** 
- Contient votre **code C++ compilé** en format binaire WebAssembly
- C'est le "vrai" code de votre classe `TestService` et de la méthode `TestFunction()`
- Format binaire, non lisible par un humain
- Petit et très rapide à exécuter

### 2. **convertedMicroServices.js**
- Fichier JavaScript (CommonJS) qui sert de **wrapper/loader**
- Son rôle : charger le fichier `.wasm` et créer une interface JavaScript
- Contient tout le "glue code" généré par Emscripten
- Gère la mémoire, les appels entre JS et WASM, etc.

## 🔗 Comment ça fonctionne ensemble ?

### Étape par étape quand vous exécutez le code :

```javascript
const Module = require('./convertedMicroServices.js');
```

**Ce qui se passe en coulisses :**

#### Étape 1 : Chargement du fichier .cjs
```
Node.js charge convertedMicroServices.js
     ↓
Le fichier .cjs s'exécute
```

#### Étape 2 : Recherche du fichier .wasm
Le fichier `.cjs` contient cette fonction :

```javascript
function findWasmBinary() {
    return locateFile('convertedMicroServices.wasm');
}
```

Cette fonction cherche le fichier `.wasm` dans le **même répertoire** que le fichier `.cjs`.

#### Étape 3 : Chargement du fichier .wasm
```javascript
// Dans le fichier .cjs (simplifié)
var wasmBinaryFile = findWasmBinary();  // → 'convertedMicroServices.wasm'

// Lecture du fichier binaire
var wasmBinary = fs.readFileSync(wasmBinaryFile);

// Instantiation du module WebAssembly
var wasmInstance = await WebAssembly.instantiate(wasmBinary);
```

#### Étape 4 : Création des bindings
Le fichier `.cjs` utilise **Embind** (bibliothèque Emscripten) pour créer des "ponts" entre JavaScript et WebAssembly :

```javascript
// Code généré automatiquement par Emscripten
class_<TestService>("TestService")
  .constructor<>()
  .function("TestFunction", &TestService::TestFunction);
```

Devient accessible en JavaScript comme :

```javascript
const service = new Module.TestService();  // Appelle le constructeur C++
const result = service.TestFunction();      // Appelle la méthode C++
```

#### Étape 5 : Callback onRuntimeInitialized
```javascript
Module.onRuntimeInitialized = () => {
  // À ce stade, le .wasm est chargé et prêt !
  console.log('Prêt à utiliser');
};
```

## 🎯 Schéma complet du flux

```
┌─────────────────────────────────────────────────────────┐
│  Votre code JavaScript                                  │
│  const m = require('./convertedMicroServices.js');    │
└─────────────────────┬───────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────────────┐
│  convertedMicroServices.js (Wrapper JavaScript)        │
│  ┌───────────────────────────────────────────────┐     │
│  │ 1. Détecte l'environnement (Node.js/Browser)  │     │
│  │ 2. Localise le fichier .wasm                  │     │
│  │ 3. Charge le binaire .wasm                    │     │
│  │ 4. Instancie WebAssembly                      │     │
│  │ 5. Crée les bindings JS ↔ C++                │     │
│  │ 6. Expose l'objet Module                      │     │
│  └───────────────┬───────────────────────────────┘     │
└──────────────────┼─────────────────────────────────────┘
                   │
                   ▼ fs.readFileSync()
┌─────────────────────────────────────────────────────────┐
│  convertedMicroServices.wasm (Code binaire)             │
│  ┌───────────────────────────────────────────────┐     │
│  │  Code machine WebAssembly                     │     │
│  │  - TestService::TestService() (constructeur)  │     │
│  │  - TestService::TestFunction() (méthode)      │     │
│  │  - return "Bonjour"                           │     │
│  └───────────────────────────────────────────────┘     │
└─────────────────────────────────────────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────────────────────┐
│  Résultat retourné à JavaScript                         │
│  "Bonjour"                                              │
└─────────────────────────────────────────────────────────┘
```

## 📂 Structure des fichiers nécessaires

**IMPORTANT** : Vous devez **toujours** avoir les **deux fichiers** dans le même répertoire :

```
convertedMicroServices/
├── convertedMicroServices.js   ← Obligatoire
├── convertedMicroServices.wasm  ← Obligatoire (chargé par le .cjs)
└── test.js                      ← Votre code qui utilise le module
```

Si vous déplacez le fichier `.cjs` sans le `.wasm`, vous aurez une erreur :

```
Error: Cannot find module 'convertedMicroServices.wasm'
```

## 🔍 Vérification pratique

Pour voir exactement ce qui se passe, créez un fichier `debug.js` :

```javascript
const Module = require('./convertedMicroServices.js');

console.log('1. Fichier .cjs chargé');
console.log('2. Module =', typeof Module);

Module.onRuntimeInitialized = () => {
    console.log('3. Fichier .wasm chargé et initialisé !');
    console.log('4. Module.TestService =', typeof Module.TestService);

    const service = new Module.TestService();
    console.log('5. Instance créée (constructeur C++ appelé)');

    const result = service.TestFunction();
    console.log('6. Méthode C++ appelée, résultat:', result);

    service.delete();
    console.log('7. Mémoire libérée (destructeur C++ appelé)');

    process.exit(0);
};

console.log('0. En attente du chargement du .wasm...');
```

Exécutez :
```bash
nix --extra-experimental-features 'nix-command flakes' develop -c node debug.js
```

Résultat attendu :
```
0. En attente du chargement du .wasm...
1. Fichier .cjs chargé
2. Module = object
3. Fichier .wasm chargé et initialisé !
4. Module.TestService = function
5. Instance créée (constructeur C++ appelé)
6. Méthode C++ appelée, résultat: Bonjour
7. Mémoire libérée (destructeur C++ appelé)
```

## 🌐 Différence avec d'autres approches

### Option A : WASM séparé (votre cas actuel) ✅
```
convertedMicroServices.js  (119 KB - loader JavaScript)
convertedMicroServices.wasm (39 KB  - code binaire)
Total: 158 KB, 2 fichiers
```

**Avantages :**
- Fichiers plus petits
- Le .wasm peut être mis en cache séparément
- Mieux pour le navigateur (streaming compilation)

### Option B : WASM intégré (embedding) ❌
Emscripten peut aussi générer un **seul fichier** avec le WASM encodé en Base64 dedans :

```bash
emcc ... -s SINGLE_FILE=1  # Option non utilisée ici
```

Résultat : 
```
convertedMicroServices.js  (~200 KB - contient tout)
Total: 200 KB, 1 fichier
```

**Inconvénients :**
- Fichier plus gros (encodage Base64 = +33%)
- Pas de cache séparé
- Chargement plus lent

## 💡 Pourquoi cette architecture ?

Cette séparation en 2 fichiers est **optimale** car :

1. **Performance** : Le navigateur peut compiler le `.wasm` pendant qu'il télécharge (streaming)
2. **Cache** : Si vous modifiez le JavaScript mais pas le C++, seul le `.cjs` change
3. **Taille** : Format binaire `.wasm` plus compact que Base64
4. **Standard** : Architecture recommandée par le W3C et Emscripten

## 🎓 Récapitulatif

| Fichier | Rôle | Contenu | Nécessaire ? |
|---------|------|---------|--------------|
| `.cjs` | Loader/Wrapper | Code JavaScript qui charge le WASM | ✅ Oui |
| `.wasm` | Code binaire | Votre code C++ compilé | ✅ Oui |
| `.cpp` | Source | Code source C++ | ❌ Non (déjà compilé) |

**En résumé :**
- Le `.cjs` et le `.wasm` sont **deux fichiers séparés**
- Le `.cjs` **charge dynamiquement** le `.wasm` au runtime
- Les **deux fichiers sont nécessaires** pour que ça fonctionne
- Le `.cjs` est le "chef d'orchestre" qui gère tout

---

**Note** : Si vous voulez voir le code binaire du `.wasm`, vous pouvez utiliser :
```bash
wasm-objdump -x convertedMicroServices.wasm  # Affiche la structure
wasm2wat convertedMicroServices.wasm          # Convertit en format texte
```

Mais c'est très bas niveau ! Le fichier `.cjs` fait tout le travail pour vous. 😊

