#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int main() {
    // Ordre d'essai des interfaces
    const std::map<std::string, std::vector<std::string>> ordres = {
        {"WINDOWS", {"VULKAN", "DX12", "DX11", "OPENGL", "SOFTWARE"}},
        {"MACOS",   {"METAL", "OPENGL", "SOFTWARE"}},
        {"IOS",     {"METAL", "SOFTWARE"}},
        {"ANDROID", {"VULKAN", "OPENGL", "SOFTWARE"}},
    };
    // autres plateforme suivi dans cet ordre
    const std::vector<std::string> parDefaut = {"VULKAN", "OPENGL", "SOFTWARE"};

    // Noms lisibles des interfaces
    const std::map<std::string, std::string> lisibles = {
        {"VULKAN",   "Vulkan"},
        {"DX12",     "DirectX 12"},
        {"DX11",     "DirectX 11"},
        {"OPENGL",   "OpenGL"},
        {"METAL",    "Metal"},
        {"SOFTWARE", "Software"},
    };

    int n = 0;
    std::cin >> n;

    int ignorees = 0;
    int logiciel = 0;
    std::set<std::string> differentes;

    for (int i = 0; i < n; ++i) {
        std::string nom, plateforme;
        int k = 0;
        std::cin >> nom >> plateforme >> k;

        std::set<std::string> disponibles;
        for (int j = 0; j < k; ++j) {
            std::string api;
            std::cin >> api;
            disponibles.insert(api);
        }

        // L'ordre de la plateforme
        const auto it = ordres.find(plateforme);
        const std::vector<std::string>& ordre =
            (it != ordres.end()) ? it->second : parDefaut;

        // Interfaces que la détection n'essaie jamais
        const std::set<std::string> dansOrdre(ordre.begin(), ordre.end());
        for (const std::string& api : disponibles) {
            if (dansOrdre.count(api) == 0) {
                ++ignorees;
            }
        }

        // Première interface de l'ordre présente dans la liste.
        // SOFTWARE marche partout, il est choisi même s'il n'est pas listé.
        std::string choisie = "SOFTWARE";
        for (const std::string& api : ordre) {
            if (api == "SOFTWARE" || disponibles.count(api) > 0) {
                choisie = api;
                break;
            }
        }

        const std::string& lisible = lisibles.at(choisie);
        std::cout << nom << ' ' << lisible << '\n';

        if (choisie == "SOFTWARE") {
            ++logiciel;
        }
        differentes.insert(lisible);
    }

    std::cout << "IGNOREES " << ignorees << '\n';
    std::cout << "LOGICIEL " << logiciel << '\n';
    std::cout << "DIFFERENTES " << differentes.size() << '\n';
    return 0;
}