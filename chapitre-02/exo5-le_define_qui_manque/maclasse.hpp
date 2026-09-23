#ifndef MACLASSE_HPP
#define MACLASSE_HPP

#ifdef AVEC_IMPLEMENTATION

class MaClasse {
public:
    MaClasse();
    void afficher();
};

#else

class MaClasse {
    // la coquille
};

#endif

#endif