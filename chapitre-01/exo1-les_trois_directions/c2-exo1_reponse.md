# Exercice : Convention des directions et produit scalaire

## Énoncé

Écrivez les trois fonctions qui fixent la convention une fois pour toutes :

- `Avant()`
- `Haut()`
- `Droite()`

Chaque fonction doit retourner un vecteur unitaire correspondant à la convention du module.

Le programme lit trois réels, les traite comme les coordonnées d’un point, puis affiche son produit scalaire avec chacune des trois directions.

L’affichage doit comporter trois lignes avec quatre décimales.

## Convention utilisée

D’après le chapitre 2, le repère utilisé est un repère direct, aussi appelé repère main droite :

- L’axe `+X` représente la droite ;
- L’axe `+Y` représente le haut ;
- L’avant correspond à la direction `-Z`.

Les trois vecteurs unitaires sont donc :

\[
Avant() = (0, 0, -1)
\]

\[
Haut() = (0, 1, 0)
\]

\[
Droite() = (1, 0, 0)
\]

## Code C++

```cpp
#include <iostream>
#include <iomanip>

using namespace std;

// Structure représentant un vecteur dans l'espace 3D
struct Vecteur3
{
    double x;
    double y;
    double z;
};

// Retourne le vecteur unitaire représentant l'avant
Vecteur3 Avant()
{
    return {0.0, 0.0, -1.0};
}

// Retourne le vecteur unitaire représentant le haut
Vecteur3 Haut()
{
    return {0.0, 1.0, 0.0};
}

// Retourne le vecteur unitaire représentant la droite
Vecteur3 Droite()
{
    return {1.0, 0.0, 0.0};
}

// Calcule le produit scalaire de deux vecteurs
double ProduitScalaire(const Vecteur3& a, const Vecteur3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

int main()
{
    Vecteur3 point;

    // Lecture des coordonnées du point
    cin >> point.x >> point.y >> point.z;

    // Configuration de l'affichage avec quatre décimales
    cout << fixed << setprecision(4);

    // Affichage du produit scalaire avec chaque direction
    cout << ProduitScalaire(point, Avant()) << endl;
    cout << ProduitScalaire(point, Haut()) << endl;
    cout << ProduitScalaire(point, Droite()) << endl;

    return 0;
}
 ```

Explication

Le produit scalaire de deux vecteurs est défini par :

a
⋅
b
=a
x
b
x
+a
y
b
y
+a
z
b
z
	​

Pour un point :

P=(x,y,z)

on obtient :

Produit scalaire avec l’avant
P⋅Avant()=(x,y,z)⋅(0,0,−1)=−z
Produit scalaire avec le haut
P⋅Haut()=(x,y,z)⋅(0,1,0)=y
Produit scalaire avec la droite
P⋅Droite()=(x,y,z)⋅(1,0,0)=x

Ainsi, le programme affiche respectivement :

La composante opposée à z ;

La composante y ;

La composante x.

Conclusion

Les fonctions Avant(), Haut() et Droite() permettent de fixer clairement la convention du repère. Le produit scalaire avec ces vecteurs permet ensuite d’extraire les composantes du point selon les directions du module.Conclusion

Les fonctions Avant(), Haut() et Droite() permettent de fixer clairement la convention du repère. Le produit scalaire avec ces vecteurs permet ensuite d’extraire les composantes du point selon les directions du module.
