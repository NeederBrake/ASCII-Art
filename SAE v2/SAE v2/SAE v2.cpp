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

int main()
{

    //UTF-8
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif // _WIN32

    //Demander l'image.pgm à l'utilisateur pour le ASCII Art
    std::string nomimg;
    std::cout << "Veuillez indiquer le nom de l'image à transformer en ASCII Art : (Bouc.pgm, Banane.pgm, Cascade.pgm) \n";
    std::cin >> nomimg;

    //Nom du fichier texte de sortie renseigné par l’utilisateur
    std::string sortie;
    std::cout << "Choisissez le nom du fichier texte de sortie (Poutrelle.txt) :\n";
    std::cin >> sortie;

    //Ouverture du fichier noming
    std::ifstream in(nomimg, std::ios_base::binary);

    //Ouverture du fichier sortie
    std::ofstream out(sortie);

    //On verifie que les fichiers sont bien ouverts
    if (!in.is_open())
        std::cerr << "Problème d'ouverture du fichier.\n";
    if (!out.is_open())
        std::cerr << "Problème d'ouverture du fichier.\n";

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

    //Obtention de la largeur et hauteur de l'image
    double largeur = std::stod(entete[2]);
    double hauteur = std::stod(entete[3]);



    //Affichage de l'entete
    for (auto n : entete)
    {
        std::cout << n << "\n";

    }
    std::cout << "---- Fin de l'entete ----\n";


    //Création d'une mémoire de largeur octets
    std::vector<char> donnees(largeur);


    //Lecture de 10 octets depuis le fichier et stockage dans le tableau donnees
    in.read(donnees.data(), largeur);

    //Réalisation de l'ASCII Art et copie dans le out
    for (int y = 0;y < hauteur; y++)
    {
        for (float n : donnees)
        {
            if (n < 0)
            {
                int npos, necart;
                npos = n * (-1);
                necart = 128 - npos;
                n = (128 + necart);
            }
            if (0 < n && n <= 31.875)
            {
                std::cout << "W";
                out << "W";
            }
            if (31.875 < n && n <= 63.75)
            {
                std::cout << "w";
                out << "w";
            }
            if (63.75 < n && n <= 95.625)
            {
                std::cout << "l";
                out << "l";
            }
            if (95.625 < n && n <= 127.5)
            {
                std::cout << "i";
                out << "i";
            }
            if (127.5 < n && n <= 159.375)
            {
                std::cout << ":";
                out << ":";
            }
            if (159.375 < n && n <= 191.25)
            {
                std::cout << ",";
                out << ",";
            }
            if (191.25 < n && n <= 223.125)
            {
                std::cout << ".";
                out << ".";
            }
            if (223.125 < n && n <= 255)
            {
                std::cout << " ";
                out << " ";
            }
        }
        out << "\n";
        std::cout << "\n";
        in.read(donnees.data(), largeur);

    }

    std::cout << "\n\n\n";

}
