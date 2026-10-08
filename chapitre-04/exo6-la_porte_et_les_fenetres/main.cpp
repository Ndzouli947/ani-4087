#include <iostream>
#include <string>

int main() {
    long long largeurMur = 0;
    long long hauteurMur = 0;
    long long seuil = 0;
    int n = 0;
    std::cin >> largeurMur >> hauteurMur >> seuil >> n;

    int justes = 0;
    int aReprendre = 0;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long u, y, l, h, e, d;
        std::cin >> nom >> u >> y >> l >> h >> e >> d;

        // Profondeur de la face avant (la saillie) et de la face arrière
        const long long saillie = d + e / 2;
        const long long arriere = d - e / 2;

        // Les bords peuvent coïncider avec ceux du mur
        // En largeur, on compare les valeurs doublées pour ne pas dépendre de W / 2.
        const bool deborde = (2 * u - l < -largeurMur)
                          || (2 * u + l > largeurMur)
                          || (y - h / 2 < 0)
                          || (y + h / 2 > hauteurMur);

        // Le premier verdict qui s'applique gagne
        std::string verdict;
        if (deborde) {
            verdict = "DEBORDE";
        } else if (saillie <= 0) {
            verdict = "INVISIBLE";
        } else if (saillie < seuil) {
            verdict = "CLIGNOTE";
        } else if (arriere > seuil) {
            verdict = "DECOLLE";
        } else {
            verdict = "OK";
        }

        // La saillie est affichée pour tous les panneaux, même ceux qui débordent
        std::cout << nom << ' ' << saillie << ' ' << verdict << '\n';

        if (verdict == "OK") {
            ++justes;
        } else {
            ++aReprendre;
        }
    }

    std::cout << "OK " << justes << '\n';
    std::cout << "A REPRENDRE " << aReprendre << '\n';
    return 0;
}
