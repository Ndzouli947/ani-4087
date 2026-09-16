### Objectif

Observer l’effet d’un retard dans le suivi des mouvements et déterminer le seuil à partir duquel chaque personne commence à ressentir une gêne ou une perte de confort.

### Déroulement de l’expérience

1. Inviter trois personnes de la classe à essayer le programme de suivi de souris à retard réglable.
2. Commencer avec un retard nul, soit **0 ms**.
3. Demander à la personne de déplacer la souris et d’observer la position du curseur à l’écran.
4. Augmenter progressivement le retard par paliers, par exemple :

   - 0 ms ;
   - 10 ms ;
   - 20 ms ;
   - 30 ms ;
   - 40 ms ;
   - 50 ms ;
   - 75 ms ;
   - 100 ms ;
   - 150 ms ;
   - 200 ms.

5. À chaque palier, demander à la personne :

   - si le mouvement reste naturel ;
   - si elle remarque un décalage entre son geste et l’image ;
   - si elle ressent une gêne, une désorientation ou une difficulté à contrôler le curseur ;
   - à partir de quel retard elle commence à percevoir clairement le décalage.

6. Arrêter l’expérience lorsque la personne indique que le retard devient nettement perceptible ou inconfortable.

### Tableau des résultats

Noter au tableau le seuil observé pour chaque participant.

| Participant | Seuil de perception du retard | Gêne ressentie | Observations |
|-------------|-------------------------------|----------------|--------------|
| Personne 1  | À compléter en classe        | À compléter    | À compléter  |
| Personne 2  | À compléter en classe        | À compléter    | À compléter  |
| Personne 3  | À compléter en classe        | À compléter    | À compléter  |

> Les valeurs doivent être relevées pendant l’expérience. Elles peuvent varier d’une personne à l’autre selon son attention, son habitude des interfaces numériques et sa sensibilité au retard.

### Analyse des résultats

Comparer les trois seuils obtenus.

Un retard faible peut être difficile à remarquer, tandis qu’un retard plus important crée un décalage visible entre le mouvement réel de la main et la réaction du curseur. Ce décalage peut rendre l’interaction moins précise et moins naturelle.

En réalité virtuelle, ce problème peut être plus sensible, car l’utilisateur doit percevoir rapidement les mouvements de sa tête, de ses mains ou de son corps. Un retard trop important peut provoquer :

- une impression de décalage entre le mouvement réel et l’image ;
- une perte de précision ;
- une désorientation ;
- une fatigue visuelle ;
- une sensation d’inconfort ou de cybercinétose.

### Conclusion sur le budget d’une image

L’expérience montre que le temps disponible pour produire et afficher une image est limité. Le retard total ne dépend pas d’une seule étape : il comprend notamment l’acquisition des mouvements, le traitement, le calcul, le rendu et l’affichage.

Pour une fréquence de 50 Hz, le budget théorique d’une image est :

\[
T = \frac{1000}{50} = 20\ \text{ms}
\]

Cela signifie que toutes les étapes doivent idéalement être réalisées en moins de **20 ms** pour maintenir une fréquence de 50 images par seconde.

Si une partie du budget est consommée par le traitement ou le rendu, il reste moins de temps pour les autres opérations. Il faut donc :

- réduire le temps de calcul ;
- optimiser le rendu ;
- limiter les traitements inutiles ;
- utiliser des modèles et des scènes adaptés aux capacités du matériel ;
- surveiller le retard total plutôt que le seul temps de rendu.

### Conclusion générale

Même quelques dizaines de millisecondes peuvent modifier la perception d’une interaction. Le budget d’une image doit donc être considéré comme une contrainte globale : chaque étape doit être suffisamment rapide pour que le mouvement affiché reste cohérent avec le mouvement réel.
