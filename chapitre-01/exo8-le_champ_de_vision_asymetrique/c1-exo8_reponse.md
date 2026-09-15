# Exercice 2 — Champ de vision d'un casque

## Objectif

Chercher les quatre angles du champ de vision d'un casque du commerce, pour l'œil gauche, puis expliquer ce qui se passerait si l'on employait à la place un champ symétrique de même surface.

## Casque étudié

Le casque choisi est le **Meta Quest 3**.

La source utilisée est la **HMD Geometry Database**, qui publie des données de géométrie mesurées pour différents casques de réalité virtuelle.

Source :
https://risa2000.github.io/hmdgdb/hmd_cfgs/MetaQuest3_Native_R72.html

La convention des quatre angles correspond à celle de la spécification OpenXR.

Source :
https://registry.khronos.org/OpenXR/specs/1.0/html/xrspec.html

## Champ de vision de l'œil gauche

Les quatre angles relevés sont :

| Direction             |       Angle |
| --------------------- | ----------: |
| Gauche (`angleLeft`)  | **−54,00°** |
| Droite (`angleRight`) | **+40,00°** |
| Haut (`angleUp`)      | **+43,98°** |
| Bas (`angleDown`)     | **−54,27°** |

## Vérification des dimensions

Le champ horizontal total est :

40,00 − (−54,00) = **94,00°**

Le champ vertical total est :

43,98 − (−54,27) = **98,25°**

## Champ symétrique de même surface

En supposant une approximation rectangulaire, un champ symétrique de même surface conserverait les mêmes dimensions totales, mais serait centré sur l'axe optique : il passerait approximativement de [−54°, +40°] à [−47°, +47°] horizontalement, et de [−54,27°, +43,98°] à [−49,13°, +49,13°] verticalement.
