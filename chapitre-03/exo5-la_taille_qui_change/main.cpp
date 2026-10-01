#include <cstdio>

#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEventSystem.h"   

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig config;
    config.title  = "Exercice 5";
    config.width  = 1280;
    config.height = 720;

    NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    bool enMarche = true;
    int  compteur = 0;   // numéro de l'événement, pour pouvoir les compter ensuite

    auto gardeFermeture = NkEvents().AddEventCallbackGuard<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) {
            enMarche = false;
        });

    auto gardeEchap = NkEvents().AddEventCallbackGuard<NkKeyPressEvent>(
        [&](NkKeyPressEvent* e) {
            if (e->GetKey() == NkKey::NK_ESCAPE) {
                enMarche = false;
            }
        });

    
    auto gardeTaille = NkEvents().AddEventCallbackGuard<NkWindowResizeEvent>(
        [&](NkWindowResizeEvent* e) {
            ++compteur;
            std::printf("#%d : %u x %u\n", compteur,
                        (unsigned)e->GetWidth(), (unsigned)e->GetHeight());
            std::fflush(stdout);
        });

    while (enMarche) {
        NkEvents().PollEvents();
    }

    std::printf("Total : %d evenement(s) de redimensionnement\n", compteur);
    return 0;
}
