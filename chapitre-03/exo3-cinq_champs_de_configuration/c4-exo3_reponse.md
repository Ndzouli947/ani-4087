# exercice 3 
---

## Énoncé
Modifiez cinq champs de ``NkWindowConfig`` que le chapitre n'a pas montrés, choisis dans ``NkWindowConfig.h.``

Pour chacun, rendez la ligne, ce que vous attendiez, et ce que vous avez observé. Un champ qui n'a rien changé est une réponse valable, à condition de dire pourquoi vous le pensez.
---
## Méthode
Le chapitre n'utilise que ``title``, ``widht`` et ``height``. J'ai choisi cinq champs de dubriques **Position et taille**, **comportement** et **apparence** de ``NkWindowConfig.h``, dont l'effet se voit directement sous Windows.

Pour chaque test:

1. je modifie un seul champ dans main.cpp, avant la ligne NkWindow fenetre(config); (la configuration est lue à ce moment) ;
2. je reconstruis avec jenga build --config Debug et je lance le programme ;
3. j'observe la fenêtre et le terminal ;
4. je remets le champ en commentaire avant de tester le suivant.

La boucle ``while (fenetre.IsOpen()) { NkEvents().PollEvents(); }`` reste active pendant les tests, sinon la fenêtre serait bloquée.
---
### Résultats obtenus après les tests



| # | Champ | Valeur testée | Effet observé |
|---|-------|---------------|---------------|
| 1 | `centered`, `x`, `y` | `false`, `0`, `0` | Agit : fenêtre en haut à gauche |
| 2 | `resizable` | `false` | Agit : bouton agrandir désactivé |
| 3 | `opacity` | `0.5f` | Agit : fenêtre translucide |
| 4 | `alwaysOnTop` | `true` | À compléter (voir plus bas) |
| 5 | `minWidth`, `minHeight` | `600`, `400` | Agit : arrêt vers 600 × 400 |

---

## Champ 1 : `centered`, `x` et `y`

**Ligne testée :**

```
config.centered = false;
config.x = 0;
config.y = 0;
```

**Attendu :** `centered` vaut `true` par défaut. En le passant à `false`, la position `x`, `y` (coin haut-gauche de la fenêtre, cadre compris) doit être prise en compte, et la fenêtre ne doit plus apparaître au centre.

**Observé :** la fenêtre apparaît dans le coin supérieur gauche de l'écran.

Au premier essai, avec `x = 300` et `y = 200`, la fenêtre apparaissait pourtant toujours au centre. Je n'ai pas identifié avec certitude la cause : le programme a peut-être été lancé sans reconstruction, ou ces valeurs donnaient une position proche du centre sur mon écran.

**Conclusion :** le champ est tenu sous Windows. `centered` doit être mis à `false` pour que `x` et `y` s'appliquent.

---

## Champ 2 : `resizable`

**Ligne testée :**

```
config.resizable = false;
```

**Attendu :** la fenêtre ne peut plus être redimensionnée par l'utilisateur.

**Observé :** le bouton « agrandir » de la barre de titre est grisé, et cliquer dessus n'a aucun effet sur la fenêtre.

**Conclusion :** le champ agit sous Windows, au moins pour le bouton agrandir. Je n'ai pas testé le redimensionnement par les bords ni le double-clic sur la barre de titre, donc je ne peux pas affirmer que tous les moyens de redimensionner sont bloqués.

---

## Champ 3 : `opacity`

**Ligne testée :**

```
config.opacity = 0.5f;
```

**Attendu :** l'opacité globale va de 0 à 1, avec 1 = opaque (valeur par défaut). À `0.5f`, la fenêtre doit être à moitié transparente.

**Observé :** la fenêtre devient transparente, on voit ce qu'il y a derrière.

**Conclusion :** le champ est tenu sous Windows.

---

## Champ 4 : `alwaysOnTop`

**Ligne testée :**

```
config.alwaysOnTop = true;
```

**Attendu :** la fenêtre reste au-dessus des autres fenêtres, même quand je clique sur une autre application.

**Observé :** en cliquant sur une autre application, la fenêtre reste au centre de l'écran.

**Conclusion :** à compléter. L'observation actuelle décrit la position de la fenêtre et non son ordre d'affichage, donc elle ne permet pas de conclure. Test à refaire : cliquer sur une application qui recouvre la fenêtre et regarder si elle reste visible par-dessus, puis comparer avec `alwaysOnTop = false`.

---

## Champ 5 : `minWidth` et `minHeight`

**Ligne testée :**

```
config.minWidth  = 600;
config.minHeight = 400;
```

**Attendu :** la taille minimale vaut 160 × 90 par défaut. Avec ces valeurs, la fenêtre doit s'arrêter à 600 × 400 pixels (zone cliente) quand on la réduit à la souris.

**Observé :** en tirant le coin de la fenêtre vers l'intérieur, elle s'arrête. La zone noire mesure environ 600 × 400 pixels sur la capture (mesure estimée sur l'image). La fenêtre peut en revanche être agrandie librement avec la souris.


**Conclusion :** le champ est tenu sous Windows. `minWidth` et `minHeight` limitent la réduction, pas l'agrandissement. Comparaison à faire sans ces deux lignes : la fenêtre doit pouvoir descendre bien en dessous de 600 × 400.

---

## Ce que j'en retiens

- Les champs de la structure ne sont pas tous garantis sur toutes les plateformes : `NkWindowConfig.h` indique qu'un réglage non honoré produit un refus nommé dans le journal.
- Un champ peut en conditionner un autre : `x` et `y` n'ont d'effet que si `centered` vaut `false`.
- Il faut tester un champ à la fois et reconstruire à chaque fois, sinon on risque de juger un ancien exécutable.