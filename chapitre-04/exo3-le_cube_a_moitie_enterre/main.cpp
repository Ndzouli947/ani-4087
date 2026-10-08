// Description :
//   Pour chaque cube, calcule la hauteur de son bas et de son haut, dit s'il
//   repose sur le sol et donne la hauteur de centre qui le pose au sol.
//   Affiche ensuite le bilan A CORRIGER / PIRE.
//
// Caracteristiques :
//   - Le cube du moteur est centre sur son origine : on utilise la
//     DEMI-hauteur e / 2, jamais la hauteur entiere.
//   - SOUS LE SOL est teste avant ENTERRE.


#include <iostream>
#include <string>

int main(){
    int n = 0;
    std::cin >> n;

    int aCorriger = 0;
    long long pire = 0;

    for (int i = 0; i < n; ++i){
        std::string nom;
        long long e = 0; // echelle verticale en millième(hauteur en millimètres)
        long long y = 0; //hauteur du centre en millimètres
        std::cin >> nom >> e >> y;

        //le cube centré
        //utilisons la demi_hauteur

        const long long demi = e /2;
        const long long bas = y - demi;
        const long long haut = y + demi;

        // verdicts dans l'ordre

        std::string verdict;
        if (haut <= 0) {
            verdict = "SOUS LE SOL";
        } else if (bas < 0){
            verdict = "ENTERRE";
        }else if (bas == 0){
            verdict = "POSE";
        } else {
            verdict = "FLOTTE";
        }

        // la hauteur du centre qui pose le cube ne depend de y

        std::cout << nom << ' ' << bas << ' ' << haut << ' ' << verdict << ' ' << demi << '\n';

        if(verdict != "POSE"){
            ++ aCorriger;
        }

        // distance entre le haut et le bas (en valeur absolue)

        const long ecart = (bas < 0) ? - bas : bas;
        if(ecart > pire){
            pire = ecart;
        }
    }

    std::cout << "A CORRIGER " << aCorriger << '\n';
    std::cout << " PIRE " << pire << '\n';

    return 0;
}
