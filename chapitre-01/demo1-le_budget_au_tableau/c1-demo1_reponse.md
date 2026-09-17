## Objectif

Représenter au tableau un budget total de 20 millisecondes sous la forme d’une barre, puis faire placer par la classe les cinq étapes nécessaires à l’affichage d’une image à leur échelle.

L’objectif est de comprendre comment les 20 millisecondes sont réparties et quelle durée reste réellement disponible pour l’exécution du code.

## Représentation du budget

Le budget total est de :

**20 ms**

On peut le représenter par une barre divisée en cinq étapes :

text
0 ms                                                        20 ms
|-------------------------------------------------------------|
| Acquisition | Traitement | Calcul | Rendu | Affichage       |
|-------------|------------|--------|-------|-----------------|

Les cinq étapes
1. Acquisition des données

Cette étape consiste à récupérer les informations nécessaires :

position de la souris ;

position et orientation de la tête ;

mouvements des contrôleurs ;

données provenant des capteurs.

2. Traitement des données

Les données acquises sont nettoyées et préparées pour être utilisées par le programme.

Cette étape peut comprendre :

la conversion des coordonnées ;

la filtration des mouvements ;

la vérification des données ;

la préparation des informations destinées au moteur graphique.

3. Calcul

Le programme calcule la nouvelle position des objets ou de la caméra virtuelle.

Il peut notamment déterminer :

la nouvelle position de la caméra ;

les mouvements des objets ;

les collisions ;

les interactions avec l’environnement ;

les transformations géométriques.

4. Rendu

Le moteur graphique construit l’image à partir des calculs précédents.

Il détermine notamment :

les objets visibles ;

leur position à l’écran ;

les lumières ;

les textures ;

les ombres ;

la perspective.

5. Affichage

L’image calculée est envoyée vers l’écran ou vers les écrans du casque de réalité virtuelle.

Cette étape comprend la transmission et l’actualisation de l’image affichée à l’utilisateur.

Activité réalisée en classe

La classe dispose d’une barre représentant les 20 millisecondes.

Chaque groupe reçoit les cinq étapes :

Acquisition ;

Traitement ;

Calcul ;

Rendu ;

Affichage.

Les étudiants doivent placer chaque étape sur la barre en tenant compte du temps qu’elle peut consommer.

Une proposition de répartition illustrative peut être représentée ainsi :

Budget total : 20 ms

| Acquisition | Traitement | Calcul | Rendu       | Affichage |
|    2 ms     |    3 ms    |  4 ms  |    7 ms     |   4 ms    |
|-------------|------------|--------|-------------|-----------|
0                                                            20 ms

Cette répartition est seulement un exemple. Dans une application réelle, la durée de chaque étape varie selon le matériel, la complexité de la scène et les optimisations du programme.

Ce qui reste pour le code

Le budget total est de 20 ms. Une partie de ce temps est déjà utilisée par :

l’acquisition des données ;

le traitement ;

les calculs ;

le rendu ;

l’affichage.

Il ne reste donc qu’une petite partie du budget pour le code supplémentaire.

Par exemple, si les quatre premières étapes et l’affichage consomment ensemble 18 ms, il ne reste que :

20 − 18 = 2 ms

Le code doit donc être exécuté dans une durée très courte. Une fonction trop lente, une boucle mal optimisée ou un calcul inutile peut dépasser le budget et provoquer un retard visible.

Réactions de la classe

Après avoir placé les cinq étapes, la classe peut discuter des questions suivantes :

Est-il facile de faire tenir toutes les étapes dans 20 ms ?

Quelle étape semble consommer le plus de temps ?

Que se passe-t-il si une étape dépasse la durée prévue ?

Peut-on supprimer certaines opérations inutiles ?

Comment réduire le temps d’exécution du code ?

Pourquoi faut-il optimiser les calculs dans une application de réalité virtuelle ?

Que ressent l’utilisateur lorsque le budget de 20 ms est dépassé ?

La représentation des 20 millisecondes montre que le budget de latence doit être partagé entre plusieurs étapes indispensables.

Le temps disponible pour le code est donc limité. Pour respecter ce budget, le programme doit être conçu et optimisé afin que l’acquisition, le traitement, les calculs, le rendu et l’affichage puissent être réalisés rapidement.

Cette contrainte est particulièrement importante en réalité virtuelle, car le dépassement du budget peut provoquer un décalage entre les mouvements de l’utilisateur et l’image affichée.
