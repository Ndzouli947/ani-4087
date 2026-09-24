## Available Toolchains

Après avoir exécuté la commande `jenga info -v`, le tableau `Available Toolchains` affiche trois toolchains :

| Nom           | Famille     | Système cible | Architecture | Environnement |
| ------------- | ----------- | ------------- | ------------ | ------------- |
| `host-gcc`    | gcc         | Windows       | x86_64       | mingw         |
| `mingw`       | gcc         | Windows       | x86_64       | mingw         |
| `android-ndk` | android-ndk | Android       | arm64        | android       |

### Ce qui est présent

* `host-gcc` est disponible pour compiler des programmes C/C++ sous Windows en x86_64.
* `mingw` est disponible pour la compilation Windows avec GCC/MinGW.
* `android-ndk` est disponible pour la compilation destinée à Android en architecture ARM64.

### Ce qui manque

Aucune des toolchains attendues dans le tableau n'est signalée comme manquante. Les toolchains Windows et Android nécessaires sont donc détectées par Jenga.

### Conclusion

Ma machine dispose actuellement des toolchains `host-gcc`, `mingw` et `android-ndk`. L'environnement est donc configuré pour effectuer des compilations Windows x86_64 et Android ARM64 avec les toolchains détectées par Jenga.
