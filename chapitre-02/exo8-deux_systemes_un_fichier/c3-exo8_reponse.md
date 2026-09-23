### Exercice 8

### énoncé 

Écrivez les filtres pour Windows et pour Linux dans votre projet, chacun avec ses bibliothèques. Faites vérifier par un camarade sur l'autre système que le projet se construit chez lui sans modification.

Si vous n'avez accès qu'à un système, écrivez quand même les deux et dites ce que vous n'avez pas pu vérifier.


### Code utilisé

```

from Jenga import *

with workspace("MaSalle"):
    configurations(['Debug', 'Release'])
    targetoses([TargetOS.WINDOWS, TargetOS.ANDROID])
    targetarchs([TargetArch.X86_64, TargetArch.ARM64])
    
  

    # Project: MaSalle
    with project("MaSalle"):
        windowedapp()
        language("C++")
        cppdialect("C++17")
        location(".")
        includedirs(["include"])
        #defines(["AVEC_IMPLEMENTATION"])
        files(["src/main.cpp", "include/**.hpp"])
        
        
        with filter("systeme: Windows"):
            links (["user32", "gdi32", "opengl32", "dinput8", "dxguid", "winmm"])
            
        with filter("system: Linux"):
            links(["pthread", "X11", "Xext", "GL"])`

```

### Ce que le résultat confirme 

Le build sans erreur ``Build Successful``, et surtout n'a rien changé dans le comportement par rapport à avant l'ajout des filtres. Le lien vers ``user32``, ``gdi32``, ``opengl32``, ``dinput8``, ``dxguid``, ``winmm`` a été appliqué silencieusement sous le système windows, tandsi que sous système Linux a été silencieusement ignoré car la sortie ne mentionne jamais ```pthread``, ``X11`` ce qui prouve que le filtre a bien fait le tri sans qu'on ait besion de lui demander de faire

### Non vérifié 

Nous n'avons pas eu accès à une machine Linux pour confirmer que le bloc ``system:Linux`` compile et lie réellement sans erreur. Cette étape nécessite qu'un camarade clone le dépôt tel quel sous Linux et lance ``jenga build``

### Conclusion

Sous Windows le fichier ``.jenga`` contenant les deux blocs ``filter("system:Windows")`` et ``filter("system:Linux")`` compile et lie sans erreur. Le filtre correspond au système, le filtre absent est ignoré sans provoquer d'erreur ni d'avertissement