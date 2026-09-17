La pose de chaque articulation dans le monde s'obtient en composant la pose monde de son parent avec sa prpre pose locale, avec le même fonction **compose** 

coude_monde = Compose(epaule_monde, coude_local)
main_monde = Compose(coude_monde, main_local)

C'est une chaîne : la main dépend du coude, qui dépend de l'épaule
Tourner l'épaule change sa pose monde, ce qui change automatiquement la pose maonde du coude, puis celle d elamain sans toucher auxposes locales, qui elles ne bougent jamais

### code C++

```cpp
#include <iostream>
#include <cmath>

struct Vec3 {
    float x, y, z;

    Vec3 operator+(const Vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }
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

    Vec3 Apply(const Vec3& p) const {
        return orientation.Rotate(p) + position;
    }
};

// Compose deux poses : parent d'abord, enfant ensuite (cf exercice precedent)
Pose Compose(const Pose& parent, const Pose& enfant) {
    Pose resultat;
    resultat.orientation = parent.orientation * enfant.orientation;
    resultat.position = parent.orientation.Rotate(enfant.position) + parent.position;
    return resultat;
}

// Construit un quaternion de rotation autour de l'axe Y, angle en radians
Quaternion RotationY(float angleRadians) {
    return {std::cos(angleRadians / 2.0f), 0.0f, std::sin(angleRadians / 2.0f), 0.0f};
}

Quaternion Identite() {
    return {1.0f, 0.0f, 0.0f, 0.0f};
}

void AfficherPose(const std::string& nom, const Pose& p) {
    std::cout << nom << " (monde) : ("
              << p.position.x << ", " << p.position.y << ", " << p.position.z << ")\n";
}

int main() {
    const float longueurBras = 0.30f;      // 30 cm, epaule -> coude
    const float longueurAvantBras = 0.25f; // 25 cm, coude -> main

    // Poses locales : chacune exprimee dans le repere de son parent.
    // Elles ne changent jamais, meme quand l'epaule tourne.
    Pose epaule_local{Identite(), {0.0f, 0.0f, 0.0f}};
    Pose coude_local{Identite(), {longueurBras, 0.0f, 0.0f}};
    Pose main_local{Identite(), {longueurAvantBras, 0.0f, 0.0f}};

    std::cout << " Bras au repos (epaule sans rotation) \n";

    // L'epaule est la racine : sa pose monde est sa pose locale
    Pose epaule_monde = epaule_local;
    Pose coude_monde = Compose(epaule_monde, coude_local);
    Pose main_monde = Compose(coude_monde, main_local);

    AfficherPose("Coude", coude_monde);
    AfficherPose("Main ", main_monde);

    std::cout << "\n Bras avec l'epaule tournee de 90 degres (axe Y) \n";

    // On fait tourner uniquement l'epaule. Les poses locales du coude
    // et de la main restent identiques : c'est la chaine de composition
    // qui propage la rotation.
    float angle90 = 3.14159265f / 2.0f;
    epaule_local.orientation = RotationY(angle90);

    epaule_monde = epaule_local;
    coude_monde = Compose(epaule_monde, coude_local);
    main_monde = Compose(coude_monde, main_local);

    AfficherPose("Coude", coude_monde);
    AfficherPose("Main ", main_monde);

    return 0;
}
```

### Résulats obtenu 

Bras au repos (épaule sans rotation)
Coude (monde) : (0.30, 0, 0)
Main(monde) : (0.55, 0, 0)

Bras avec l'épaule tournée de 90 dégres (axe Y) 
Coude (monde) : (0, 0, -0.30)
Main (monde) : (0, 0, -0.55)

### Vérification et conclusion 

Au repos, le bras est aligné qur l'axe X: le coude est à 0,30m de l'épaule, la main à 0,55m 
Après avoir tourné uniquement le coude l'épaule de 90 dégrès autour de l'axe Y, le coude et lamain se trouvent alignés sur l'axe -Z, à la même distance de l'origine qu'avant, simplement dans une direction differentes. Ni la pose locale du coude ni celle de la main n'ont été modifiées.

Cela confirme la propriété énoncé : faire tournerun parent fait suivre tous ses enfants, sans qu'il soit nécessaire de leur donner l'ordre individuellement.