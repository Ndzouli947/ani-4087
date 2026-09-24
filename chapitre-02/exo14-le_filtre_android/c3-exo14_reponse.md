# Exercice 14 : 

## Objectif

L'objectif de cet exercice est d'ajouter au fichier de projet `MaSalle.jenga` un filtre spécifique à la plateforme **Android**, contenant les définitions et les bibliothèques nécessaires à la compilation Android.

L'exercice demande également de vérifier que ce filtre est réellement pris en compte lors d'une compilation ciblant Android.

---

## Ajout du filtre Android

Dans le fichier `MaSalle.jenga`, un filtre spécifique à Android a été ajouté à l'intérieur du bloc du projet `MaSalle`.

```python
with filter("system:Android"):
    defines([
        "ANDROID",
        "NKENTSEU_PLATFORM_ANDROID"
    ])

    links([
        "EGL",
        "GLESv3",
        "android",
        "log"
    ])
```

Les bibliothèques Windows et Linux restent dans leurs propres filtres afin qu'elles ne soient pas utilisées lors d'une compilation Android.

La structure permet ainsi d'avoir des dépendances différentes selon la plateforme ciblée :

* **Windows** : bibliothèques Windows et DirectX ;
* **Linux** : bibliothèques X11 et OpenGL ;
* **Android** : bibliothèques EGL, OpenGL ES, Android et Log.

---

##  Vérification avec `jenga info -v`

Dans un premier temps, j'ai exécuté :

```powershell
jenga info -v
```

La commande permet d'obtenir des informations générales sur le workspace, notamment les configurations, les plateformes, les architectures et les toolchains disponibles.

Cependant, l'ajout ou la modification du filtre Android ne modifie pas de manière visible les informations générales affichées par `jenga info -v`.

Ainsi, cette commande ne permet pas de vérifier directement si le contenu du filtre :

```python
with filter("system:Android"):
```

est effectivement appliqué lors de la compilation.

---

##  Vérification avec `--platform`

Pour vérifier que le filtre Android est réellement activé, j'ai lancé une compilation en ciblant explicitement Android avec :

```powershell
jenga build --platform android-arm64 --config Debug -v
```

Cette commande demande à Jenga de construire le projet en configuration **Debug**, pour la plateforme **Android ARM64**, avec l'affichage détaillé des opérations de compilation.

---

##  Résultat obtenu

La compilation a bien sélectionné la plateforme Android.

Le résultat indique notamment :

```text
Build\Bin\Debug-Android\MaSalle\libMaSalle.so
```

Le chemin `Debug-Android` montre que Jenga utilise bien la cible Android.

La compilation utilise également le NDK Android installé sur la machine :

```text
Android\Sdk\ndk\30.0.16248370
```

Cependant, le processus de linkage échoue ensuite avec l'erreur :

```text
undefined symbol: android_main
```

Cette erreur est différente des erreurs précédentes concernant les bibliothèques Windows et Linux.

---


## Conclusion

L'exercice permet de constater que `jenga info -v` ne suffit pas pour vérifier l'activation d'un filtre de plateforme.

La vérification doit être réalisée en lançant une véritable compilation avec l'option `--platform`.

Dans notre cas, la commande :

```powershell
jenga build --platform android-arm64 --config Debug -v
```

a bien sélectionné la plateforme Android et a utilisé la configuration Android du projet.

