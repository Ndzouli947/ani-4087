## Énoncé

> Écrivez un filtre dont la condition est fausse sur votre machine, avec une définition à l'intérieur, et prouvez qu'elle n'est pas appliquée. Puis rendez la condition vraie et prouvez qu'elle l'est.

## 1. Code utilisé

### `include/filtre.hpp`

```cpp
#ifndef FILTRE_HPP
#define FILTRE_HPP

#if defined(_WIN32)
    #define PLATEFORME_ACTIVEE
#endif

#endif
```

(Premier test effectué avec `#if defined(__linux__)` — condition fausse sur ma machine, qui est sous Windows.)

### `src/main.cpp`

```cpp
#include <iostream>
#include "filtre.hpp"

int main() {
#ifdef PLATEFORME_ACTIVEE
    std::cout << "Definition appliquee : Oui" << std::endl;
#else
    std::cout << "Definition appliquee : Non" << std::endl;
#endif
    return 0;
}
```

## 2. Pourquoi ne pas utiliser `jenga info` ou `jenga build --verbose`

Ces deux commandes ont été testées et se sont révélées inutiles pour ce diagnostic : leur sortie est  identique,  que la condition du filtre soit vraie ou fausse. Aucune des deux n'affiche l'état des définitions de préprocesseur. Il a donc fallu faire porter la preuve par le **programme compilé lui-même**, via un affichage `std::cout` conditionné par un `#ifdef`.

## 3. Résultats obtenus

| Condition testée | Macro évaluée | Résultat (vrai/faux) | Sortie du programme exécuté |
|---|---|---|---|
| `#if defined(__linux__)` | fausse sous Windows | **Faux** | `Definition appliquee : Non` |
| `#if defined(_WIN32)` | vraie sous Windows | **Vrai** | `Definition appliquee : Oui` |

## 4. Étapes de la chaîne de construction concernées

Toute cette démonstration se joue **avant même la compilation**, à l'étape du **préprocesseur** :
- Quand la condition est fausse, la ligne `#define PLATEFORME_ACTIVEE` n'est jamais lue ni transmise au compilateur  c'est comme si elle n'avait jamais existé 
- Quand la condition est vraie, la macro est définie et devient visible du reste du fichier, y compris dans `main.cpp` via l'inclusion du header.

## 5. Enseignements de l'exercice

**Les outils de build ne renseignent pas toujours sur l'état des définitions du préprocesseur.** `jenga info` et `jenga build --verbose` ne montrent aucune différence entre les deux cas il faut donc que le programme prouve lui-même, à l'exécution, ce qu'il a reçu à la compilation.
