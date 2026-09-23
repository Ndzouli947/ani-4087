```
╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: Link Failed                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\Users\PC\Documents\ani-4087\chapitre-02\exo1-le_projet_minimal\Build\Obj\Debug-Windows\Ma ║
║ Salle\src_main.obj: In function `main':                                                      ║
║ C:/Users/PC/Documents/ani-4087/chapitre-02/exo1-le_projet_minimal/src/main.cpp:4: undefined  ║
║ reference to `hello()'                                                                       ║
║ collect2.exe: error: ld returned 1 exit status                                               ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝
✗ Link failed: Build\Bin\Debug-Windows\MaSalle\MaSalle.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 2.06s  │
│ Errors: 2  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘
```

### Pourquoi cette erreur se produit:

Le main.cpp a été compilé avec succès en src_main.obj. Le préprocesseur a trouvé helloworld.hpp, la compilationa réussi.

Mais au moment de l'édition des leins l'étape ou on assemble tous les fichiers .obj ensemble pour créer MaSalle.exe le inker chercher les code réel de la fonction hello() et ne le trouve pas.

Pour revenir à la dernière reponse de cete exercice a quelle étape ça appartient : c'est l'étape de l'éditoin des liens(linking)

Les indices sont claires:

- Le titre dit littéralemnt "Compilation" Error: Link Failed
- Le message undefined reference to 'hello()' est la signature classique d'une erruer de linking.
