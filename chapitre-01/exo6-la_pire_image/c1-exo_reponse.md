## Mesures sur 1000 images

J'ai mesuré la durée de chaque image produite par un programme qui
dessine en boucle.

| Mesure | Résultat |
|---|---:|
| Durée de la plus longue image | 14,7 ms |
| Nombre d'images dépassant 11 ms | 37 |

## Analyse

Sur les 1000 images observées, la durée de l'image la plus longue est
de 14,7 ms. De plus, 37 images dépassent la limite de 11 ms.

Cela signifie que le programme n'est pas suffisamment régulier pour
garantir une expérience confortable dans un casque fonctionnant autour
de 90 Hz. Même si la majorité des images sont suffisamment rapides,
les images qui dépassent 11 ms peuvent provoquer des ralentissements
ou une perte de fluidité.

## Le programme tiendrait-il dans un casque ?

Non, pas de manière fiable.

À 90 Hz, une image doit être produite en environ 11,1 ms. Comme certaines
images prennent plus de 11 ms et que la plus longue atteint 14,7 ms,
le programme risque de manquer certaines échéances d'affichage.

Pour une application de réalité virtuelle, il faudrait donc optimiser
le programme afin de réduire la durée maximale des images et surtout
d'éviter les dépassements de la durée disponible.
