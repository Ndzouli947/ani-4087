# Exercice 9 

## énoncé:

Ajoutez à files un motif qui ne correspond à aucun fichier, et à includedirs un dossier qui n'existe pas.

Rendez ce que jenga info en dit, et ce que jenga build en dit. Comparez les deux : lequel vous aurait fait gagner du temps ?

## Code uttilisé:
```
 with project("MaSalle"):
        windowedapp()
        language("C++")
        cppdialect("C++17")
        location(".")
        includedirs(["include"])

        # ajout du motif ne correspondant à aucun fichier
        files(["src/main.cpp", "src/modules/**.cpp"])
        
        # ajout du include non présent sur le disque
        includedirs(["include_non_présent"])
```

Ce projet n'a qu'un fichier source ``src/main.cpp`` qu'on ajouté deux chemins qui ne désignent rien.

## Ce que ``jenga info`` dit 

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
Name          Family        Target OS   Arch     Env    
========================================================
host-gcc      gcc           Windows     x86_64   mingw
mingw         gcc           Windows     x86_64   mingw
android-ndk   android-ndk   Android     arm64    android


Daemon
------------------------------------------------------------
Status: Not running
``` 

Il décrit l'espace de travail, dit les projets et dit quelles sont les chînes disponibles, mais cette commande n'affiche pas pas de fichiers, pas de motifs ``files`` pas de liste et pas de dossier d'inclusion donc ça ne peut rien nous signaler.


## Ce que ``jenga build`` dit 

```
Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     mingw

Build Order (1 projects):
  1. MaSalle [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MaSalle       Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\MaSalle\MaSalle.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful              Time: 4.15s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED            
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           4.15s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```

Après avoir taper la commande ``jenga build`` aucune erreur, pas d'avertissement, le motif est ignoré silencieusement avce le dossier absent(jenga et le compilateur ne le signale pas)

## Comparaison des sorties de ``jenga info `` et ``jenga build``

``jenha info `` permet d'afficher le nom du projet, le langage utilisé etc...
ainsi que les outils disponible 
``jenga build`` quant à lui permet d'afficher les informations liées à ``files ``( le nombres de sources).

La commande qui m'aurez fait gagner en temps c'est ``jenga build`` car c'est la seule des deux commandes qui affiches les i,formations liées à ``files`` alors que ``jenga info`` ne m'aurait appris car il ne montre aucun chemin. 