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
 
    
    fenetre.ShowMouse(false);          // cacher le curseur
    fenetre.ClipMouseToClient(true);   // confiner le curseur à la zone client
 
    bool enMarche = true;
 
    auto gardeFermeture = NkEvents().AddEventCallbackGuard<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) { enMarche = false; });
 
    auto gardeEchap = NkEvents().AddEventCallbackGuard<NkKeyPressEvent>(
        [&](NkKeyPressEvent* e) {
            if (e->GetKey() == NkKey::NK_ESCAPE) { enMarche = false; }
        });
 
    int numero = 0;
    int dernierX = -1, dernierY = -1;
 
    while (enMarche) {
        NkEvents().PollEvents();
 
        
        const int x  = (int)NkInput.MouseX();
        const int y  = (int)NkInput.MouseY();
        const int rx = (int)NkInput.MouseRawDeltaX();
        const int ry = (int)NkInput.MouseRawDeltaY();
 
        ++numero;
 
        // Pour garder le terminal lisible : on n'écrit que si quelque chose a bougé.
        if (x != dernierX || y != dernierY || rx != 0 || ry != 0) {
            std::printf("image %d : x=%d y=%d  rawDelta=(%d, %d)\n", numero, x, y, rx, ry);
            std::fflush(stdout);
            dernierX = x;
            dernierY = y;
        }
 
        Sleep(16)
    }
 
    // IMPORTANT : rendre le curseur au système. Le confinement peut survivre
    // au programme s'il n'est pas relâché
    fenetre.ClipMouseToClient(false);
    fenetre.ShowMouse(true);
 
    return 0;
}