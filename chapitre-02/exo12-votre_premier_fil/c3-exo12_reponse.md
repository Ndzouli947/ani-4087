# Exercice 12 : Préparation du fichier de projet pour tout le livre

##  Objectif

L'objectif de cet exercice est de préparer le fichier de projet Jenga pour l'ensemble des chapitres à venir.

Le projet utilisé est `NKXRDemo`. Le fichier `.jenga` contient déjà les éléments nécessaires aux chapitres étudiés. Les fonctionnalités des prochains sprints sont préparées sous forme de commentaires `TODO`.

Ces lignes seront décommentées progressivement lorsque le chapitre correspondant sera étudié et que les dépendances exactes seront connues.

---

##  Principe de préparation

Le fichier de projet est organisé de manière à séparer :

* les informations générales du projet ;
* les fichiers sources ;
* les dépendances Nkentseu ;
* les configurations propres aux systèmes ;
* les configurations Vulkan ;
* les configurations Debug et Release ;
* les ajouts prévus pour les prochains sprints.

Les fonctionnalités futures ne sont pas activées immédiatement. Elles sont documentées dans le fichier afin de pouvoir être ajoutées progressivement.

---

##  Sprints déjà étudiés

### Sprint 1 : Deux yeux, deux images ; le repère, la pose et le mètre

Ce sprint introduit notamment les notions de :

* repère ;
* position ;
* pose ;
* orientation ;
* distance ;
* stéréoscopie.

Ces notions constituent les bases mathématiques et spatiales utilisées dans les chapitres suivants.

### Sprint 2 : Jenga, de A à Z

Ce sprint introduit le système de construction Jenga :

* fichier `.jenga` ;
* workspace ;
* projet ;
* configurations ;
* fichiers sources ;
* dépendances ;
* bibliothèques ;
* filtres par système ;
* configurations Debug et Release.

Le fichier `NKXRDemo.jenga` est donc préparé à partir de ce sprint.

---

#  Préparation des sprints à venir

## Sprint 3 : NKWindow et NKEvent

Le projet devra utiliser les fonctionnalités permettant :

* de créer et gérer une fenêtre ;
* de recevoir les événements ;
* de gérer les interactions avec la fenêtre.

Les dépendances exactes seront activées lorsque le sprint sera étudié.

```python
# TODO Sprint 3 :
# Ajouter/activer les éléments nécessaires à NKWindow et NKEvent.
```

---

## Sprint 4 : NKRHI et NKRenderer

Le projet devra intégrer les fonctionnalités de rendu graphique.

Il faudra notamment vérifier :

* le backend graphique ;
* la création des ressources de rendu ;
* le renderer ;
* les dépendances de NKRHI et NKRenderer.

```python
# TODO Sprint 4 :
# Ajouter/activer les éléments nécessaires à NKRHI et NKRenderer.
```

---

## Sprint 5 : Images, modèles, textes, sons

Ce sprint introduira la gestion de différents types de ressources.

Le projet devra être préparé pour gérer notamment :

* images ;
* modèles ;
* textes ;
* sons ;
* ressources associées.

```python
# TODO Sprint 5 :
# Ajouter les modules et ressources nécessaires aux médias.
```

---

## Sprint 6 : La tête, l'orientation et les deux yeux

Le projet devra intégrer les informations relatives :

* à la tête ;
* à son orientation ;
* à la position ;
* aux deux yeux ;
* à la vue stéréoscopique.

```python
# TODO Sprint 6 :
# Ajouter les fonctionnalités XR nécessaires au suivi de la tête,
# à l'orientation et aux deux yeux.
```

---

## Sprint 7 : La cadence et la prédiction

Ce sprint concerne notamment :

* la cadence d'affichage ;
* le temps disponible pour une image ;
* la prédiction ;
* la synchronisation.

```python
# TODO Sprint 7 :
# Ajouter les éléments nécessaires à la gestion du temps,
# de la cadence et de la prédiction.
```

---

## Sprint 8 : Les chaînes d'échange

Le projet devra être préparé pour gérer les échanges entre les différents composants.

```python
# TODO Sprint 8 :
# Ajouter les éléments nécessaires aux chaînes d'échange.
```

---

## Sprint 9 : Les actions

Ce sprint introduira la gestion des actions et des interactions.

Le fichier de projet pourra nécessiter :

* de nouvelles dépendances ;
* des définitions ;
* des ressources ;
* des configurations spécifiques.

```python
# TODO Sprint 9 :
# Ajouter les éléments nécessaires à la gestion des actions.
```

---

## Sprint 10 : La composition et les couches

Le projet devra prendre en charge la composition du rendu et les différentes couches.

```python
# TODO Sprint 10 :
# Ajouter les éléments nécessaires à la composition
# et à la gestion des couches.
```

---

## Sprint 11 :Lire le vrai backend et La même application, deux backends

Il faudra préparer le projet à utiliser directement le backend graphique concerné et le même programme devra pouvoir être construit avec différents backends.

```python
# TODO Sprint 11 :
# Ajouter les configurations spécifiques au backend réelet  les filtres permettant de sélectionner le backend approprié.
```

---


---

## Sprint 12 : Rendre deux fois

Le projet devra réaliser deux rendus correspondant aux deux yeux.

```python
# TODO Sprint 12 :
# Ajouter les configurations nécessaires au rendu stéréoscopique.
```

---

## Sprint 13 :La porte s'ouvre

Ce sprint permettra de poursuivre vers l'utilisation réelle du système XR.

```python
# TODO Sprint 13 :
# Ajouter les dépendances et configurations nécessaires
# à l'utilisation XR réelle.
```

---

## Sprint 14 : Des panneaux qu'on lit

Le projet devra gérer l'affichage de panneaux et de textes dans l'environnement.

```python
# TODO Sprint 14 :
# Ajouter les ressources et fonctionnalités nécessaires
# à l'affichage des panneaux et des textes.
```

### Le son qui place les choses

Il faudra également préparer la gestion du son dans l'espace.

```
# TODO Sprint 14 :
# Ajouter les éléments nécessaires à l'audio spatial.
```

---

## Sprint 15 : Quelqu'un d'autre entre

Le projet devra pouvoir gérer la présence d'un autre utilisateur ou personnage dans l'environnement.

```
# TODO Sprint 15 :
# Ajouter les ressources, dépendances et configurations
# nécessaires à la présence d'un autre utilisateur/personnage.
```

---

## Sprint 16 : Bâtir et livrer

Le dernier sprint concerne la construction et la livraison de l'application.

Il faudra notamment vérifier :

* le build final ;
* le packaging ;
* la signature ;
* le déploiement ;
* les différentes plateformes.

```
# TODO Sprint 16 :
# Préparer le projet pour le build final,
# le packaging, la signature et le déploiement.
```

---

# Devoir d'approfondissement — Jenga et C++

Une dernière partie est consacrée au devoir d'approfondissement.

```
# TODO Approfondissement :
# Ajouter les éventuelles configurations spécifiques
# demandées par le devoir Jenga et C++.
```

---

#  Méthode de progression

Le fichier sera complété progressivement.

Le principe est :

```text
Chapitre étudié
       

Identification des nouveaux besoins
       

Ajout de la dépendance/configuration
       

Décommentage de la ligne correspondante
       

Reconstruction du projet
       

Vérification
```

Il ne faut donc pas activer à l'avance toutes les dépendances inconnues.

---

#  Pourquoi utiliser des commentaires TODO ?

Les commentaires `TODO` permettent de garder une trace des modifications prévues.

Par exemple :

```
# TODO Sprint 4 :
# Ajouter/activer les éléments nécessaires à NKRHI et NKRenderer.
```

Lorsque le Sprint 4 sera étudié, cette indication pourra être remplacée par la configuration exacte fournie dans le chapitre.

Cela évite d'inventer des dépendances et permet de conserver un fichier de projet cohérent.

---

# Conclusion

Le fichier `NKXRDemo.jenga` est maintenant préparé pour l'ensemble du livre.

Les sprints 1 et 2 correspondent aux notions déjà étudiées. Les sprints 3 à 16 ainsi que le devoir d'approfondissement sont préparés sous forme de commentaires `TODO`.

Les lignes correspondantes seront décommentées une par une au fur et à mesure de l'avancement dans le livre.

Le fichier devient ainsi une **feuille de route technique du projet**, tout en restant valide et compréhensible avant l'ajout des futures fonctionnalités.
