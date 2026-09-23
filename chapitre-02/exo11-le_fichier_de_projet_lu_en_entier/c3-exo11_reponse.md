#  Exercice 11:

**Fichier étudié :** `Applications/NKXRDemo/NKXRDemo.jenga`
**Projet :** Nkentseu
**Nombre de lignes :** 77
**Dernière modification :** 11 août 2026
**Commit :** `831a5d60`

Le fichier `NKXRDemo.jenga` a été parcouru intégralement, y compris les commentaires et la documentation présents dans le fichier. L'analyse ci-dessous repose sur les informations fournies par le fichier de projet ainsi que sur les éléments du code source auxquels ses commentaires font référence.

---

## 1. Ce que construit le projet

Le fichier construit un seul projet nommé **`NKXRDemo`**.

Il s'agit d'une application graphique de type :

```text
windowedapp()
```

Le projet est développé en **C++17** et récupère automatiquement les fichiers sources présents dans :

```text
src/**.cpp
```

La démonstration correspond au premier niveau de la mission consacrée à **NKXR**. Elle permet de simuler une scène de réalité virtuelle sur un écran classique, sans utiliser directement un casque VR.

La scène est rendue en **stéréo simulée** : les deux images correspondant aux deux yeux sont affichées côte à côte.

Le fonctionnement de la démonstration est le suivant :

* la souris permet de simuler les mouvements de la tête ;
* les touches **ZQSD/WASD** permettent de se déplacer ;
* chaque œil dispose de son propre renderer ;
* les images sont d'abord rendues hors écran ;
* un renderer compositeur rassemble ensuite les images pour l'affichage final.

Le projet prévoit également plusieurs variables d'environnement destinées aux tests automatisés :

* `NK_XR_SIM_POSE` : permet de fixer une pose simulée ;
* `NK_XR_SHOT` : permet de réaliser une capture pour chaque œil ;
* `NK_XR_EXIT` : permet de contrôler la fermeture de l'application.

L'exécutable produit est placé dans un chemin de la forme :

```text
Build/Bin/<config>-<système>/NKXRDemo
```

Le projet contient également des métadonnées concernant le paquet, notamment :

* l'éditeur : **Rihen Universe** ;
* la version : **0.1.0** ;
* la licence du dépôt.

---

##  Dépendances du projet

Le projet utilise l'appel :

```text
nkentseudependson([...])
```

Cet appel permet de déclarer les différents modules dont l'application dépend. Au total, **23 modules** sont utilisés.

Les principales catégories de modules sont les suivantes.

### Réalité étendue et rendu

* `NKXR`
* `NKRenderer`
* `NKRHI`
* `NKSL`
* `NKGLSlang`
* `NKSPIRVCross`
* `NKGlad`

Ces modules permettent notamment de gérer la réalité étendue, le rendu graphique et les shaders.

### Gestion des ressources

* `NKFont`
* `NKImage`
* `NKSerialization`
* `NKReflection`
* `NKFileSystem`
* `NKStream`

Ils assurent différentes fonctions liées aux fichiers, images, polices, flux et données.

### Fenêtre et événements

* `NKWindow`
* `NKEvent`

Ils permettent notamment de créer la fenêtre et de gérer les interactions avec l'utilisateur.

### Modules fondamentaux

* `NKMath`
* `NKTime`
* `NKLogger`
* `NKContainers`
* `NKMemory`
* `NKCore`
* `NKPlatform`
* `NKThreading`

Ils constituent les différentes briques fondamentales nécessaires au fonctionnement de l'application.

Le projet utilise également les fichiers du dossier `src` ainsi que les **en-têtes Vulkan 1.4.350** fournis dans le dossier `Externals`.

---

##  Adaptation du projet selon le système

Le fichier `.jenga` prévoit des configurations différentes selon le système d'exploitation.

| Élément                   | Windows                                                                                                                            | Linux                                | macOS                           |
| ------------------------- | ---------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------ | ------------------------------- |
| Chaîne de compilation     | `TC_WINDOWS` (`nk-windows-clang-mingw`)                                                                                            | `clang-native`                       | `clang-native`                  |
| Définitions               | `WIN32_LEAN_AND_MEAN`, `_UNICODE`, `UNICODE`                                                                                       | `NKENTSEU_FORCE_WINDOWING_XLIB_ONLY` | Aucune                          |
| Bibliothèques principales | `user32`, `gdi32`, `opengl32`, `dwmapi`, `shell32`, `advapi32`, `d3d11`, `d3d12`, `dxgi`, `dxguid`, `d3dcompiler`, `uuid`, `ole32` | `pthread`, `X11`, `Xext`, `GL`       | `Cocoa`, `QuartzCore`, `OpenGL` |

### Linux

La configuration Linux utilise le backend **XLib**.

Le filtre correspondant est activé lorsque :

```text
linux-backend=xlib
```

est spécifié, ou lorsqu'aucune option `linux-backend` ni `headless` n'est fournie.

### Plateformes non prises en charge dans ce fichier

Le fichier étudié ne contient pas de configuration spécifique pour :

* Android ;
* Web ;
* Wayland ;
* UWP.

Les paramètres relatifs à **Debug** et **Release** sont quant à eux communs aux différentes plateformes.

En Debug, l'optimisation est désactivée et les symboles de débogage sont conservés.

En Release, le projet utilise une optimisation orientée vers la vitesse avec :

```text
optimize("Speed")
```

et active notamment :

```text
NDEBUG
```

---

## 4. Les trois pièges documentés

Le fichier présente trois situations particulières qui peuvent provoquer des erreurs si certaines lignes sont supprimées.

---

### Piège n°1 — Les dépendances NKGLSlang et NKSPIRVCross

Les modules :

```text
NKGLSlang
NKSPIRVCross
```

sont déclarés explicitement dans les dépendances du projet.

Cette déclaration est nécessaire parce que `NKSL` utilise directement des fonctionnalités fournies par **glslang** et **SPIRV-Cross**.

Une dépendance indirecte à travers `NKSL` ou `NKRHI` ne suffit pas pour que l'exécutable final récupère automatiquement ces bibliothèques lors de l'édition de liens.

---

###  Piège n°2 — Le chemin vers les en-têtes Vulkan

Le fichier ajoute explicitement le dossier contenant les en-têtes Vulkan.

Cette configuration est nécessaire car :

```text
NkVulkanDevice.h
```

utilise notamment :

```
#include <vulkan/vulkan.h>
```

Les en-têtes Vulkan utilisés par le projet sont fournis dans le dossier `Externals`.


---

###  Piège n°3 — La définition `NK_RHI_VK_ENABLED`

Le fichier définit explicitement :

```text
NK_RHI_VK_ENABLED
```

Cette définition est importante car elle permet à `NKRHI` d'utiliser l'implémentation Vulkan réelle.

Dans :

```text
NkVulkanDevice.h
```

la présence de cette définition détermine quelle version de `NkVulkanDevice` doit être utilisée.

Lorsque la définition est active, le programme dispose de la véritable classe Vulkan.

Sans cette définition, le fichier d'en-tête utilise à la place une **classe vide ou simplifiée**, dont certaines fonctions Vulkan ne sont pas disponibles.

---

## Conclusion

L'analyse du fichier `NKXRDemo.jenga` montre que le fichier de projet ne sert pas uniquement à indiquer les fichiers sources à compiler. Il décrit également les dépendances, les bibliothèques nécessaires, les définitions spécifiques et les adaptations nécessaires selon le système d'exploitation.

Les trois pièges étudiés montrent également qu'une erreur visible dans le code C++ peut parfois avoir son origine dans le fichier `.jenga`.

Les trois situations correspondent à trois étapes différentes :

1. **Préprocesseur** : les en-têtes Vulkan doivent être accessibles.
2. **Compilation** : `NK_RHI_VK_ENABLED` doit être défini pour utiliser la bonne implémentation Vulkan.
3. **Édition de liens** : les bibliothèques `NKGLSlang` et `NKSPIRVCross` doivent être explicitement disponibles.


