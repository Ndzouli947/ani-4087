
# Exercice 15 : 

## Objectif

L'objectif de cet exercice est de fabriquer une clé de signature qui pourra être utilisée pour signer l'application Android.

La clé ainsi que son mot de passe doivent être conservés **en dehors du dépôt Git**, afin d'éviter de publier des informations sensibles.

---

##  Création du dossier de stockage

J'ai choisi de stocker la clé dans un dossier situé en dehors du dépôt du projet.

La commande utilisée est :

```cmd
mkdir "%USERPROFILE%\cles"
```

Le dossier créé se trouve donc dans :

```text
C:\Users\PC\cles
```

---

##  Génération de la clé avec Jenga

La clé de signature a été générée directement avec la commande `jenga keygen` :

```cmd
jenga keygen -i --alias masalle --output "%USERPROFILE%\cles\masalle.jks"
```

### Signification de la commande

* `jenga keygen` : lance l'outil de génération de clé de Jenga ;
* `-i` : lance la génération de manière interactive ;
* `--alias masalle` : définit `masalle` comme alias de la clé ;
* `--output` : indique l'emplacement du fichier de clé ;
* `masalle.jks` : fichier contenant le keystore Java utilisé pour la signature.

---

##  Paramètres utilisés

Lors de la génération, Jenga a demandé plusieurs informations.

### Alias

```text
masalle
```

### Validité

J'ai conservé la valeur proposée par défaut :

```text
10000 jours
```

---

## Emplacement de la clé

La clé a été enregistrée à l'emplacement :

```text
C:\Users\PC\cles\masalle.jks
```

Ce dossier est situé en dehors du dépôt du projet `ani-4087`.

Ainsi, le fichier de signature privée n'est pas placé dans le dépôt Git.

---

##  Gestion du mot de passe

Lors de la création de la clé, un mot de passe a été défini.

Pour des raisons de sécurité, **le mot de passe n'est pas indiqué dans ce rapport et n'est pas enregistré dans le dépôt Git**.

Il est conservé séparément dans un emplacement privé et sécurisé.

---

## Vérification

La génération de la clé s'est terminée correctement et le fichier suivant a été créé :

```text
C:\Users\PC\cles\masalle.jks
```

La clé est donc disponible pour les prochaines étapes de signature de l'application Android.

---

## Conclusion

La clé de signature Android a été créée avec succès à l'aide de `jenga keygen`.

La commande utilisée est :

```cmd
jenga keygen -i --alias masalle --output "%USERPROFILE%\cles\masalle.jks"
```

La clé est stockée en dehors du dépôt du projet et son mot de passe est conservé séparément afin de ne pas exposer les informations sensibles dans le dépôt.
