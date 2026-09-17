Le cours rappelle qu'une pose peut être représentée sous la forme d'une matrice 4x4, composée d'une rotation et d'une translation. Pour obtenir la matrice de vue c'est-à-dire la positon du monde vue depsui un point donné il faut inverser cette matrice.

Pour une pose, la transformation d'un point s'écrit:

y = orientation * x + position

inverser cette relation pour trouver x à partir de y donne :

x = orientation^-1 * (y-position)
x = orientation^-1 * y - orientation^-1 * position

les deux propriétés rendent le calcul simple:

- l'inverse d'une rotation representée par un quaternion unitaireest son conjugué;

- la position inverse s'obtient donc en prenant la translation opposé et en la faisant tourner par cette rotation inverse

### code c++

## Code C++

```
#include <iostream>
#include <cmath>
#include <iomanip>

struct Vec3 {
    float x, y, z;
};

struct Quaternion {
    float w, x, y, z;

    Quaternion Conjugue() const { return {w, -x, -y, -z}; }

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
        Quaternion r = (*this) * qv * Conjugue();
        return {r.x, r.y, r.z};
    }
};

struct Pose {
    Quaternion orientation;
    Vec3 position;
};

// Matrice 4x4 stockee ligne par ligne (16 coefficients)
struct Mat4 {
    float m[16];

    void Print(const std::string& nom) const {
        std::cout << nom << " :\n" << std::fixed << std::setprecision(4);
        for (int ligne = 0; ligne < 4; ligne++) {
            for (int col = 0; col < 4; col++) {
                std::cout << std::setw(9) << m[ligne * 4 + col] << " ";
            }
            std::cout << "\n";
        }
    }
};

// Construit la matrice 4x4 d'une pose : rotation derivee du quaternion,
// translation en derniere colonne.
Mat4 PoseVersMatrice(const Pose& p) {
    const Quaternion& q = p.orientation;
    Mat4 mat{};

    mat.m[0] = 1 - 2*(q.y*q.y + q.z*q.z);
    mat.m[1] = 2*(q.x*q.y - q.z*q.w);
    mat.m[2] = 2*(q.x*q.z + q.y*q.w);
    mat.m[3] = p.position.x;

    mat.m[4] = 2*(q.x*q.y + q.z*q.w);
    mat.m[5] = 1 - 2*(q.x*q.x + q.z*q.z);
    mat.m[6] = 2*(q.y*q.z - q.x*q.w);
    mat.m[7] = p.position.y;

    mat.m[8]  = 2*(q.x*q.z - q.y*q.w);
    mat.m[9]  = 2*(q.y*q.z + q.x*q.w);
    mat.m[10] = 1 - 2*(q.x*q.x + q.y*q.y);
    mat.m[11] = p.position.z;

    mat.m[12] = 0; mat.m[13] = 0; mat.m[14] = 0; mat.m[15] = 1;

    return mat;
}

// VERSION 1 : inversion generale par cofacteurs (methode classique,
// ne sait rien de la structure "pose" de la matrice) 
Mat4 InversionGenerale(const Mat4& m) {
    const float* a = m.m;
    Mat4 inv{};
    float d[16];

    d[0]  =  a[5]*a[10]*a[15] - a[5]*a[11]*a[14] - a[9]*a[6]*a[15] + a[9]*a[7]*a[14] + a[13]*a[6]*a[11] - a[13]*a[7]*a[10];
    d[4]  = -a[4]*a[10]*a[15] + a[4]*a[11]*a[14] + a[8]*a[6]*a[15] - a[8]*a[7]*a[14] - a[12]*a[6]*a[11] + a[12]*a[7]*a[10];
    d[8]  =  a[4]*a[9]*a[15]  - a[4]*a[11]*a[13] - a[8]*a[5]*a[15] + a[8]*a[7]*a[13] + a[12]*a[5]*a[11] - a[12]*a[7]*a[9];
    d[12] = -a[4]*a[9]*a[14]  + a[4]*a[10]*a[13] + a[8]*a[5]*a[14] - a[8]*a[6]*a[13] - a[12]*a[5]*a[10] + a[12]*a[6]*a[9];

    float det = a[0]*d[0] + a[1]*d[4] + a[2]*d[8] + a[3]*d[12];

    // GARDE-FOU CLASSIQUE : si le determinant est (quasi) nul, on ne
    // peut pas inverser -> on renvoie l'identite SANS RIEN SIGNALER.
    // C'est exactement le piege decrit dans le cours.
    if (std::fabs(det) < 1e-8f) {
        Mat4 identite{};
        identite.m[0] = identite.m[5] = identite.m[10] = identite.m[15] = 1.0f;
        return identite;
    }

    d[1]  = -a[1]*a[10]*a[15] + a[1]*a[11]*a[14] + a[9]*a[2]*a[15] - a[9]*a[3]*a[14] - a[13]*a[2]*a[11] + a[13]*a[3]*a[10];
    d[5]  =  a[0]*a[10]*a[15] - a[0]*a[11]*a[14] - a[8]*a[2]*a[15] + a[8]*a[3]*a[14] + a[12]*a[2]*a[11] - a[12]*a[3]*a[10];
    d[9]  = -a[0]*a[9]*a[15]  + a[0]*a[11]*a[13] + a[8]*a[1]*a[15] - a[8]*a[3]*a[13] - a[12]*a[1]*a[11] + a[12]*a[3]*a[9];
    d[13] =  a[0]*a[9]*a[14]  - a[0]*a[10]*a[13] - a[8]*a[1]*a[14] + a[8]*a[2]*a[13] + a[12]*a[1]*a[10] - a[12]*a[2]*a[9];

    d[2]  =  a[1]*a[6]*a[15]  - a[1]*a[7]*a[14]  - a[5]*a[2]*a[15] + a[5]*a[3]*a[14] + a[13]*a[2]*a[7]  - a[13]*a[3]*a[6];
    d[6]  = -a[0]*a[6]*a[15]  + a[0]*a[7]*a[14]  + a[4]*a[2]*a[15] - a[4]*a[3]*a[14] - a[12]*a[2]*a[7]  + a[12]*a[3]*a[6];
    d[10] =  a[0]*a[5]*a[15]  - a[0]*a[7]*a[13]  - a[4]*a[1]*a[15] + a[4]*a[3]*a[13] + a[12]*a[1]*a[7]  - a[12]*a[3]*a[5];
    d[14] = -a[0]*a[5]*a[14]  + a[0]*a[6]*a[13]  + a[4]*a[1]*a[14] - a[4]*a[2]*a[13] - a[12]*a[1]*a[6]  + a[12]*a[2]*a[5];

    d[3]  = -a[1]*a[6]*a[11]  + a[1]*a[7]*a[10]  + a[5]*a[2]*a[11] - a[5]*a[3]*a[10] - a[9]*a[2]*a[7]   + a[9]*a[3]*a[6];
    d[7]  =  a[0]*a[6]*a[11]  - a[0]*a[7]*a[10]  - a[4]*a[2]*a[11] + a[4]*a[3]*a[10] + a[8]*a[2]*a[7]   - a[8]*a[3]*a[6];
    d[11] = -a[0]*a[5]*a[11]  + a[0]*a[7]*a[9]   + a[4]*a[1]*a[11] - a[4]*a[3]*a[9]  - a[8]*a[1]*a[7]   + a[8]*a[3]*a[5];
    d[15] =  a[0]*a[5]*a[10]  - a[0]*a[6]*a[9]   - a[4]*a[1]*a[10] + a[4]*a[2]*a[9]  + a[8]*a[1]*a[6]   - a[8]*a[2]*a[5];

    float invDet = 1.0f / det;
    for (int i = 0; i < 16; i++) inv.m[i] = d[i] * invDet;

    return inv;
}

//  VERSION 2 : inverse analytique, conjugue + translation opposee  
Pose InverseAnalytique(const Pose& p) {
    Quaternion inv = p.orientation.Conjugue();
    Vec3 t = p.position;
    Vec3 tNegatif{-t.x, -t.y, -t.z};
    Vec3 positionInverse = inv.Rotate(tNegatif);
    return {inv, positionInverse};
}

void ComparerCoefficients(const Mat4& m1, const Mat4& m2) {
    float ecartMax = 0.0f;
    for (int i = 0; i < 16; i++) {
        float ecart = std::fabs(m1.m[i] - m2.m[i]);
        if (ecart > ecartMax) ecartMax = ecart;
    }
    std::cout << "Ecart maximal sur les 16 coefficients : " << ecartMax << "\n\n";
}

int main() {
    std::cout << std::fixed << std::setprecision(4);

    //  Cas 1 : pose valide 
    float angle = 3.14159265f / 3.0f; // 60 degres
    Quaternion q{std::cos(angle / 2.0f), 0.0f, std::sin(angle / 2.0f), 0.0f};
    Pose pose{q, {1.0f, 2.0f, 3.0f}};

    Mat4 matricePose = PoseVersMatrice(pose);

    Mat4 inverseGenerale = InversionGenerale(matricePose);
    Pose inverseAnalytiquePose = InverseAnalytique(pose);
    Mat4 inverseAnalytiqueMat = PoseVersMatrice(inverseAnalytiquePose);

    std::cout << " Cas 1 : pose valide \n\n";
    inverseGenerale.Print("Inverse generale");
    std::cout << "\n";
    inverseAnalytiqueMat.Print("Inverse analytique");
    std::cout << "\n";
    ComparerCoefficients(inverseGenerale, inverseAnalytiqueMat);

    // Cas 2 : pose degeneree (quaternion nul, signe d'un bug amont) 
    Quaternion qDegenere{0.0f, 0.0f, 0.0f, 0.0f};
    Pose poseDegeneree{qDegenere, {1.0f, 2.0f, 3.0f}};
    Mat4 matriceDegeneree = PoseVersMatrice(poseDegeneree);

    std::cout << " Cas 2 : pose degeneree (quaternion nul)\n\n";
    matriceDegeneree.Print("Matrice de la pose degeneree");
    std::cout << "\n";

    Mat4 resultatDegenere = InversionGenerale(matriceDegeneree);
    resultatDegenere.Print("Resultat de l'inversion generale");

    return 0;
}
```

Le code met en oeuvre deux fonctions distinctes qui inversnet ka matrice pose , pour pouvoir comparer les ésultats
- une fonction d'inverse analytique qui traite la matrice comme une matrice 4x' quelconque et l'inverse par ma méthode classiquedes cofacteurs

- une fonction d'inverse analytique qui applique directement la formule du conjugué et de la translation opposée sur la pose, sans jamais construire ni inverser la matrice

il convertit ensuite chaque résultat en matrice de 4x4 pour pouvoir comparer les seize coefficients terme à terme et affiche l'écart maximal observé entre les deux méthodes

### Résultats observés 

sur une pose valide les deux méthodes produisent des matrices identiques, lécart maximal mesuré entre les seize coefficientsest nul 
cela confirme que l'inverse analytique est mathématiquement équivalent à l'inverse générale, pour un coût de calcul bien moindre


### Conclusion 

Ce résultat illsutre exactement la mise ne garde du cours ce type de defaut ne fait pas planter le programme , l se voit seulement à l'écran
