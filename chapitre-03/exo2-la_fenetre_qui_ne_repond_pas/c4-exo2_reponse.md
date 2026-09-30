### Exercice 2 : La fenêtre qui ne répond pas
---
# énoncé:

Remplacez le corps de la boucle par un commentaire, de façon à ne plus appeler PollEvents.

Lancez, attendez, et rendez une capture du moment où le système déclare la fenêtre bloquée. Chronométrez au bout de combien de secondes cela arrive sur votre machine.
---
# Solution 

Le corps de la boucle devient un commentaire 
```
while (fenetre.IsOpen()) {
    // NKEvents().PollEvents();
}
```
## Ce qui se passe 
Windows envoie à chaque fenêtre des messages (déplacement, cli, redessin, fermeture). **PollEvents** lui sert à les traiter. Sans cet appel, la fenêtre s'ouvre, mais elle ne répond à rien. Au bout de 72 secondes(temps récupérer à l'aide d'un chronomètre), Windows la déclare bloquée le tire affiche **Ne répond pas**

La fenêtre ne réagit plus à la croix pour la fermer. Du coup pour la fermer on tape au clavier dans le terminal ``Ctrl + C``et dans le terminal un message sera affiché pour dire que ça été interrompu; le message est le suivant `` Interrupted.``