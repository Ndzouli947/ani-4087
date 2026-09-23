# Exercice 7 
## Énoncé

> Prenez la liste des vingt-trois dépendances de la démonstration du moteur et classez-la en trois groupes : celles dont le nom suffit à deviner le rôle, celles dont vous avez une idée sans certitude, celles dont vous ne savez rien. Pour ce troisième groupe, ouvrez l'en-tête principal de chaque module et rendez une phrase par module.

## Liste complète des dépendances (23)

```
NKXR, NKRenderer, NKRHI, NKSL, NKGLSlang, NKSPIRVCross, NKSerialization,
NKReflection, NKFileSystem, NKFont, NKImage, NKGlad, NKEvent, NKWindow,
NKMath, NKTime, NKLogger, NKStream, NKContainers, NKMemory, NKCore,
NKPlatform, NKThreading
```

---

## Groupe 1  Le nom suffit à deviner le rôle (14 modules)

| Module | Rôle deviné |
|---|---|
| NKCore | Types et fonctions de base du moteur |
| NKMath | Vecteurs, matrices, quaternions |
| NKWindow | Création et gestion de la fenêtre |
| NKTime | Horloge, delta-time, chronométrage |
| NKMemory | Gestion de la mémoire (allocateurs) |
| NKThreading | Multithreading |
| NKLogger | Journalisation (logs) |
| NKFileSystem | Accès aux fichiers et dossiers |
| NKImage | Chargement/traitement d'images |
| NKFont | Gestion des polices de texte |
| NKEvent | Gestion des événements (clavier, souris...) |
| NKContainers | Structures de données (listes, chaînes) |
| NKRHI | Interface bas niveau vers la carte graphique |
| NKXR | Réalité virtuelle/étendue |

## Groupe 2 Une idée sans certitude (4 modules)

| Module | Ce qu'on devine | Ce qui reste incertain |
|---|---|---|
| NKRenderer | Rendu graphique de haut niveau | Chevauchement possible avec NKRHI  où s'arrête l'un, où commence l'autre ? |
| NKSerialization | Sauvegarde/chargement de données structurées | Format exact (JSON, binaire, custom) ? |
| NKStream | Manipulation de flux de données | Flux réseau, fichier, audio, ou générique ? |
| NKPlatform | Couche d'abstraction du système d'exploitation | Que couvre-t-elle que NKWindow/NKFileSystem ne couvrent pas déjà ? |

### Groupe 3 aucune idée 

 |Module | En-tête | Phrase |
 |---|---|---|
 | NKRHI | ```Kernel/Runtime/NKRHI/src/NKRHI/NkRHI.h``` | C'est la couche d'abstraction de bas niveau du moteur vers l'API graphique: un en-tête qui regroupe la gestion du contexte, des périphériques |
 | NKSL | ``Kernel/Runtime/NKSL/src/NKSL/NKSL.h`` | C'est le compilateur de shaders propre au moteur, qui encapsule **glslang** pour convertir ses shaders vers différentes cibles |
 | NKSPIRVCross | ``Externals/Libs/NKSPIRVCross/src/spirv_cross/spirv_cross.hpp`` | C'est une enveloppe autour de **SPIRV-Cross** qui retraduit du bytecode SPIR-V vers d'autres langages de shaders.|
 |NKGLSlang | ``Externals/Libs/NKGLSlang/glslang/Public/ShaderLang.h`` | C'est une enveloppe autour de **glslang** qui compile du code **GLSL/HLSL** en bytecode **SPIR-V** |
 | NKGlad | ``Externals/Libs/NKGlad/include/glad/gl.h`` | C'est le chargeur de fonction **OpenGL** qui donne accès à l'nesemble des fonctions et constantes de l'API.|
