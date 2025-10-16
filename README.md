## Emscripten

Emscripten est un compilateur source à source open source permettant de compiler du bitcode LLVM en asm.js, qui peut être exécuté par les navigateurs web.

Le bytecode LLVM étant généré à partir de programmes écris en C ou C++, par extension Emscripten permet donc de compiler un programme C ou C++ en javascript et en WebAssembly

Emcc utilise Clang et LLVM pour être compilé en WebAssembly. Il crééer également du javascript qui fournit une API de support au code compilé en Web Assembly. Ce Javascript peut être exécuté par NodeJs ou depuis un fichier un html dans un navigateur.

### Exemple 

Pour afficher hello world en C on on aura le code suivant :

```c
// test.C
#include <stdio.h>

int main() {

    printf("Hello World \n");

    return 0;
}
```

En lançant la commande `emcc test.c ` on obtiendra deux fichiers :
1. a.out.js
2. a.out.wasm

Le premier est un fichier javascript classique, le second est en WebAssembly.

On peut le code généré avec la commande `node a.out.js`. Ce code js servira d'interface avec le code web assembly produit.

## Connexion entre code C/C++ et Js

Emscripten permet de faire communiquer du code javascript et C/C++. On peut:
* Appeler des fonctions C déjà compilé directement depuis du Js
* Appeler des classes C++ depuis javascript
* Appeler des fonctions javascript depuis du C et du C++


## CMakeList

CMake est un outil permettant de gérer la compilation d'un projet. Dans le modèle classique de compilation on a :

![Compilation simple](compilation_simple.png)

Les fichier source peuvent être des fichier C, C++, ou autre. Ceux-ci seront traités par le script de compilation qui appelera le compilateur pour créer l'exécutable final.

Le script de compilation peut avoir plusieurs formes suivant le projet et l'éditeur utilisé. En l'occurence ici un Makefile

Ce modèle à des limites car plusieurs personnes, avec plusieurs configurations, souhaiterons compiler avec différents outils.

Cmake (grâce aux CMakeList) résoud cette problématique en créant les scripts de compilation à l'aide d'un fichier de configuration générique. On à ainsi ce nouveau modèle de compilation:

![Compilation cmake](compilation_cmake.png)

Cette fois, Cmake grâce au fichier CMakeList.txt, va produire le script de compilation permettant la création de l'exécutable. Le fichier CMakeLists.txt est indépedant de la platefroem. Il décrit comment ocmpiler le projet à l'aide d'informations comme :  le langage utilisé, les fichiers à compiler, les dépendances. Ainsi CMake va pouvoir produire le script de compilation adéquat pour votre machine et votre projet. 

## Thrift 

Les fichier .thrift sont des fichier d'IDL (Interface Definition Language) qui décrivent: 
* les types et structures échangés
* les exceptions
* les services RPC

Pour générer le code cpp (qu'in peut déjà voir dan gen-cpp) on lance la commande `thrift --gen cpp social_network.thrift`. Ici ça génera le code C++ (utilisé coté serveur) sans problême.

Pour ce qui est des clients ils sont écris en lua. On génere leur code avec `thrift --gen lua social_network.thrift`. Ici je ne sais pas si c'est une différence de version (j'ai essayer avec thrift 12-13-14 et 18). Mais on doit retoucher au fichier générer. Prenez inspiration sur ceux qui existait déjà. Les erreurs que vous verrait potentiellement indique juste qu'ils faut redéclarer des variables et retourner le module à la fin des fichiers généré. C'est peut être pas très clair comme ça mais en regardant le code généré auparavant ça se fait facilement.

## Jaeger 

Jaeger (https://www.jaegertracing.io/) permet de monitorer et de tracer des micro-services.

## Sources et documentation transmise par le professeur

- [Grosse liste d’applis portées avec Emscripten](https://github.com/emscripten-core/emscripten/wiki/Porting-Examples-and-Demos)
- The browser is the computer (présentation @ WASM IO)
    - [Vidéo](https://www.youtube.com/watch?v=T5cT3U2afC0)
    - [Slides](https://speakerdeck.com/angelmmiguel/o?slide=2)
- Emscripten
    - [Networking](https://emscripten.org/docs/porting/networking.html)
- [WasmLinux (démo)](https://wasmlinux-demo.pages.dev/)
- [Fledger — cross-platform network programming in WASM libc (EPFL C4DT)](https://c4dt.epfl.ch/article/cross-platform-network-programming-in-wasm-libc/)
- Container to WASM (utilise VM, hors scope mais culture générale)
    - [container2wasm](https://github.com/container2wasm/container2wasm)
- [Tokio with WASM (Rust)](https://github.com/cunarist/tokio-with-wasm)
- [WASM it (Rust)](https://azriel.im/wasm_it/)
- PgLite — Postgres dans le navigateur
    - [Site](https://pglite.dev/)
- WebAssembly sur architectures exotiques
    - [Note](https://anil.recoil.org/notes/wasm-on-exotic-targets)
- Postgres WASM (autre Postgres dans le navigateur)
    - [Article Supabase](https://supabase.com/blog/postgres-wasm)
- Compiler du C vers WebAssembly sans Emscripten
    - [Article](https://surma.dev/things/c-to-webassembly/)
- 


## Application Social Network

![Social Network Architecture](../oldSocialNetwork/figures/socialNet_arch.png)


## Sources
* https://fr.wikipedia.org/wiki/Emscripten
* https://emscripten.org/docs/introducing_emscripten/about_emscripten.html
* https://fr.wikipedia.org/wiki/Apache_Thrift
* https://emscripten.org/docs/porting/connecting_cpp_and_javascript/Interacting-with-code.html
* https://alexandre-laurent.developpez.com/tutoriels/cmake/# social-network-dst-emscripten
