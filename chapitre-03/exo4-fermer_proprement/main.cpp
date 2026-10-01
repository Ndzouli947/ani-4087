#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEventSystem.h"   
#include "NKEvent/NkKeyboardEvent.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig config;
    config.title  = "Fenêtre";
    config.width  = 1280;
    config.height = 720;

    NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    // Le booléen est déclaré AVANT les gardes : les variables locales sont
    // détruites dans l'ordre inverse, donc les gardes (qui retirent les rappels)
    // disparaissent avant le booléen que les rappels utilisent.
    bool enMarche = true;

    // Chemin 1 : l'utilisateur ferme la fenêtre (croix, Alt+F4).
    auto gardeFermeture = NkEvents().AddEventCallbackGuard<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) {
            enMarche = false;
        });

    // Chemin 2 : l'utilisateur appuie sur Échap.
    auto gardeEchap = NkEvents().AddEventCallbackGuard<NkKeyPressEvent>(
        [&](NkKeyPressEvent* e) {
            if (e->GetKey() == NkKey::NK_ESCAPE) {
                enMarche = false;
            }
        });

    while (enMarche) {
        NkEvents().PollEvents();
    }

    return 0;
}