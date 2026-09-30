#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEventSystem.h"  

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig config;
    config.title  = "Exercice 3";
    config.width  = 1280;
    config.height = 720;

    //  Champ 1 : position (centered, x, y) 
    config.centered = false;
    config.x =0 ;
    config.y = 0;

    //  Champ 2 : resizable 
    //config.resizable = false;

    //  Champ 3 : opacity 
    //config.opacity = 0.5f;

    // Champ 4 : alwaysOnTop 
    //config.alwaysOnTop = true;

    // Champ 5 : taille minimale (minWidth, minHeight) 
    //config.minWidth  = 600;
    //config.minHeight = 400;

   

    NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    while (fenetre.IsOpen()) {
        NkEvents().PollEvents();
    }

    return 0;
}