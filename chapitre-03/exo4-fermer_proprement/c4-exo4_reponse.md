# Exercice 4 : 
---

## Énoncé

> Ajoutez un rappel sur `NkWindowCloseEvent` qui met un booléen à faux, et faites porter la boucle sur ce booléen plutôt que sur `IsOpen()`. Ajoutez ensuite un rappel sur `NkKeyPressEvent` qui fait la même chose sur la touche Échap. Rendez le code et expliquez pourquoi les deux chemins de sortie doivent aboutir au même endroit.

---

## 1. Le code (`src/main.cpp`)

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEventSystem.h"   
#include "NKEvent/NkKeyboardEvent.h"

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

    // Le booléen est déclaré AVANT les gardes : les variables locales sont
    // détruites dans l'ordre inverse, donc les gardes (qui retirent les rappels)
    // disparaissent avant le booléen que les rappels utilisent.
    bool enMarche = true;

    // Chemin 1 : l'utilisateur ferme la fenêtre (croix, Alt+F4).
    auto gardeFermeture = NkEvents().AddEventCallbackGuard<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) {
            enMarche = false;
        });

    // Chemin 2 : l'utilisateur appuie sur Échap.
    auto gardeEchap = NkEvents().AddEventCallbackGuard<NkKeyPressEvent>(
        [&](NkKeyPressEvent* e) {
            if (e->GetKey() == NkKey::NK_ESCAPE) {
                enMarche = false;
            }
        });

    while (enMarche) {
        NkEvents().PollEvents();
    }

    return 0;
}
```


### Ce que fait le programme

1. Il ouvre la fenêtre et vérifie sa validité.
2. Il déclare **un seul booléen**, `enMarche`, qui vaut `true` tant que le programme doit continuer.
3. Il pose deux rappels typés : l'un écoute `NkWindowCloseEvent`, l'autre `NkKeyPressEvent` filtré sur Échap. Chacun met `enMarche` à `false`.
4. La boucle ne dépend plus de `IsOpen()` mais de `enMarche`, et continue de pomper les événements à chaque tour.

### Deux détails du code

- **`AddEventCallbackGuard` et non `AddEventCallback`.** Ma première version utilisait `AddEventCallback`, qui retourne `void` : le compilateur a refusé (`variable has incomplete type 'void'`). `AddEventCallbackGuard` retourne un garde qu'on range dans une variable, et qui retire le rappel quand il est détruit.
- **`enMarche` est déclaré avant les gardes.** Les variables locales sont détruites dans l'ordre inverse de leur déclaration : les gardes retirent donc leurs rappels avant que le booléen disparaisse. Les rappels capturent `enMarche` par référence, et un événement tardif ne doit jamais écrire dans une variable détruite.

---

## 2. Observations

| Action de l'utilisateur | Résultat |
|-------------------------|----------|
| Appui sur Échap | La fenêtre se ferme et le programme se termine |
| Clic sur la croix | La fenêtre se ferme et le programme se termine également |

---

## 3. Pourquoi les deux chemins de sortie doivent aboutir au même endroit

Les deux rappels ne font qu'une chose : mettre `enMarche` à `false`. La sortie de la boucle, et tout ce qui suit, n'existe qu'une seule fois.

**1. Une seule décision de sortie.**
La boucle ne regarde qu'une variable. Il n'y a qu'une manière de la quitter, donc pas deux logiques qui pourraient se contredire. Si Échap faisait un `return` direct et que la croix passait par la boucle, le programme aurait deux sorties, à tester et à maintenir séparément.

**2. Une seule séquence d'arrêt.**
Tout ce qui doit arriver à la fermeture se trouve après la boucle : retirer les rappels (les gardes), détruire la fenêtre, rendre le code de retour. Un chemin de sortie qui court-circuite ce passage saute ce nettoyage, ou oblige à le recopier ailleurs. Une copie finit toujours par oublier une étape ajoutée plus tard dans l'autre.

**3. Un comportement identique pour l'utilisateur.**
Quelle que soit la façon de quitter, le programme termine dans le même état. Si l'on veut plus tard demander une confirmation, sauvegarder ou afficher un message, on le fait à un seul endroit, et les deux chemins en profitent d'un coup.

**4. Le matériel n'apparaît pas dans le code qui décide.**
C'est le principe du chapitre sur les actions : plusieurs commandes (une touche, un bouton de manette) visent la même action, et le code de la règle ne change pas d'une ligne. Ici, deux événements (fermeture, Échap) visent la même décision « arrêter », et la boucle ne connaît ni l'un ni l'autre. Ajouter une troisième sortie, par exemple un bouton de manette, revient à poser un rappel de plus qui met `enMarche` à `false`, sans toucher à la boucle.

**5. Échap est un événement, pas un état.**
Le chapitre distingue l'état (« la touche est-elle enfoncée maintenant ? ») de l'événement (« la touche vient-elle d'être enfoncée ? »). Quitter est une chose qui **arrive** une fois, donc un événement convient. Mettre `enMarche` à `false` plusieurs fois, si la touche produit des répétitions, est sans conséquence : l'opération ne change rien après la première fois.

### Une conséquence à connaître

Avec `IsOpen()`, la boucle suivait l'état réel de la fenêtre. Avec `enMarche`, elle ne suit que ce que les rappels lui disent. Si le système fermait la fenêtre par un chemin qui ne produit pas `NkWindowCloseEvent`, la boucle continuerait de tourner sans fenêtre. C'est une raison de plus de n'avoir qu'un seul point de décision : c'est là qu'il faut regarder en cas de problème.

---
