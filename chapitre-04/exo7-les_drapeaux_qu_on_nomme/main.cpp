#include <cstdint>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    // Les treize drapeaux simples, dans l'ordre du tableau de l'énoncé
    const std::vector<std::pair<std::string, std::uint32_t>> simples = {
        {"RENDER2D", 1},
        {"RENDER3D", 2},
        {"TEXT", 4},
        {"UI", 8},
        {"SHADOW", 16},
        {"POST_PROCESS", 32},
        {"VFX", 64},
        {"ANIMATION", 128},
        {"OVERLAY", 256},
        {"SIMULATION", 512},
        {"OFFSCREEN", 1024},
        {"RAYTRACING", 2048},
        {"GPU_CULLING", 4096},
    };

    // Tous les noms connus : les treize simples et les cinq composés
    std::map<std::string, std::uint32_t> connus;
    for (const auto& drapeau : simples) {
        connus[drapeau.first] = drapeau.second;
    }
    connus["NONE"] = 0;
    connus["2D_ESSENTIALS"] = 1 | 4;
    connus["3D_BASE"] = 2 | 16 | 32;
    connus["DEBUG"] = 256 | 512;
    connus["ALL"] = 4294967295u;

    int n = 0;
    std::cin >> n;

    // Sans aucun nom, la configuration garde sa valeur par défaut : ALL
    std::uint32_t valeur = (n == 0) ? connus["ALL"] : 0;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        std::cin >> nom;

        const auto it = connus.find(nom);
        if (it == connus.end()) {
            std::cout << "INCONNU " << nom << '\n';
        } else {
            // OU binaire, pas addition : un nom répété ne change rien
            valeur |= it->second;
        }
    }

    char hexa[16];
    std::snprintf(hexa, sizeof(hexa), "%08X", static_cast<unsigned int>(valeur));
    std::cout << "VALEUR " << valeur << '\n';
    std::cout << "HEXA 0x" << hexa << '\n';

    // Les quatre drapeaux qui ont besoin d'autres drapeaux, dans l'ordre imposé
    struct Dependance {
        std::string nom;
        std::vector<std::string> besoins;
    };
    const std::vector<Dependance> dependances = {
        {"TEXT", {"RENDER2D"}},
        {"UI", {"RENDER2D", "TEXT"}},
        {"SHADOW", {"RENDER3D"}},
        {"OVERLAY", {"RENDER2D", "TEXT"}},
    };

    for (const Dependance& d : dependances) {
        // Un drapeau éteint ne réclame rien
        if ((valeur & connus[d.nom]) == 0) {
            continue;
        }
        for (const std::string& besoin : d.besoins) {
            if ((valeur & connus[besoin]) == 0) {
                std::cout << "MANQUE " << d.nom << ' ' << besoin << '\n';
            }
        }
    }

    // On compte les treize drapeaux simples allumés dans la valeur finale
    int allumes = 0;
    for (const auto& drapeau : simples) {
        if ((valeur & drapeau.second) != 0) {
            ++allumes;
        }
    }

    std::cout << "ALLUMES " << allumes << '\n';
    std::cout << "ETEINTS " << (13 - allumes) << '\n';
    return 0;
}
