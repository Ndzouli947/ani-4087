# Exercice 7 : le pointeur caché


## Énoncé

 Cachez le curseur et confinez-le. Affichez à chaque image la position `x`, `y` et le `rawDelta`. Bougez la souris jusqu'à ce qu'elle atteigne le bord. Rendez les deux séries et dites laquelle continue de bouger, et pourquoi c'est celle-là qu'il faut.

---

## 1. Le code (`src/main.cpp`)

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEventSystem.h" 
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkEventDispatcher.h" // input
#include "NKTime/NkClock.h"
#include "NKTime/NkChrono.h"
#include "NKLogger/NkLog.h"

using namespace nkentseu;
 
int nkmain(const NkEntryState& state) {
    NkWindowConfig config;
    config.title  = "Fenêtre";
    config.width  = 1280;
    config.height = 720;
 
    NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }
 
    
    fenetre.ShowMouse(false);          // cacher le curseur
    fenetre.ClipMouseToClient(true);   // confiner le curseur à la zone client
 
    bool enMarche = true;
 
    auto gardeFermeture = NkEvents().AddEventCallbackGuard<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) { enMarche = false; });
 
    auto gardeEchap = NkEvents().AddEventCallbackGuard<NkKeyPressEvent>(
        [&](NkKeyPressEvent* e) {
            if (e->GetKey() == NkKey::NK_ESCAPE) { enMarche = false; }
        });
 
    int numero = 0;
    int dernierX = -1, dernierY = -1;
 
    while (enMarche) {
        NkEvents().PollEvents();
 
        
        const int x  = (int)NkInput.MouseX();
        const int y  = (int)NkInput.MouseY();
        const int rx = (int)NkInput.MouseRawDeltaX();
        const int ry = (int)NkInput.MouseRawDeltaY();
 
        ++numero;
 
        // Pour garder le terminal lisible : on n'écrit que si quelque chose a bougé.
        if (x != dernierX || y != dernierY || rx != 0 || ry != 0) {
            std::printf("image %d : x=%d y=%d  rawDelta=(%d, %d)\n", numero, x, y, rx, ry);
            std::fflush(stdout);
            dernierX = x;
            dernierY = y;
        }
 
        Sleep(16)
    }
 
    // IMPORTANT : rendre le curseur au système. Le confinement peut survivre
    // au programme s'il n'est pas relâché
    fenetre.ClipMouseToClient(false);
    fenetre.ShowMouse(true);
 
    return 0;
}
```


### Ce que fait le programme

1. Il ouvre la fenêtre, **cache** le curseur (`ShowMouse(false)`) et le **confine** à la zone cliente (`ClipMouseToClient(true)`).
2. À chaque tour de boucle (environ 60 par seconde), après avoir traité les événements, il lit :
   - la **position** du pointeur : `NkInput.MouseX()` et `NkInput.MouseY()` ;
   - le **déplacement brut** : `NkInput.MouseRawDeltaX()` et `MouseRawDeltaY()`.
3. Il affiche une ligne quand la position ou le déplacement brut n'est pas nul. Cela garde le terminal lisible : ce n'est donc pas une ligne par image dans tous les cas, mais les numéros d'image montrent ce qui a été omis.
4. À la sortie (Échap ou fermeture), il relâche le confinement et réaffiche le curseur : le confinement peut survivre au programme s'il n'est pas relâché.

---

## 2. Les deux séries

La sortie contient les deux séries dans les mêmes lignes : la colonne `x=… y=…` est la **position**, la colonne `rawDelta=(…, …)` est le **déplacement brut**. Voici le passage où le pointeur arrive au bord droit de la fenêtre et continue d'être poussé :

| Image | Position `x` | Position `y` | `rawDelta` (x, y) |
|------:|-------------:|-------------:|-------------------|
| 527 | 1255 | 211 | (3, 0) |
| 528 | 1260 | 211 | (2, 0) |
| 529 | 1265 | 211 | (2, 0) |
| 530 | 1273 | 211 | (2, 0) |
| 531 | **1277** | 211 | (2, 0) |
| 532 | **1277** | 211 | (3, 0) |
| 533 | **1277** | 211 | (3, 0) |
| 534 | **1277** | 211 | (2, 0) |
| 535 | **1277** | 211 | (2, 0) |
| 536 | **1277** | 209 | (3, −1) |
| 537 | **1277** | 206 | (6, −1) |
| 538 | **1277** | 205 | (5, −1) |
| 539 | **1277** | 204 | (4, 0) |
| 540 | **1277** | 203 | (4, 0) |

La poussée contre le bord droit se poursuit jusqu'à l'image 585 : `x` reste à 1277, alors que le déplacement brut en x reste positif (de 2 à 8).

**Le même phénomène sur le bord haut** (images 93 à 101) : la position `y` reste à **0**, alors que le déplacement brut vertical reste négatif.

| Image | Position `x` | Position `y` | `rawDelta` (x, y) |
|------:|-------------:|-------------:|-------------------|
| 92 | 847 | 2 | (2, −8) |
| 93 | 853 | **0** | (1, −5) |
| 94 | 856 | **0** | (2, −3) |
| 95 | 862 | **0** | (3, −3) |
| 96 | 876 | **0** | (5, −5) |
| 97 | 891 | **0** | (4, −5) |
| 98 | 911 | **0** | (2, −4) |
| 99 | 937 | **0** | (3, −3) |
| 100 | 954 | **0** | (2, −1) |
| 101 | 982 | **0** | (5, −1) |

---

## 3. Laquelle continue de bouger, et pourquoi c'est celle-là qu'il faut

**Le déplacement brut continue de bouger ; la position s'arrête.**

Au bord droit, la position `x` se fige à 1277 pendant plus de cinquante images (531 à 585), alors que `rawDelta` continue de donner des valeurs entre 2 et 8 : la main avance toujours, mais le pointeur ne peut plus. Au bord haut, `y` reste à 0 tant que le déplacement vertical brut reste négatif.

**Pourquoi c'est le déplacement brut qu'il faut pour une tête.**

1. **La position est bornée.** Le curseur est confiné à la fenêtre : sa position ne peut pas dépasser les limites de la zone cliente. Une fois au bord, elle cesse de renseigner sur la main, alors que la main continue. Si l'on faisait tourner une caméra avec la position, elle s'arrêterait de tourner dès que le pointeur touche le bord, au milieu d'un mouvement.
2. **Le déplacement brut mesure la main, pas l'écran.** Il rend le mouvement physique de la souris depuis la dernière lecture, sans dépendre de l'endroit où se trouve le pointeur. On peut donc tourner indéfiniment, comme dans un jeu à la première personne.
3. **Le déplacement brut est sans accélération.** Le chapitre explique que le déplacement « normal » subit l'accélération que Windows applique pour le confort du bureau : la tête tournerait plus vite quand on bouge vite, ce que l'oreille interne ne pardonne pas. Le déplacement brut évite cet effet.
4. **Le curseur est caché.** La position du pointeur n'a plus de sens visuel : le joueur ne la voit pas, il ne voit que la direction de la tête.

---

## 4. Une observation en plus : `rawDelta` ne retombe pas à zéro

En lisant la sortie, j'ai remarqué que `rawDelta` ne revient **pas** à `(0, 0)` quand la souris est immobile :

- Des images **234 à 462** (229 images consécutives), la position reste figée à `x=982 y=196` : la souris est donc immobile. Pourtant, `rawDelta` reste à `(-2, 0)` pendant toute cette période, jusqu'à ce que je bouge de nouveau (image 463).
- Dans les images 586 à 661 (76 images), `rawDelta` reste à `(1, 0)` pendant que la position ne change plus. Comme le pointeur est collé au bord, je ne peux pas l'affirmer avec la même certitude, mais le schéma ressemble au précédent.

---

## 5. Ce que j'en retiens

- Une position bornée ne dit plus rien du mouvement une fois au bord ; un déplacement brut, si.
- Pour une caméra, on lit le **déplacement brut**, pas la position : il est sans limite et sans accélération.
- Il faut tout de même se méfier d'une valeur lue telle quelle : ici, `rawDelta` reste figé sur sa dernière valeur quand la souris s'arrête, d'où la nécessité d'accumuler et de consommer une fois par image.
- Il faut relâcher le confinement et réafficher le curseur à la fermeture du programme.