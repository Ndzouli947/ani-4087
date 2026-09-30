### Exercie 1: La fenêtre nue
---

# énoncé:
---
crivez le programme de quinze lignes de ce chapitre, construisez-le avec Jenga, et lancez-le.

Rendez le fichier et une capture de la fenêtre. Dites combien de temps cela vous a pris, honnêtement : ce nombre vous servira de référence pour mesurer vos progrès. .jenga

# Solution
---
Pour la réalisation de cet exercice, j'ai crée un projet avec Jenga en utilisant Kit. Les modules ont été utilisé pour créer la fenêtre et gérer ls événements 
 
Ce que fait le programme: 
Le programme crée une fenêtre "Fenêtre" avec les dimensions suivantes: **1200 pixels pour la largeur** et **720 pixels de hauteur** , le programme vérifi si la fenêtre apparait ou est valide.

---
### Programme main.cpp :
```
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEventSystem.h" 

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig config;
    config.title = "Fenêtre";
    config.width = 1200;
    config.height = 720;

    NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    while (fenetre.IsOpen()) {
        NkEvents().PollEvents();     
    }

    return 0;
}
```

### Fenetre.jenga:


```
#!/usr/bin/env python3

from Jenga import *

with workspace("Fenetre"):
    useconfig("C:/Users/PC/Documents/Nkentseu/Kit/Kit.jenga")
    configurations(['Debug', 'Release'])
    targetoses([TargetOS.WINDOWS])
    targetarchs([TargetArch.X86_64])

    with project("Fenetre"):
        consoleapp()
        language("C++")
        cppdialect("C++20")
        location("Fenetre")
        files(["src/**.cpp", "include/**.hpp"])
        usekit(["NKWindow", "NKEvent"])
```

J'ai construis ce programme avec la commande`` jenga``  build qui crée ensuite un exécutable ``Build\Bin\Debug-Windows\Fenetre\Fenetre.exe``

La compilation étant terminée (réussie) j'ai lancé le programme pour vérifier que la fenêtre s'affiche bien.

### Temps de réalisation

Le temps de codage est d'envirion **25 minutes** temps mésuré avec un téléphone car il a fallu que je corrige certaines erreurs qui s'affichaient dans le terminal suite à des erreurs commises par moi, mais résolu.
