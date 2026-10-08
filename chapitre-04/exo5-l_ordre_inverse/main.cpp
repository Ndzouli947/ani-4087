#include <iostream>
#include <string>

// valuer d'un entier

long long absolu(long long v) {
    return (v < 0) ? -v : v;
}

int main() {
    int n = 0;
    std::cin >> n;

    int deplaces = 0;
    long long pire = 0;

    for(int i = 0; i < n; ++i) {
        std::string nom;
        long long tx, ty, tz;  //transaltion absolue
        long long sx, sy, sz;  //echelle

        std::cin >> nom >> tx >> ty >> tz >> sx >> sy >> sz;

        // maivais ordre
        // on multiplie avant le de diviser et la divsion entre tronque vers 0
        const long long mx = sx * tx / 1000;
        const long long my = sy * ty / 1000;
        const long long mz = sz * tz / 1000;

        // ecart le plus grand des trois ecarts absolus entre bonne et mauvaise position
        long long ecart = absolu(tx - mx);
        if(absolu(ty - my)> ecart) {
            ecart = absolu(ty - my);
        }
        if (absolu(tz - mz)> ecart) {
            ecart = absolu(tz - mz);
        }

        std::cout << nom << ' ' << mx << ' ' << my << ' ' << mz << ' ' << ecart << '\n';

        if(ecart != 0){
            ++deplaces;
        }
        if(ecart > pire){
            pire = ecart;
        }
    }

    std::cout << "DEPLACES " << deplaces << '\n';
    std::cout << "PIRE " << pire << '\n';
    return 0;
}
