#include <iostream>  
#include<chrono>
#include<cmath>


int main ()
{
    const int N = 1000000;
    double resultat = 0.0;

    // debut du chronomètrage
    auto debut = std::chrono::high_resolution_clock::now();

    // Calcul lourd 
    for (int i = 1; i <= N; ++i) {
        resultat += std::sqrt(static_cast <double> (i));
    }

    // Fin du chronomètrage 
    auto fin = std::chrono::high_resolution_clock::now();

    // calcul de la durée en millisecondes
    auto duree = std::chrono::duration_cast < std::chrono::milliseconds>(
        fin- debut
    );
    std::cout << "Resultat : " << resultat << std::endl;
    std::cout << "Temps d'exécutoion : " << duree.count() << "ms" << std::endl;

    return 0;
}