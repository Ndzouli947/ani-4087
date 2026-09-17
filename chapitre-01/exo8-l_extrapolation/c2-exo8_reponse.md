## Principe

Le cours l'explique directement : quand on interroge la position d'une
tête, la réponse est déjà légèrement dépassée, et l'image ne sera
affichée que plusieurs millisecondes plus tard. Ce qui compte n'est
donc pas où était la pose, mais où elle sera. C'est le rôle de
l'extrapolation.

La méthode retenue est l'**intégration d'Euler** : on utilise les
vitesses (supposées constantes sur l'intervalle `dt`) pour avancer la
position et l'orientation.

### Partie linéaire

C'est la partie simple: la nouvelle position s'obtient en ajoutant le déplacement parcouru pendant dt à la vitesse linéaire donnée:

nouvelle_pistion = position + vitesse_lineaire * dt 

### Partie angulaire

Une vitesse angulaire est un vecteur dont la **direction** donne l'axe
de rotation et dont la **norme** donne la vitesse de rotation, en
radians par seconde. Pour avancer l'orientation de `dt` secondes, il
faut construire un petit quaternion de rotation « delta » représentant
la rotation accomplie pendant cette durée, puis le combiner à
l'orientation actuelle :

    angle_parcouru = norme(vitesse_angulaire) * dt
    axe = vitesse_angulaire / norme(vitesse_angulaire)
    delta = quaternion(axe, angle_parcouru)
    nouvelle_orientation = normaliser(delta * orientation)

### Code c++


```cpp
#include <iostream>
#include <cmath>

struct Vec3 {
    float x, y, z;

    Vec3 operator+(const Vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vec3 operator*(float s) const { return {x * s, y * s, z * s}; }
    float Length() const { return std::sqrt(x*x + y*y + z*z); }
};

struct Quaternion {
    float w, x, y, z;

    Quaternion operator*(const Quaternion& q) const {
        return {
            w*q.w - x*q.x - y*q.y - z*q.z,
            w*q.x + x*q.w + y*q.z - z*q.y,
            w*q.y - x*q.z + y*q.w + z*q.x,
            w*q.z + x*q.y - y*q.x + z*q.w
        };
    }

    Quaternion Normalise() const {
        float n = std::sqrt(w*w + x*x + y*y + z*z);
        return {w/n, x/n, y/n, z/n};
    }
};

struct Pose {
    Quaternion orientation;
    Vec3 position;
};

// Construit le quaternion delta correspondant a une rotation d'angle
// "angle" (radians) autour de l'axe unitaire "axe".
Quaternion QuaternionDepuisAxeAngle(const Vec3& axe, float angle) {
    float demiAngle = angle / 2.0f;
    float s = std::sin(demiAngle);
    return {std::cos(demiAngle), axe.x * s, axe.y * s, axe.z * s};
}

// Avance une pose de dt secondes, a vitesses lineaire et angulaire
// constantes (integration d'Euler).
Pose Extrapoler(const Pose& pose, const Vec3& vitesseLineaire,
                const Vec3& vitesseAngulaire, float dt) {
    Pose resultat;

    // Partie lineaire : deplacement simple
    resultat.position = pose.position + vitesseLineaire * dt;

    // Partie angulaire : on gere le cas nul AVANT de normaliser l'axe
    float normeAngulaire = vitesseAngulaire.Length();

    Quaternion delta;
    const float epsilon = 1e-6f;

    if (normeAngulaire < epsilon) {
        // Aucune rotation en cours : quaternion identite, pas de
        // division par zero sur un axe qui n'existe pas.
        delta = {1.0f, 0.0f, 0.0f, 0.0f};
    } else {
        float angleParcouru = normeAngulaire * dt;
        Vec3 axe = vitesseAngulaire * (1.0f / normeAngulaire);
        delta = QuaternionDepuisAxeAngle(axe, angleParcouru);
    }

    resultat.orientation = (delta * pose.orientation).Normalise();

    return resultat;
}

int main() {
    Pose pose;
    Vec3 vitesseLineaire, vitesseAngulaire;
    float dt;

    std::cout << "Orientation actuelle (w x y z) : ";
    std::cin >> pose.orientation.w >> pose.orientation.x
             >> pose.orientation.y >> pose.orientation.z;

    std::cout << "Position actuelle (x y z) : ";
    std::cin >> pose.position.x >> pose.position.y >> pose.position.z;

    std::cout << "Vitesse lineaire (x y z, m/s) : ";
    std::cin >> vitesseLineaire.x >> vitesseLineaire.y >> vitesseLineaire.z;

    std::cout << "Vitesse angulaire (x y z, rad/s) : ";
    std::cin >> vitesseAngulaire.x >> vitesseAngulaire.y >> vitesseAngulaire.z;

    std::cout << "Duree dt (secondes) : ";
    std::cin >> dt;

    Pose extrapolee = Extrapoler(pose, vitesseLineaire, vitesseAngulaire, dt);

    std::cout << "\nPose extrapolee :\n";
    std::cout << "Orientation (w x y z) : ("
              << extrapolee.orientation.w << ", " << extrapolee.orientation.x << ", "
              << extrapolee.orientation.y << ", " << extrapolee.orientation.z << ")\n";
    std::cout << "Position (x y z)       : ("
              << extrapolee.position.x << ", " << extrapolee.position.y << ", "
              << extrapolee.position.z << ")\n";

    return 0;
}
```


## Format de l'entrée

Les valeurs sont lues dans l'ordre suivant :

    orientation_w orientation_x orientation_y orientation_z
    position_x position_y position_z
    vitesse_lineaire_x vitesse_lineaire_y vitesse_lineaire_z
    vitesse_angulaire_x vitesse_angulaire_y vitesse_angulaire_z
    dt


## Format de l'entrée

Les valeurs sont lues dans l'ordre suivant :

    orientation_w orientation_x orientation_y orientation_z
    position_x position_y position_z
    vitesse_lineaire_x vitesse_lineaire_y vitesse_lineaire_z
    vitesse_angulaire_x vitesse_angulaire_y vitesse_angulaire_z
    dt


## Exemple d'exécution — cas avec rotation

Entrée : orientation identité, position à l'origine, vitesse linéaire
de 1 m/s sur X, vitesse angulaire de 1 rad/s sur Y, dt = 0,1 s.

    Orientation actuelle (w x y z) : 1 0 0 0
    Position actuelle (x y z) : 0 0 0
    Vitesse lineaire (x y z, m/s) : 1 0 0
    Vitesse angulaire (x y z, rad/s) : 0 1 0
    Duree dt (secondes) : 0.1

    Pose extrapolee :
    Orientation (w x y z) : (0.9988, 0.0000, 0.0500, 0.0000)
    Position (x y z)       : (0.1000, 0.0000, 0.0000)

## Exemple d'exécution — cas sans rotation (vitesse angulaire nulle)

    Orientation actuelle (w x y z) : 1 0 0 0
    Position actuelle (x y z) : 0 0 0
    Vitesse lineaire (x y z, m/s) : 1 0 0
    Vitesse angulaire (x y z, rad/s) : 0 0 0
    Duree dt (secondes) : 0.1

    Pose extrapolee :
    Orientation (w x y z) : (1.0000, 0.0000, 0.0000, 0.0000)
    Position (x y z)       : (0.1000, 0.0000, 0.0000)


### Concluusion

La position avance normalement dans les deux cas, puisque la partie
linéaire ne dépend jamais de la vitesse angulaire. Dans le second cas,
l'orientation reste strictement égale à l'orientation de départ : le
test `normeAngulaire < epsilon` a bien évité de calculer un axe de
rotation à partir d'un vecteur nul, ce qui aurait provoqué une division
par zéro et produit des valeurs invalides (`nan`) dans le quaternion
résultat.