#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif // _WIN32

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <iomanip>
#include <locale>
#include <sstream>

int main(int argc, char* argv[])
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif // _WIN32

    std::string nomimg, sortie;
    std::string paleNum;

    // Gestion des arguments de la ligne de commande
    for (int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]) == "--help")
        {
            std::cout << "Usage :\n"
                << argv[0] << " [options] \n\n"
                << "Options : \n"
                << "--input fichier    Spécifie le fichier image à convertir \n"
                << "--output fichier   Spécifie le nom du fichier texte qui contiendra l'Ascii Art. \n"
                << "--palette fichier  Spécifie un fichier texte contenant la palette de couleur Ascii. \n"
                << "--help             Affiche cette aide \n\n";
            return 0;
        }
        if (std::string(argv[i]) == "--input" && i + 1 < argc)
        {
            nomimg = std::string(argv[i + 1]);
            i++;  // Skip the next argument since it has been consumed
        }
        if (std::string(argv[i]) == "--output" && i + 1 < argc)
        {
            sortie = std::string(argv[i + 1]);
            i++;
        }
        if (std::string(argv[i]) == "--palette" && i + 1 < argc)
        {
            paleNum = std::string(argv[i + 1]);
            i++;
        }
    }

    // Demander l'image.pgm à l'utilisateur si non spécifié
    if (nomimg.empty())
    {
        std::cout << "Veuillez indiquer le nom de l'image à transformer en ASCII Art : ";
        std::cin >> nomimg;
    }

    // Nom du fichier texte de sortie renseigné par l’utilisateur
    if (sortie.empty())
    {
        std::cout << "Choisissez le nom du fichier texte de sortie (Ex : filename.txt) : ";
        std::cin >> sortie;
    }

    // Ouverture des fichiers
    std::ifstream in(nomimg, std::ios_base::binary);
    std::ofstream out(sortie);

    if (!in.is_open())
    {
        std::cerr << "Problème d'ouverture du fichier d'entrée : " << nomimg << std::endl;
        return 1;
    }

    if (!out.is_open())
    {
        std::cerr << "Problème d'ouverture du fichier de sortie : " << sortie << std::endl;
        return 1;
    }

    // (Le reste de votre code pour lire et traiter les fichiers)

    //---------------------------------------------------------------------------------------------------------------------------------------------------------


    //Ici vous devez décoder l'entête du fichier
    std::string entetes;
    std::array<std::string, 5>entete;


    //Affichage des entetes
    for (int n = 0; n < 5; n++)
    {
        if (n != 2)
        {
            std::getline(in, entetes);
            entete[n] = entetes;

        }
        if (n == 2)
        {

            std::getline(in, entetes, ' ');
            entete[n] = entetes;
        }
    }

    //Pour obtenir la largeur et la hauteur
    double largeur = std::stod(entete[2]);
    double hauteur = std::stod(entete[3]);



    //Affichage de l'entete
    for (auto n : entete)
    {
        std::cout << n << "\n ";

    }
    std::cout << "---- Fin de l'entete ----\n\n";


    //---------------------------------------------------------------------------------------------------------------------------------------------------------

    //Choix de la palette de couleur
    std::vector<std::string> paleTab;
    std::ifstream pal(paleNum);

    bool usedInArgs = true;

    if (!pal.is_open())
    {
        paleNum = "palette.txt";
        paleTab = { "W", "w", "l", "i", ":", ",", ".", " " };

        usedInArgs = false;

    }

    //On récupère la palette dans un tableau

    std::string paleCaractere;

    if (usedInArgs)
    {
        while (!pal.eof())
        {
            std::getline(pal, paleCaractere);
            paleTab.push_back(paleCaractere);
        }
    }

    std::cout << " Voici la palette choisie : \n";
    for (auto n : paleTab)
    {
        std::cout << n << " __";
    }
    std::cout << "\n\n";


    //---------------------------------------------------------------------------------------------------------------------------------------------------------


    //Création d'une mémoire de largeur octets :
    std::vector<char> donnees(largeur);


    //Lecture de 10 octets depuis le fichier et stockage dans le tableau donnees :
    in.read(donnees.data(), largeur);





    //Palette encore
    double tranche = (255 / paleTab.size());



    std::vector <double> trancheScale;
    double increment = 0;

    for (int n = 0; n <= paleTab.size(); n++)
    {

        trancheScale.push_back(increment);
        increment += tranche;


    }


    for (auto g : trancheScale)
    {
        std::cout << g << " ";
    }



    for (int y = 0; y < hauteur; y++)
    {
        for (float n : donnees)
        {

            for (int x = 0; x <= paleTab.size() - 1; x++)
            {
                if (n < 0)
                {
                    int npos, necart;
                    npos = n * (-1);
                    necart = 128 - npos;
                    n = (128 + necart);

                }

                if (trancheScale[x] < n && n <= trancheScale[x + 1] && x < paleTab.size() - 1)
                {
                    std::cout << paleTab[x];
                    out << paleTab[x];
                }

                if (trancheScale[x] < n && x == paleTab.size() - 1)
                {
                    out << paleTab[x];
                    std::cout << paleTab[x];
                }
            }


        }
        out << "\n";
        std::cout << "\n";
        in.read(donnees.data(), largeur);

    }


    //---------------------------------------------------------------------------------------------------------------------------------------------------------


}