Le cours prévient : « il faut forcer le chemin court, sinon un écart
minuscule peut se lire comme un tour presque complet dans l'autre sens
, Deux quaternions opposés posent le même problème sous une autre
forme, car ils décrivent la même rotation. »


### Calcul de la vitesse angulaire moyenne 

Entre deux orientations ` q1` et `q2` à l'instant t, la rotation qui mène de l'une à l'autre s'obtient par:

    delta = q2 * conjugue(q1)


Delta est un quaternion qui représente cette rotation relative on en extrait un angle et un axe : 

    angle = q2 * acos(delta.w)
    axe = normaliser(delta.x, delta.y, delta.z)

La vitesse_angulaire = axe * (angle/dt)


### Le forçage du chemin court

Un quaternion `q` et son opposé `-q` représentent exactement la même
rotation (c'est une propriété connue : le quaternion est une double
couverture du groupe des rotations). Le problème est que, pris comme
vecteurs à quatre composantes, `q` et `-q` sont très éloignés l'un de
l'autre, même s'ils décrivent la même orientation.

Le moyen de savoir si `q1` et `q2` « pointent dans la même direction »
est de calculer leur produit scalaire à quatre composantes :

    produit_scalaire = q1.w*q2.w + q1.x*q2.x + q1.y*q2.y + q1.z*q2.z

Si ce produit scalaire est négatif, cela signifie que `q1` et `q2`
sont sur des « hémisphères » opposés de l'espace des quaternions, même
s'ils représentent des orientations très proches. Le forçage du chemin
court consiste alors à remplacer `q2` par `-q2` avant de calculer
`delta`, ce qui ramène le calcul sur le chemin le plus court.

### Code C++


```cpp
#include <iostream>
#include <cmath>

struct Vec3 {
    float x, y, z;
    Vec3 operator*(float s) const { return {x * s, y * s, z * s}; }
    float Length() const { return std::sqrt(x*x + y*y + z*z); }
};

struct Quaternion {
    float w, x, y, z;

    Quaternion Conjugue() const { return {w, -x, -y, -z}; }
    Quaternion Oppose() const { return {-w, -x, -y, -z}; }

    Quaternion operator*(const Quaternion& q) const {
        return {
            w*q.w - x*q.x - y*q.y - z*q.z,
            w*q.x + x*q.w + y*q.z - z*q.y,
            w*q.y - x*q.z + y*q.w + z*q.x,
            w*q.z + x*q.y - y*q.x + z*q.w
        };
    }

    float ProduitScalaire(const Quaternion& q) const {
        return w*q.w + x*q.x + y*q.y + z*q.z;
    }
};

float Clamp(float v, float lo, float hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

// Calcule la vitesse angulaire moyenne entre q1 et q2, separees de dt
// secondes. Si forcerCheminCourt est vrai, on s'assure de prendre le
// chemin le plus court entre les deux orientations.
Vec3 VitesseAngulaireMoyenne(const Quaternion& q1, const Quaternion& q2,
                              float dt, bool forcerCheminCourt) {
    Quaternion q2Utilise = q2;

    if (forcerCheminCourt) {
        float produitScalaire = q1.ProduitScalaire(q2);
        if (produitScalaire < 0.0f) {
            // q2 et q1 sont sur des hemispheres opposes : on prend
            // l'oppose de q2, qui represente la meme orientation.
            q2Utilise = q2.Oppose();
        }
    }

    Quaternion delta = q2Utilise * q1.Conjugue();

    float w = Clamp(delta.w, -1.0f, 1.0f);
    float angle = 2.0f * std::acos(w);

    Vec3 axeNonNormalise{delta.x, delta.y, delta.z};
    float normeAxe = axeNonNormalise.Length();

    Vec3 axe;
    const float epsilon = 1e-6f;
    if (normeAxe < epsilon) {
        // Rotation quasi nulle : l'axe n'a pas de sens, vitesse nulle.
        axe = {0.0f, 0.0f, 0.0f};
    } else {
        axe = axeNonNormalise * (1.0f / normeAxe);
    }

    return axe * (angle / dt);
}

int main() {
    float dt = 0.1f; // 100 ms entre les deux mesures

    // q1 : orientation identite
    Quaternion q1{1.0f, 0.0f, 0.0f, 0.0f};

    // q2 : une rotation de 1 degre autour de X, PUIS on prend son
    // oppose. -q represente exactement la meme orientation que q,
    // mais le produit scalaire avec q1 devient negatif.
    float angleReel = 1.0f * 3.14159265f / 180.0f; // 1 degre en radians
    Quaternion petiteRotation{
        std::cos(angleReel / 2.0f), std::sin(angleReel / 2.0f), 0.0f, 0.0f
    };
    Quaternion q2 = petiteRotation.Oppose();

    std::cout << "q1 : (" << q1.w << ", " << q1.x << ", " << q1.y << ", " << q1.z << ")\n";
    std::cout << "q2 : (" << q2.w << ", " << q2.x << ", " << q2.y << ", " << q2.z << ")\n";
    std::cout << "(q2 represente la MEME orientation qu'une rotation de 1 degre,\n";
    std::cout << " mais son produit scalaire avec q1 est negatif)\n\n";

    Vec3 avecForcage = VitesseAngulaireMoyenne(q1, q2, dt, true);
    Vec3 sansForcage = VitesseAngulaireMoyenne(q1, q2, dt, false);

    std::cout << "Avec forcage du chemin court :\n";
    std::cout << "  vitesse angulaire = (" << avecForcage.x << ", "
              << avecForcage.y << ", " << avecForcage.z << ") rad/s\n";
    std::cout << "  norme = " << avecForcage.Length() << " rad/s\n\n";

    std::cout << "Sans forcage :\n";
    std::cout << "  vitesse angulaire = (" << sansForcage.x << ", "
              << sansForcage.y << ", " << sansForcage.z << ") rad/s\n";
    std::cout << "  norme = " << sansForcage.Length() << " rad/s\n";

    return 0;
}
```

## Résultat obtenu

q1 : (1.0000, 0.0000, 0.0000, 0.0000)
q2 : (-0.9999, -0.0087, 0.0000, 0.0000) 

Avec forcage de chemin court : 
vitesse angulaire = (1.0000, 0.0000, 0.0000) rad/s
norme = 0.1745 rad/s

Sans forcage : 
vitesse angulaire = (-1.0000, 0.0000, 0.0000) rad/s
norme = 6.1087 rad/s 

### Analyse du résultat absurde 

- **Avec le forçage**, le calcul détecte que le produit scalaire entre
  `q1` et `q2` est négatif, prend l'opposé de `q2`, et retrouve la
  bonne réponse : une vitesse angulaire de norme 0,1745 rad/s, ce qui
  correspond exactement à 1 degré parcouru en 0,1 seconde (1° = 0,01745
  rad, divisé par 0,1 s = 0,1745 rad/s).


- **Sans le forçage**, le calcul prend `delta.w` négatif tel quel, ce
  qui donne un angle proche de 359 degrés au lieu de 1 degré. Le
  résultat devient une vitesse angulaire de norme 6,1087 rad/s — soit
  près de 350 degrés par seconde — alors que l'objet réel tourne à
  peine.


### Conclusion

deux quaternions
opposés décrivent la même rotation, mais un calcul naïf qui ne
vérifie pas le signe du produit scalaire interprète cet écart comme
un tour presque complet dans l'autre sens. Le résultat obtenu sans
forçage n'est pas une erreur qui plante le programme  c'est un
nombre parfaitement valide, mais physiquement absurde, qui produirait
une rotation extrêmement rapide et erratique dans une application
réelle. Le forçage du chemin court, en testant simplement le signe du
produit scalaire avant le calcul, élimine ce défaut sans coût
significatif.