## Comparaison Debug / Release

| | Debug | Release |
|---|---|---|
| Taille de l'exécutable | 60 652 octets | 60 652 octets |
| Temps de construction | 0.85 s | 0.92 s |

Les temps de constructions sont proches, et Release est même légèrement plus lent (0.92s contre 0.85s). Sur ce projet le temps est dominé par le démarrage du compilateur et l'édition des liens, pas par le travail d'optimisation, l'écart est 0.07s n'est pas significatif

Or le cours indique que l'écart Debug/Release se compte en facteurs pas en pourcentage, mais cet écart ne peut se manifesterque sur du code qui travaille réellement boucle, calculs, allocations. Avec un programme vide, il n'y a rien à accélérer.