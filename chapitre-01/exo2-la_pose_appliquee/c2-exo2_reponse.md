### Rappel 

UNe pose est composée de deux éléments:
- une position;
- une orientation représentée par un quaternion

L'application d'une pose à un point suit la formule:

p_espace = orientation * p_entite + position

La rotation doit donc être effectuée avant la translation.


## Code C++

```cpp
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

// Application d'une rotation quaternion à un point 3D
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

// Application d'une pose à un point : rotation puis translation
Vecteur3 AppliquerPose(const Pose& pose, const Vecteur3& point)
{
    // Première étape : rotation du point
    Vecteur3 pointTourne =
        Rotationner(pose.orientation, point);

    // Deuxième étape : translation du point
    Vecteur3 pointTransforme =
    {
        pointTourne.x + pose.position.x,
        pointTourne.y + pose.position.y,
        pointTourne.z + pose.position.z
    };

    return pointTransforme;
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

    // Lecture du point à transformer
    cin >> point.x
        >> point.y
        >> point.z;

    // Application de la pose au point
    Vecteur3 resultat = AppliquerPose(pose, point);

    // Affichage avec quatre décimales
    cout << fixed << setprecision(4);

    cout << resultat.x << endl;
    cout << resultat.y << endl;
    cout << resultat.z << endl;

    return 0;
}

```
### Format de l'entrée
les valeurs sont lues dans l'ordre suivant:
position_x position_y position_z
quaternion_x quaternion_y quaternion_z quaternion_w
point_x point_y point_z

### Conclusion

LA fonction AppliquerPose() applique correctement une pose à un point en respectant l'ordre: Rotatio ensuite Translation.

D'où la formule finale est p_espace = orientation * p_entite + position