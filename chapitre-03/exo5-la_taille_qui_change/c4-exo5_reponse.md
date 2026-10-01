# Exercice 5: La taille qui change
---

# Énoncé 
---
Écoutez NkWindowResizeEvent et affichez la nouvelle taille dans la console à chaque changement.

Redimensionnez lentement, puis d'un coup. Rendez les deux séries de nombres, et dites ce que vous en concluez sur le nombre d'événements reçus.

### main.cpp
```cpp
auto gardeTaille = NkEvents().AddEventCallbackGuard<NkWindowResizeEvent>(
        [&](NkWindowResizeEvent* e) {
            ++compteur;
            std::printf("#%d : %u x %u\n", compteur,
                        (unsigned)e->GetWidth(), (unsigned)e->GetHeight());
            std::fflush(stdout);
        });

```

### Redimensionnement lent 
---
J'ai commencé à redimensionner la fenêtre lentement en faisant glisse le bord de la fenêtre et j'ai constaté que plusieurs changements ont apparu dans la console j'ai également observé que la taille changeait et que des événements étaient affichés pendant que je deplaçais le bord de la fenêtre.

### Redimensionnement d'un coup 
---
J'ai redimensionné la fenêtre rapidement, cette fois ci il y avait plusieurs changements affichés mais moins nombreux que lors du redimensionnnement lent.

# Conclusion
---
Lors du redimensionnement lent, nous avons reçu beaucoup d'événements parce que la taille de la fenêtre changeait plusieurs fois quand nous avons déplacé le bord doucement, mais avec le redimensionnement rapide nous avons eu plusieurs événement moins nombreux

Donc ```NKWindoResizeEvent`` est  appelée à chaque changement de taille par le programme. Le nombre d'événements reçus dépendent  de la manière dont le fenêtre est redimensionnée.
