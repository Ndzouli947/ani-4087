#include <iostream>
#include <string>

int main () {
    int n = 0;
    std::cin >> n;

    int visibles = 0;
    int enPanne = 0;

    for (int i = 0; i <n; ++i) {
        std::string nom;
        // mettons long long pour NK_SS_ALL(4294967295) car il ne tient pas dans un int à 32 bits
        long long drapeaux, sx, sy, sz, distance, lumieres, ambiante, proche;

        std::cin >> nom >> drapeaux >> sx >> sy >> sz >> distance >> lumieres >> ambiante >> proche;

        // distance entre la camera et la face avant du cube sachant que sz est pair
        const long long faceAvant = distance - sz/ 2;

        // causes testées dans l'ordre

        std::string verdict;
        if ((drapeaux & 2) == 0){
            verdict = "RENDER3D ETEINT";
        } else if (sx == 0 || sy ==0 || sz == 0){
            verdict = "ECHELLE NULLE";
        } else if (faceAvant <= 0) {
            verdict = "CAMERA DANS LE CUBE";
        } else if (faceAvant < proche){
            verdict = "DANS LE PLAN PROCHE";
        } else if (lumieres == 0 && ambiante == 0){
            verdict = "PAS DE LUMIERE";
        } else {
            verdict = "VISIBLE";
        }

        std::cout << nom << ' ' << verdict << '\n';

        if(verdict == "VISIBLE"){
            ++visibles;
        } else {
            ++enPanne;
        }
    }
        std::cout << "VISIBLES " << visibles << '\n';
        std::cout << "EN PANNE " << enPanne << '\n';

    return 0;
}
