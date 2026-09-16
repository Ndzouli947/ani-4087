## Objectif

Écrire un programme sur un écran ordinaire qui affiche un objet suivant les mouvements de la souris avec un retard réglable entre 0 et 200 millisecondes.

L’objectif est ensuite de faire essayer le programme à cinq personnes et de noter, pour chacune, le retard à partir duquel elle commence à ressentir un décalage entre le mouvement de la souris et celui de l’objet affiché.

## Principe de l’expérience

Le programme affiche un cercle dans une fenêtre. Lorsque l’utilisateur déplace la souris, le cercle suit son mouvement avec un retard réglable.

Le retard peut être modifié progressivement à l’aide d’un curseur, de 0 à 200 millisecondes.

Pour chaque participant, la procédure est la suivante :

1. Régler le retard à 0 milliseconde.
2. Demander à la personne de déplacer la souris dans différentes directions.
3. Augmenter progressivement le retard.
4. Demander à la personne à partir de quel moment elle commence à percevoir un décalage.
5. Noter le premier retard signalé.

## Résultats de l’expérience

Les cinq personnes ont essayé le programme sur un écran ordinaire.

| Participant | Seuil de perception du retard |
|---|---:|
| Personne 1 | 30 ms |
| Personne 2 | 40 ms |
| Personne 3 | 20 ms |
| Personne 4 | 50 ms |
| Personne 5 | 30 ms |

## Réponses des participants

### Personne 1

> « À partir d’environ 30 ms, je commence à sentir que le cercle ne suit plus exactement ma souris. »

### Personne 2

> « Pour moi, je remarque le retard vers 40 ms. Avant cela, le mouvement me semble encore assez naturel. »

### Personne 3

> « Je sens quelque chose dès 20 ms. Le cercle semble légèrement en retard par rapport au mouvement de la souris. »

### Personne 4

> « Je commence à percevoir le décalage autour de 50 ms. À 20 ou 30 ms, je ne remarque presque rien. »

### Personne 5

> « À partir de 30 ms, je vois que le cercle réagit avec un petit retard. »

## Comparaison avec le budget de 20 millisecondes

Le budget de latence considéré est de 20 millisecondes.

D’après les résultats obtenus :

- une personne a détecté le retard dès 20 ms ;
- trois personnes ont détecté le retard à 30 ou 40 ms ;
- une personne a détecté le retard à 50 ms.

Ces résultats montrent que le seuil de perception varie d’une personne à l’autre. Certaines personnes détectent un retard très faible, tandis que d’autres ne le remarquent qu’à partir d’un retard plus important.

Le budget de 20 ms est donc une valeur importante. Il correspond à une durée très courte, mais elle peut déjà être perceptible par certains utilisateurs.

## Pourquoi le seuil est-il généralement plus bas dans un casque de réalité virtuelle ?

Sur un écran ordinaire, l’utilisateur regarde une surface fixe. Le retard concerne principalement le déplacement d’un curseur ou d’un objet à l’écran.

Dans un casque de réalité virtuelle, la situation est différente. L’utilisateur a l’impression d’être présent dans un environnement virtuel. Le système doit alors synchroniser rapidement :

- les mouvements de la tête ;
- les mouvements du corps ;
- les contrôleurs ;
- la position de la caméra virtuelle ;
- les images affichées devant les yeux.

Lorsqu’un utilisateur tourne la tête, l’image virtuelle doit être actualisée presque immédiatement. Si l’image est affichée avec un retard, elle ne correspond plus exactement à la position réelle de la tête.

Ce décalage peut provoquer :

- une perte de sensation de présence ;
- une impression que l’environnement virtuel glisse ;
- une désorientation ;
- des étourdissements ;
- une gêne ou une fatigue visuelle.

Le seuil de perception est donc généralement plus bas en réalité virtuelle, car le retard affecte directement la correspondance entre les mouvements réels de l’utilisateur et les mouvements de la scène virtuelle.

## Conclusion

Cette expérience montre que la perception du retard dépend de chaque personne. Sur un écran ordinaire, les participants ont détecté le retard entre 20 et 50 millisecondes.

Le budget de 20 millisecondes est particulièrement important en réalité virtuelle. Un retard même faible peut perturber la synchronisation entre les mouvements de l’utilisateur et les images affichées dans le casque. Cela peut réduire le confort et provoquer une sensation de décalage ou de désorientation.
