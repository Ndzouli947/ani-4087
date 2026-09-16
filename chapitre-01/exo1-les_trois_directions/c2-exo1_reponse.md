Convention utilisée

Fonction

	

Vecteur retourné

	

Signification




Avant()

	

(0, 0, -1)

	

Direction avant




Haut()

	

(0, 1, 0)

	

Direction verticale positive




Droite()

	

(1, 0, 0)

	

Direction horizontale droite

Chaque vecteur est unitaire, car sa norme vaut 1.

#include <iostream>
#include <iomanip>
#include <cmath>

struct Vecteur3
{
    double x;
    double y;
    double z;
};

// Direction avant : axe Z négatif
Vecteur3 Avant()
{
    return {0.0, 0.0, -1.0};
}

// Direction vers le haut : axe Y positif
Vecteur3 Haut()
{
    return {0.0, 1.0, 0.0};
}

// Direction vers la droite : axe X positif
Vecteur3 Droite()
{
    return {1.0, 0.0, 0.0};
}

// Produit scalaire entre deux vecteurs
double ProduitScalaire(const Vecteur3& a, const Vecteur3& b)
{
    return a.x * b.x
         + a.y * b.y
         + a.z * b.z;
}

int main()
{
    Vecteur3 point;

    // Lecture des trois coordonnées du point
    std::cin >> point.x >> point.y >> point.z;

    // Affichage avec quatre chiffres après la virgule
    std::cout << std::fixed << std::setprecision(4);

    std::cout << ProduitScalaire(point, Avant()) << '\n';
    std::cout << ProduitScalaire(point, Haut()) << '\n';
    std::cout << ProduitScalaire(point, Droite()) << '\n';

    return 0;
}

Explication du résultat

Soit un point :

P=(x,y,z)

Le produit scalaire avec chaque direction donne :

P⋅Avant()=−z
P⋅Haut()=y
P⋅Droite()=x

Le programme affiche donc, dans l’ordre :

la composante du point vers l’avant ;

sa composante verticale ;

sa composante vers la droite.

Conclusion

Les fonctions Avant(), Haut() et Droite() fixent la convention du module à un seul endroit. Le reste du programme peut donc utiliser ces fonctions sans avoir à se souvenir des signes des axes. Cela évite notamment de confondre l’avant avec l’arrière, puisque dans cette convention l’avant correspond à la direction Z négatif.