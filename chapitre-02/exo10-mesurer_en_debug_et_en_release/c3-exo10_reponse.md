# Exercice 9  Mesure des performances en Debug et Release

##  Objectif

L'objectif de cet exercice est de mesurer le temps d'exécution d'un calcul lourd dans deux configurations de compilation différentes :

* **Debug**
* **Release**  

Cette expérience permet de comparer les performances obtenues dans ces deux configurations et de déterminer si le calcul respecte le budget temporel disponible pour produire une image dans le contexte de la réalité virtuelle.

Le budget considéré est de **11 millisecondes par image**.

---

##  Principe

Un programme C++ effectue un calcul numérique lourd à l'aide d'une boucle.

Pour chaque valeur de `i`, le programme calcule la racine carrée de `i` et ajoute le résultat à une variable.

Le nombre d'itérations utilisé pour l'expérience est :

```text
N = 1 000 000
```

Le temps d'exécution est mesuré avec `std::chrono`.

Le même programme est compilé puis exécuté successivement dans les configurations **Debug** et **Release**.

---

##  Résultats obtenus

Les résultats obtenus sont les suivants :

| Configuration | Résultat du calcul | Temps d'exécution |
| ------------- | -----------------: | ----------------: |
| Debug         |       6.66667e+008 |         **51 ms** |
| Release       |       6.66667e+008 |         **53 ms** |
| Budget VR     |                  — |         **11 ms** |

Le résultat du calcul est identique dans les deux configurations :

```text
6.66667e+008
```

Cela indique que le changement de configuration de compilation n'a pas modifié le résultat numérique du programme.

---



##  Comparaison entre Debug et Release

Les mesures obtenues sont :

```text
Debug   : 51 ms
Release : 53 ms
```

La différence entre les deux mesures est :

$$
53 - 51 = 2\ ms
$$

Dans cette expérience particulière, Release est donc mesuré comme étant **2 ms plus lent** que Debug.

Ce résultat ne signifie pas que Release est généralement moins performant que Debug. Une mesure unique peut être influencée par les conditions d'exécution de la machine, comme la charge du processeur, les processus exécutés en arrière-plan ou d'autres facteurs.

Pour obtenir une comparaison plus fiable, il serait préférable d'effectuer plusieurs exécutions dans chaque configuration et de calculer une moyenne.

---

##  Comparaison avec le budget de 11 ms

Le budget d'une image étant de **11 ms**, on obtient :

```text
Debug   : 51 ms > 11 ms
Release : 53 ms > 11 ms
```

Les deux configurations dépassent donc largement le budget disponible.

En rapport avec le budget :

$$
\frac{51}{11} \approx 4,64
$$

Le temps Debug représente environ **4,6 fois** le budget disponible.

Pour Release :

$$
\frac{53}{11} \approx 4,82
$$

Le temps Release représente environ **4,8 fois** le budget disponible.

Le calcul est donc trop lourd pour être exécuté dans un budget de 11 ms tel quel.

---

## Quelle mesure aurait pu conduire à une mauvaise décision ?

La mesure en **Debug** pourrait conduire à une mauvaise décision si elle était utilisée seule pour évaluer les performances finales du programme.

La configuration Debug est principalement destinée au développement et au débogage. Elle n'est donc pas la configuration de référence pour mesurer les performances finales d'une application.

Dans notre expérience, les deux configurations dépassent néanmoins le budget de 11 ms :

* Debug : **51 ms**
* Release : **53 ms**

La conclusion concernant ce calcul particulier est donc la même dans les deux cas : il dépasse le budget.

L'exercice montre surtout qu'il faut effectuer les mesures de performance dans une configuration appropriée, notamment **Release**, et qu'il est préférable de répéter les mesures afin d'obtenir des résultats plus représentatifs.

---

##  Conclusion générale

Cet exercice nous a permis de mesurer le temps d'exécution d'un calcul lourd dans les configurations Debug et Release.

Avec :

```text
N = 1 000 000
```

les résultats obtenus sont :

```text
Debug   : 51 ms
Release : 53 ms
Budget  : 11 ms
```

Les deux configurations dépassent le budget de 11 ms. Le calcul réalisé n'est donc pas suffisamment rapide pour respecter le budget temporel d'une image dans le contexte étudié.

La différence de 2 ms entre Debug et Release est faible dans cette expérience et ne permet pas, à elle seule, de tirer une conclusion générale sur les performances des deux configurations.

Pour une analyse plus fiable, plusieurs mesures devraient être effectuées dans chaque configuration afin de calculer une moyenne.
