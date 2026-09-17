Une pose transforme un point selon la fromule suivante : 
p_espace = orientation * p_entite + position 

Composer deux poses (un parent P et un enfant E) consiste à trouver une pose unique C qui produit , en une seule application, le même résultat que d'appliquer d'abord E puis P sur le résultat obtenu

En partant de la définition on applique d'abord E à un point p, puis P au résultat

étape_1 = E.orientation * p + E.position 
étape_2 = P.orientation * etape_1 + P.position

En developpant l'étape_2 on a: 
etape_2 = P.orientation * (E.orientation * p + E.position) + P.position
        = (P.orientation * E.orientation)*p + (P.orientation * E.position + P.position)

On reconnait la forme d'une pose unique appliquée à p, avec:

C.orientation = P.orientation * E.orientation

C.position = P.orientation * E.posiotn + P.position

C'est la définition de la composition: la rotation est le produit des deux rotations, et la position composée est la positoinde l'enfant tournée par le parent, puis décalée par la position du parent.

```cpp
#include <iostream>
#include <cmath>

struct Vec3 {
    float x, y, z;

    Vec3 operator+(const Vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vec3 operator-(const Vec3& v) const { return {x - v.x, y - v.y, z - v.z}; }
    float Length() const { return std::sqrt(x*x + y*y + z*z); }
};

struct Quaternion {
    float w, x, y, z;

    // Multiplication de deux quaternions : compose deux rotations
    Quaternion operator*(const Quaternion& q) const {
        return {
            w*q.w - x*q.x - y*q.y - z*q.z,
            w*q.x + x*q.w + y*q.z - z*q.y,
            w*q.y - x*q.z + y*q.w + z*q.x,
            w*q.z + x*q.y - y*q.x + z*q.w
        };
    }

    // Applique la rotation à un point via q * v * conjugue(q)
    Vec3 Rotate(const Vec3& v) const {
        Quaternion qv{0, v.x, v.y, v.z};
        Quaternion conj{w, -x, -y, -z};
        Quaternion result = (*this) * qv * conj;
        return {result.x, result.y, result.z};
    }
};

struct Pose {
    Quaternion orientation;
    Vec3 position;

    // Applique la formule du cours : p_espace = orientation * p_entite + position
    Vec3 Apply(const Vec3& p) const {
        return orientation.Rotate(p) + position;
    }
};

// Compose deux poses : appliquer Compose(parent, enfant) a un point
// doit donner le meme resultat que appliquer enfant puis parent separement.
Pose Compose(const Pose& parent, const Pose& enfant) {
    Pose resultat;
    resultat.orientation = parent.orientation * enfant.orientation;
    resultat.position = parent.orientation.Rotate(enfant.position) + parent.position;
    return resultat;
}

int main() {
    // Pose parente : rotation de 90 degres autour de Y, decalee de 2m sur X
    float angle = 3.14159265f / 2.0f;
    Quaternion rotationParent{std::cos(angle / 2.0f), 0.0f, std::sin(angle / 2.0f), 0.0f};
    Pose parent{rotationParent, {2.0f, 0.0f, 0.0f}};

    // Pose enfant : aucune rotation, decalee de 1m sur Z
    Quaternion rotationEnfant{1.0f, 0.0f, 0.0f, 0.0f}; // quaternion identite
    Pose enfant{rotationEnfant, {0.0f, 0.0f, 1.0f}};

    // Point de test, exprime dans le repere de l'enfant
    Vec3 point{1.0f, 0.0f, 0.0f};

    // Methode 1 : composer les deux poses, puis appliquer la pose composee
    Pose composee = Compose(parent, enfant);
    Vec3 resultat1 = composee.Apply(point);

    // Methode 2 : appliquer l'enfant, puis appliquer le parent sur le resultat
    Vec3 pointDansParent = enfant.Apply(point);
    Vec3 resultat2 = parent.Apply(pointDansParent);

    // Ecart entre les deux methodes
    Vec3 diff = resultat1 - resultat2;
    float ecart = diff.Length();

    std::cout << "Resultat 1 (pose composee)          : ("
              << resultat1.x << ", " << resultat1.y << ", " << resultat1.z << ")\n";
    std::cout << "Resultat 2 (application successive) : ("
              << resultat2.x << ", " << resultat2.y << ", " << resultat2.z << ")\n";
    std::cout << "Ecart entre les deux methodes        : " << ecart << "\n";

    return 0;
}
```

### Résultats obtenu
Resulat 1 (pose composée): (2, 0, 3)
Résultat 2 (application successive): (2, 0, 3)
Ecart entre les deux méthodes: 0

### Conclusion 
Les deux méthodes donnent le même point, avec un écart nul. cela confirme que composer deux poses puis appliquer le résultat produit exactement le même effet qu'appliquer les poses séparement, dans l'ordre enfant puis parent ce qui valide la formule plus haut.