# Exercice 6 : état contre événement


## Énoncé

 Écrivez deux compteurs. Le premier s'incrémente à chaque image où la touche Espace est tenue, lu par `NkInput.IsKeyDown`. Le second s'incrémente à chaque `NkKeyPressEvent` sur Espace. Appuyez une seconde, relâchez. Rendez les deux nombres et expliquez l'écart.

---

## 1. Le code (`src/main.cpp`)

```cpp
#include <chrono>
#include <cstdio>
#include <thread>

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

    bool enMarche = true;
    int  compteurEtat      = 0;   // images où Espace est tenue (lu par l'état)
    int  compteurEvenement = 0;   // NkKeyPressEvent reçus sur Espace

    auto gardeFermeture = NkEvents().AddEventCallbackGuard<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) { enMarche = false; });

    // Échap quitte ; Espace est compté. Aucun filtre sur la répétition :
    // on compte tous les NkKeyPressEvent reçus.

    auto gardeTouches = NkEvents().AddEventCallbackGuard<NkKeyPressEvent>(
        [&](NkKeyPressEvent* e) {
            if (e->GetKey() == NkKey::NK_ESCAPE) { enMarche = false; }
            if (e->GetKey() == NkKey::NK_SPACE)  { ++compteurEvenement; }
        });

    while (enMarche) {
        NkEvents().PollEvents();

        // État : on lit APRÈS avoir pompé les événements, pour avoir le présent.
        if (NkInput.IsKeyDown(NkKey::NK_SPACE)) {
            ++compteurEtat;
        }

        // Une "image" = un tour de boucle. Sans cette pause, la boucle tourne
        // des milliers de fois par seconde et le compteur d'état explose.
        // ~60 images par seconde, pour que les nombres restent lisibles.
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    std::printf("Compteur d'etat      (IsKeyDown)      : %d\n", compteurEtat);
    std::printf("Compteur d'evenement (NkKeyPressEvent) : %d\n", compteurEvenement);
    return 0;
}
```

> Remplacer par le code exact qui compile chez moi si un détail diffère.

### Choix de conception

- **Une « image » est un tour de boucle.** Sans pause, la boucle tourne des milliers de fois par seconde. J'ai ajouté une pause de 16 ms pour approcher une cadence de soixante images par seconde. La cadence réelle dépend de la précision du minuteur de Windows : elle est proche de cette valeur, sans l'égaler exactement.
- **L'état est lu après `PollEvents`**, pour que `IsKeyDown` reflète l'instant présent.
- **Aucun filtre sur la répétition** : le second compteur reçoit tous les `NkKeyPressEvent` sur Espace, sans tester `IsRepeat()`.
- **Les deux modèles du moteur.** D'après le wiki de NKEvent (`Events.md`), `NkInput` est une façade de *polling* (`NkInputQuery`, modèle « pull ») qui lit l'état agrégé du système, alors que les rappels typés reposent sur le modèle « push » (`NkEventDispatcher`). Les deux compteurs utilisent donc les deux modèles.

---

## 2. Les nombres obtenus

Procédure : cliquer sur la fenêtre pour lui donner le focus, appuyer sur Espace, maintenir environ une seconde, relâcher, puis appuyer sur Échap pour afficher les compteurs.

### Essais avec une durée d'appui maîtrisée

| Essai | Appui | Compteur d'état (`IsKeyDown`) | Compteur d'événements (`NkKeyPressEvent`) |
|-------|-------|------------------------------:|------------------------------------------:|
| 1 | Appui bref | 12 | 1 |
| 2 | Appui d'environ une seconde | 62 | 1 |

### Premiers essais, sans chronomètre

| Essai | Compteur d'état (`IsKeyDown`) | Compteur d'événements (`NkKeyPressEvent`) |
|-------|------------------------------:|------------------------------------------:|
| A | 75 | 1 |
| B | 94 | 1 |
| C | 207 | 1 |

**Remarques sur les mesures :**

- **Le compteur d'état suit la durée de l'appui.** 12 pour un appui bref, 62 pour environ une seconde. Le second chiffre correspond à une cadence proche de soixante images par seconde, ce qui est cohérent avec la pause de 16 ms du programme (la cadence réelle n'est pas parfaitement exacte sous Windows, donc « proche » et non « égale »).
- **Les premiers essais variaient** (de 75 à 207) parce que la durée de chaque appui n'avait pas été contrôlée. Ils montrent la même proportionnalité avec des appuis plus longs.
- **Le compteur d'événements vaut 1 dans les cinq essais**, quelle que soit la durée de l'appui.

---

## 3. Explication de l'écart

**Les deux compteurs ne mesurent pas la même chose.**

- **L'état** est une photographie du présent. À chaque image, `NkInput.IsKeyDown(NkKey::NK_SPACE)` répond à la question « la touche est-elle enfoncée à cet instant ? ». Tant que je maintiens Espace, la réponse est oui à chaque image, et le compteur monte d'une unité par image. Il est donc **proportionnel à la durée de l'appui** : à environ soixante images par seconde, une seconde d'appui donne de l'ordre de soixante comptes. Mes valeurs vont dans ce sens : 12 pour un appui bref, 62 pour un appui d'environ une seconde. Les premiers essais non chronométrés (75, 94 et 207) correspondent à des appuis plus longs.
- **L'événement** est le récit de ce qui s'est passé. `NkKeyPressEvent` signale que la touche **vient d'être enfoncée**. Il arrive une fois à l'instant de l'appui, puis plus rien tant que je maintiens la touche. Il est donc **indépendant de la durée de l'appui** : un appui, un événement, d'où 1 dans les trois essais.

**Une précision sur la répétition.**

Windows envoie des répétitions quand une touche est maintenue, et je m'attendais donc à plus d'un événement. Le code de NKEvent montre que le moteur y a pensé : `NkKeyPressEvent` porte un drapeau `IsRepeat()`, vrai quand l'événement vient de la répétition automatique du système (`NkEvent.h`, membre `mIsRepeat`, commenté « true si auto-repeat OS »). Un événement de répétition aurait donc dû pouvoir arriver dans mon rappel avec `IsRepeat()` à `true`, et mon compteur, qui ne filtre rien, l'aurait compté. Il est pourtant resté à 1 : **les répétitions n'ont pas atteint mon rappel**.

Je n'ai pas trouvé pourquoi. Le test `!event.IsRepeat()` que j'avais repéré (ligne 925 de `NkEvent.h`) se trouve dans un exemple de documentation en commentaire, « Filtrage avancé » : il montre comment un utilisateur ignore les répétitions dans **son propre** gestionnaire. Ce n'est donc pas du code du moteur et il n'explique pas l'absence de répétitions. Il confirme au contraire que le moteur est censé les livrer aux gestionnaires, qui doivent alors les filtrer eux-mêmes.

La cause reste donc à trouver. Pour trancher, il faudrait compter séparément les événements dont `IsRepeat()` vaut `true` et ceux dont il vaut `false`, ou chercher dans le code du backend Windows comment les répétitions sont transmises.
---

## 4. Ce que j'en retiens

- Un compteur d'état croît avec la durée de l'appui ; un compteur d'événements croît avec le nombre d'appuis.
- Le choix entre les deux dépend de la nature de l'action : ce qui dure ou ce qui arrive.
- Un `NkKeyPressEvent` porte `IsRepeat()` pour distinguer le vrai appui de la répétition automatique du système : un code qui doit réagir une seule fois à un appui (tirer, sauter) doit tester ce drapeau.
