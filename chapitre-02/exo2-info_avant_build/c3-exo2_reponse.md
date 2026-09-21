### Sortie fournie par la commande jenga info :
```
=========================== Jenga Workspace: MaSalle ===========================

Location: C:\Users\PC\Documents\ani-4087\chapitre-02\exo1-le_projet_minimal
Entry file: C:\Users\PC\Documents\ani-4087\chapitre-02\exo1-le_projet_minimal\MaSalle.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows, Android
Target Architectures: x86_64, arm64


Projects
------------------------------------------------------------
Name      Kind          Language   Test   External
==================================================
MaSalle   WindowedApp   C++        No     No


Available Toolchains
------------------------------------------------------------
Name       Family   Target OS   Arch     Env  
==============================================
host-gcc   gcc      Windows     x86_64   mingw
mingw      gcc      Windows     x86_64   mingw


Daemon
------------------------------------------------------------
Status: Not running

```
### Ce que jenga info apprends en plus, non écrit dans le fichier:

- Le chemin réel de reconstruction: location(".") est resolu en C:\Users\PC\Documents\ani-4087\chapitre-02\exo1-le_projet_minimal l'endroit exact où jenga va chercher les sources et écrites les sorties

- Les cibles par défaut non déclarées: rien dans le fichier ne mentionne de plateforme ou d'OS cible, et pourtant  Target OSes: Windows, Android et deux architectures (x86_64, arm64) apparaissent déjà. ce sont des valeurs par défaut du workspace, pas quelque chose pas quelque chose qu'on a écrit à la main.

-Le point cental, dans Available Toolchains, seules host-gcc et mingw figurent, toutes deux dans  Target OS: Windows, mais aucune toolchain Android n'apparait alors que  qu'android est listé comme cible théorique ( et cela est du au faite que l'installtion du NDK n'a pas encore été fait) conformement au coours qui dit si aucune ligne ne dit anfroid rein de ce qui suit ne fonctionnera, cela signifie qu'un déploiement Android echouerait sur cette machine indépendamment de la qualité du fichier .jenga

-Le demon:(Daemon: Not running) c'est un mécanisme d'accélération des builds incrémentaux, absents du fichier de projet

Le fichier d eprojet décrit une intention, jenga info décrit l'état réel de la machine à cet instant. L'écart le plus significatif reste le même qu'avant, mais cette la localisation elle-même confirme que le dépôt est correct.
