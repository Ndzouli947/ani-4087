#include <chrono>
#include <cstdio>
#include <thread>

#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEventSystem.h" 
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkEventDispatcher.h" // input
#include "NKTime/NkClock.h"
#include "NKTime/NkChrono.h"
#include "NKLogger/NkLog.h"

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

    bool enMarche = true;
    int  compteurEtat      = 0;   // images où Espace est tenue (lu par l'état)
    int  compteurEvenement = 0;   // NkKeyPressEvent reçus sur Espace

    auto gardeFermeture = NkEvents().AddEventCallbackGuard<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) { enMarche = false; });

    // Échap quitte ; Espace est compté. Aucun filtre sur la répétition :
    // on compte tous les NkKeyPressEvent reçus.

    auto gardeTouches = NkEvents().AddEventCallbackGuard<NkKeyPressEvent>(
        [&](NkKeyPressEvent* e) {
            if (e->GetKey() == NkKey::NK_ESCAPE) { enMarche = false; }
            if (e->GetKey() == NkKey::NK_SPACE)  { ++compteurEvenement; }
        });

    while (enMarche) {
        NkEvents().PollEvents();

        // État : on lit APRÈS avoir pompé les événements, pour avoir le présent.
        // À VÉRIFIER : la forme exacte de l'appel (NkInput.IsKeyDown ou NkInput().IsKeyDown ?).
        if (NkInput.IsKeyDown(NkKey::NK_SPACE)) {
            ++compteurEtat;
        }

        // Une "image" = un tour de boucle. Sans cette pause, la boucle tourne
        // des milliers de fois par seconde et le compteur d'état explose.
        // ~60 images par seconde, pour que les nombres restent lisibles.
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    std::printf("Compteur d'etat      (IsKeyDown)      : %d\n", compteurEtat);
    std::printf("Compteur d'evenement (NkKeyPressEvent) : %d\n", compteurEvenement);
    return 0;
}