## Rappel théorique

Une pose est définie par :


Pose = (position, orientation)


L’application d’une pose à un point est :


p_{espace} = R(p) + T


où :

- (R) représente la rotation ;
- (T) représente la translation.

Pour annuler cette transformation, il faut appliquer la transformation inverse :

p_ = R^{-1}(p_{espace} - T)


Le quaternion étant normalisé, l’inverse de sa rotation est donné par son **conjugué**.

## Conjugué d’un quaternion

Soit un quaternion :


q = (x,y,z,w)


Son conjugué est :


q^* = (-x,-y,-z,w)

Le signe des trois composantes vectorielles est inversé, tandis que la composante scalaire w reste inchangée.

### position de la pose inverse

La position inverse est calculée en deux étapes:
1. on prend la position opposée:

-T = (-T_x,-T_y,-T_z)


2. on tourne cette positon opposée avec le conjugué:

T_{inverse} = R^{-1}(-T)


La pose inverse est donc: 

Pose^-{1} = R^-{1}(-T),R^-{1}

### code
```
#include <iostream>
#include <iomanip>
#include <cmath>

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

// Additionne deux vecteurs
Vecteur3 Additionner(const Vecteur3& a, const Vecteur3& b)
{
    return {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

// Retourne le vecteur opposé
Vecteur3 Oppose(const Vecteur3& v)
{
    return {
        -v.x,
        -v.y,
        -v.z
    };
}

// Calcule le conjugué d'un quaternion
Quaternion Conjugue(const Quaternion& q)
{
    return {
        -q.x,
        -q.y,
        -q.z,
        q.w
    };
}

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

    // Formule de rotation pour un quaternion normalisé :
    // p' = p + w * t + (u × t)
    Vecteur3 resultat =
    {
        p.x + q.w * t.x + (u.y * t.z - u.z * t.y),
        p.y + q.w * t.y + (u.z * t.x - u.x * t.z),
        p.z + q.w * t.z + (u.x * t.y - u.y * t.x)
    };

    return resultat;
}

// Applique une pose à un point : rotation puis translation
Vecteur3 AppliquerPose(
    const Pose& pose,
    const Vecteur3& point)
{
    // Étape 1 : rotation du point
    Vecteur3 pointTourne =
        Rotationner(pose.orientation, point);

    // Étape 2 : translation
    return Additionner(pointTourne, pose.position);
}

// Calcule l'inverse d'une pose
Pose Inverser(const Pose& pose)
{
    Pose inverse;

    // 1. L'inverse de la rotation est le conjugué
    inverse.orientation = Conjugue(pose.orientation);

    // 2. On prend la position opposée
    Vecteur3 positionOpposee = Oppose(pose.position);

    // 3. On tourne la position opposée avec le conjugué
    inverse.position =
        Rotationner(inverse.orientation, positionOpposee);

    return inverse;
}

// Calcule la différence entre deux vecteurs
Vecteur3 Difference(
    const Vecteur3& a,
    const Vecteur3& b)
{
    return {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

// Calcule la norme d'un vecteur
double Norme(const Vecteur3& v)
{
    return sqrt(
        v.x * v.x +
        v.y * v.y +
        v.z * v.z
    );
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

    // Application de la pose au point
    Vecteur3 pointTransforme =
        AppliquerPose(pose, point);

    // Calcul de la pose inverse
    Pose poseInverse = Inverser(pose);

    // Application de la pose inverse au résultat
    Vecteur3 pointRetrouve =
        AppliquerPose(poseInverse, pointTransforme);

    // Calcul de l'écart entre le point initial et le point retrouvé
    Vecteur3 ecart =
        Difference(pointRetrouve, point);

    double erreur = Norme(ecart);

    // Affichage des résultats
    cout << fixed << setprecision(4);

    cout << "Point transforme : "
         << pointTransforme.x << " "
         << pointTransforme.y << " "
         << pointTransforme.z << endl;

    cout << "Point retrouve : "
         << pointRetrouve.x << " "
         << pointRetrouve.y << " "
         << pointRetrouve.z << endl;

    cout << "Ecart : "
         << erreur << endl;

    return 0;
} 
```

Le programme lit les valeurs dans l’ordre suivant :

position_x position_y position_z
quaternion_x quaternion_y quaternion_z quaternion_w
point_x point_y point_z

Exemple d'éxecution

Entrée 
(1 2 3)

(0 0 0 1)

(4 5 6)

Le quaternion (0, 0, 0, 1) représente une rotation nulle.

### Application d ela pose
Le point est simplement translaté:

        p_transforme = (4, 5, 6) + (1, 2, 3)
        p_transforme = (5, 7,9)

### Calcul de l'inverse
Le conjugué du quaternion est identique: 
    q* = (0, 0, 0, 0)

La position opposée est: 
    -T = (-1, -2, -3)

comme la rotation inverse est nulle:
    T_inverse = (5, 7, 9) + (-1, -2, -3)

### Application de la pose inverse
    p_inverse = (5, 7, 9)
    p_inverse = (4, 5, 6)

### Sortie
point transforme: (5, 7, 9)
point inverse: (4, 5, 6)
Ecart : 0

L'écart doit être nul car la pose annule les deux opérations de la pose initiale:
La rotation inverse annule la rotation initiale;
La translation inverse annule la translation initiale.

Mathématiquement: 

    Pose−1(Pose(p))=p

En pratique, les calculs utilisent des nombres flottants. il peut donc apparaître une petite erreur numérique.

### Conclusion
L'inverse d'une pose ne consiste pas simplemenmt à changer le signe de sa position. il faut également tenir compte de l'orientation: 
    q-1 = q*  et T-1 = R-1(-T)

    ainsi, la pose inverse devient   

    Pose-1 = (R-1(-T),q*)
