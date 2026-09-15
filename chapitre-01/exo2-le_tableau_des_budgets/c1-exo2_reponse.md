## Tableau des résultats

| Étape                               | Valeur mesurée trouvée | Source                        | Conclusion                                                                                                             |
| ----------------------------------- | ---------------------- | ----------------------------- | ---------------------------------------------------------------------------------------------------------------------- |
| Les capteurs mesurent le mouvement  | Introuvable séparément | Warburton et al.              | L'échantillonnage des capteurs est inclus dans la chaîne, mais aucune valeur isolée et généralisable n'est donnée.     |
| Le système transmet la mesure       | Introuvable séparément | Warburton et al.              | Le transfert est identifié comme une étape, mais sa durée indépendante n'est pas fournie.                              |
| Votre application décide et dessine | Introuvable séparément | Warburton et al.              | La durée dépend du moteur, de la scène, du GPU et du matériel.                                                         |
| Le compositeur assemble             | Introuvable séparément | Documentation Meta Horizon OS | Le rôle du compositeur est documenté, mais aucune durée universelle mesurée n'est donnée.                              |
| L'écran affiche l'image             | 0,5 à 2 ms             | Warburton et al.              | Cette valeur concerne l'éclairage d'un écran à faible persistance, et non nécessairement toute la latence d'affichage. |

## Sources consultées

1. Warburton, M. et al. (2023). *Measuring motion-to-photon latency for sensorimotor experiments with virtual reality systems*. Behavior Research Methods.

2. Meta Horizon OS Developers. *The compositor*.
