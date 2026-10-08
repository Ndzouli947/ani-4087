#include <iostream>
#include <string>
#include <vector>

// emprise au sol d'un rectangle avec une vue de dessus

struct Rectangle {
    long long xmin;
    long long xmax;
    long long zmin;
    long long zmax;
};

// angle bouche si un seul mur contient son carré
bool contientTout(const Rectangle& mur, const Rectangle& carre) {
    return mur.xmin <= carre.xmin && mur.xmax >= carre.xmax
    && mur.zmin <= carre.zmin && mur.zmax >= carre.zmax;
}

int main() {
    long long cote = 0;
    long long epaisseur = 0;
    int n = 0;
    std::cin >> cote >> epaisseur >> n;

    std::vector<Rectangle> murs;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long cx, cz, sx, sz;
        std::cin >> nom >> cx >> cz >> sx >> sz;

        //emprise du centre moins la demi-taille au centre plus la demi-taille
        const Rectangle emprise = {cx- sx / 2, cx + sx / 2, cz - sz/ 2, cz + sz / 2};
        murs.push_back(emprise);

        std::cout << nom << ' ' << emprise.xmin << ' ' << emprise.xmax << ' ' << emprise.zmin << ' ' << emprise.zmax << '\n';
    }

    const long long h = cote / 2;
    const long long e = epaisseur;

    //quantre(4) dansl'ordre
    const std::string noms[4] = {
        "FOND_GAUCHE", "FOND_DROIT", "ENTREE_GAUCHE", "ENTREE_DROIT"
    };

    const Rectangle angles[4] = {
        {-h - e, -h, -h - e, -h},
        {h, h + e, -h - e, -h},
        {-h - e, -h, h, h + e},
        {h, h + e, h, h + e},
    };

    int trous = 0;
    for(int a = 0; a < 4; ++a){
        bool bouche = false;
        for (const Rectangle& mur: murs) {
            if(contientTout(mur, angles[a])){
                bouche = true;
                break;
            }
        }
        if(!bouche){
            ++trous;
        }

        std::cout << noms[a] << ' ' << (bouche ? "BOUCHE" : "TROU") << '\n';
    }

    std::cout << "TROUS " << trous << '\n';
    return 0;
}
