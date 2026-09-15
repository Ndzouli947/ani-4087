## Mesure

La durée maximale mesurée pour le rendu d'une image est de **14,7 ms**.

## Estimation pour deux yeux

Pour un affichage stéréoscopique, la scène doit être rendue pour l'œil
gauche puis pour l'œil droit.

En supposant que le coût soit doublé :

**14,7 × 2 = 29,4 ms**

Le rendu des deux vues coûterait donc environ **29,4 ms**.

## Temps disponible

À 90 Hz, une image doit être produite en environ **11,1 ms**.

Après avoir effectué deux rendus :

**11,1 − 29,4 = -18,3 ms**

Le budget est donc dépassé de **18,3 ms**.

## Conclusion

Le rendu est beaucoup trop coûteux pour tenir dans le budget d'un casque
à 90 Hz s'il devait réellement prendre 14,7 ms par image.

Il faudrait principalement réduire le coût du rendu : simplifier la scène,
réduire le nombre d'objets ou de polygones, optimiser les effets graphiques
et utiliser efficacement le GPU.
