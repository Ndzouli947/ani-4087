Une pose décrit la manière dont un objet est placé dans l’espace.

Elle contient deux informations :

Pose=(position,orientation)

Position : indique où se trouve l’objet.

Orientation : indique comment l’objet est tourné.

### Première transformation : rotation puis translation
La formule est p_espace = orientation * p_entite + position

si on note :
p: le point initial;
R: la rotation;
T: la translation
alors : p1 = R(p) + T

### Deuxième transformation : translation puis rotation 
p_espace = orientation * (p_entite+position)

Avec les mêmes notations: p2 = R(p+T)

En génarale, ces deux transformations ne donnet pas le même résultat, car la rotation et la translation ne sont pas commutatives

### Code c++

``` cpp

#include <iostream>
#include <iomanip>

using namespace std;

// Structure représentant un vecteur 3D
struct Vecteur3
{
    double x;
    double y;
    double z;
};

// Structure représentant un quaternion
struct Quaternion
{
    double x;
    double y;
    double z;
    double w;
};

// Structure représentant une pose
struct Pose
{
    Vecteur3 position;
    Quaternion orientation;
};

// Applique une rotation quaternion à un point 3D
Vecteur3 Rotationner(const Quaternion& q, const Vecteur3& p)
{
    // Partie vectorielle du quaternion
    Vecteur3 u = {q.x, q.y, q.z};

    // Calcul de t = 2 * (u × p)
    Vecteur3 t =
    {
        2.0 * (u.y * p.z - u.z * p.y),
        2.0 * (u.z * p.x - u.x * p.z),
        2.0 * (u.x * p.y - u.y * p.x)
    };

    // Formule de rotation :
    // p' = p + w * t + (u × t)
    Vecteur3 resultat =
    {
        p.x + q.w * t.x + (u.y * t.z - u.z * t.y),
        p.y + q.w * t.y + (u.z * t.x - u.x * t.z),
        p.z + q.w * t.z + (u.x * t.y - u.y * t.x)
    };

    return resultat;
}

// Additionne deux vecteurs
Vecteur3 Additionner(const Vecteur3& a, const Vecteur3& b)
{
    return {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

// Fonction 1 : rotation puis translation
Vecteur3 AppliquerPoseRotationPuisTranslation(
    const Pose& pose,
    const Vecteur3& point)
{
    // Étape 1 : rotation
    Vecteur3 pointTourne =
        Rotationner(pose.orientation, point);

    // Étape 2 : translation
    Vecteur3 resultat =
        Additionner(pointTourne, pose.position);

    return resultat;
}

// Fonction 2 : translation puis rotation
Vecteur3 AppliquerPoseTranslationPuisRotation(
    const Pose& pose,
    const Vecteur3& point)
{
    // Étape 1 : translation
    Vecteur3 pointTranslate =
        Additionner(point, pose.position);

    // Étape 2 : rotation
    Vecteur3 resultat =
        Rotationner(pose.orientation, pointTranslate);

    return resultat;
}

// Affiche un vecteur sur une seule ligne
void AfficherVecteur(const Vecteur3& v)
{
    cout << fixed << setprecision(4)
         << v.x << " "
         << v.y << " "
         << v.z << endl;
}

int main()
{
    Pose pose;
    Vecteur3 point;

    // Lecture de la position de la pose
    cin >> pose.position.x
        >> pose.position.y
        >> pose.position.z;

    // Lecture du quaternion : x, y, z, w
    cin >> pose.orientation.x
        >> pose.orientation.y
        >> pose.orientation.z
        >> pose.orientation.w;

    // Lecture du point
    cin >> point.x
        >> point.y
        >> point.z;

    // Calcul des deux transformations
    Vecteur3 resultat1 =
        AppliquerPoseRotationPuisTranslation(pose, point);

    Vecteur3 resultat2 =
        AppliquerPoseTranslationPuisRotation(pose, point);

    // Affichage des résultats
    cout << "Rotation puis translation : ";
    AfficherVecteur(resultat1);

    cout << "Translation puis rotation : ";
    AfficherVecteur(resultat2);

    return 0;
}
```

Format de l’entrée

Le programme lit les valeurs dans l’ordre suivant :

position_x position_y position_z
quaternion_x quaternion_y quaternion_z quaternion_w
point_x point_y point_z

exemple où les résultats sont différents
Entrée
1 0 0
0 0 0.7071068 0.7071068
1 0 0

Le quaternion représente une rotation de 90 degrés autour de l’axe Z.

### Rotation puis translation
Le point (1, 0, 0) devient (0, 1, 0) après rotation.
Puis on ajoute la translation (1, 0, 0): 
        p1 = (0, 1, 0) + (1, 0, 0)
        p1 = (1, 1, 0)

### transaltion puis rotation 
on translate d'abord le piont:
        (1, 0, 0) + (1, 0, 0) = (2, 0, 0)
    
Puis on apllique la ratation de 90 dégrés autour de z : 
        p2 = (0, 2, 0) 

Les deux résultats sont différents

Cas où les résultats coïncident

Choisissons une pose sans rotation :

1 2 3
0 0 0 1
4 5 6

Le quaternion (0, 0, 0, 1) représente l’identité : il ne modifie pas le point.

### Rotation puis translation
p1 = p + position

p1 = (4, 5, 6) + (1, 2, 3)

p1 = (5, 7, 9)

### translation puis rotation
la translation donne: 
p + position = (5, 7, 9)

La rotation est nulles donc le point este inchangé:
p2 = (5, 7, 9)

Les résultats cïncident parce que le quaternion représente une rotaion nulle.
La rotation est donc l'identité : R(p) = p
ainsi : R(p) + T = p + T et R(p + T) = p + T

### Conclusion 
L'ordre des transformations est important:
- Rotation puis transformation :  p1 = R(p) + T
- Traslation puis rotation :  p2 = R(p + T)