### Comparaison des deux messages:


1er cas:
```
╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MaSalle                                                        Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                 Compilation Error: main.cpp                                  ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\Users\PC\Documents\ani-4087\chapitre-02\exo1-le_projet_minimal\src\main.cpp: In function  ║
║ 'int main()':                                                                                ║
║ C:\Users\PC\Documents\ani-4087\chapitre-02\exo1-le_projet_minimal\src\main.cpp:5:9: error:   ║
║ 'class MaClasse' has no member named 'afficher'                                              ║
║      obj.afficher();                                                                         ║
║          ^~~~~~~~                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\PC\Documents\ani-4087\chapitre-02\exo1-le_projet_minimal\src\main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 1.17s  │
│ Errors: 1  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         1
Time:           1.17s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ MaSalle
```

Elle appartient à l'étape de compilation car el build s'arrête directement au moment où le compilateur analyse ``` main.cpp``` ligne par ligne. Il sait que MaClasse existe, mais en lisant sa d"fintion, il constate qu'elle est vide, donc afficher n'existe pas dans cette classe.


2e cas:


```
╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: Link Failed                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\Users\PC\Documents\ani-4087\chapitre-02\exo1-le_projet_minimal\Build\Obj\Debug-Windows\Ma ║
║ Salle\src_main.obj: In function `main':                                                      ║
║ C:/Users/PC/Documents/ani-4087/chapitre-02/exo1-le_projet_minimal/src/main.cpp:4: undefined  ║
║ reference to `MaClasse::MaClasse()'                                                          ║
║ C:/Users/PC/Documents/ani-4087/chapitre-02/exo1-le_projet_minimal/src/main.cpp:5: undefined  ║
║ reference to `MaClasse::afficher()'                                                          ║
║ collect2.exe: error: ld returned 1 exit status                                               ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝
✗ Link failed: Build\Bin\Debug-Windows\MaSalle\MaSalle.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 2.27s  │
│ Errors: 3  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         3
Time:           2.28s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ MaSalle

```

Elle appartient à l'étape d'édition de liens, juste avant l'erreur la compilation réussi, c'est seulement au moment du linking que ça échoue. Le compilateur savait que Maclasse existait et avait une méthode ```afficher()```, mais personne n'a jamais écrit le code réel de cette méthode dans un .cpp ce qui fait que le linker ne trouve rine à appeller



Parmi cees deux cas le cas que nous aurons diagnostiquer c'est le 1 car le 'class MaClasse' has no member named 'afficher' dit qu'il y'a pas de membre à appelé afficher et le massage pointe directement vers l'endroit du bug