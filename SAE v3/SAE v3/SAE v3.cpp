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
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif // _WIN32

    //Demande de l'image pgm à utiliser pour le ASCII Art
    std::string nomimg;
    std::cout << "Veuillez indiquer le nom de l'image à transformer en ASCII Art : (Bouc.pgm, Banane.pgm,Cascade.pgm) \n";
    std::cin >> nomimg;


    //Nom du fichier texte de sortie renseigné par l’utilisateur
    std::string sortie;
    std::cout << "Choisissez le nom du fichier texte de sortie (Ex : filename.txt) :\n";
    std::cin >> sortie;

    //Ouverture du fichier noming
    std::ifstream in(nomimg, std::ios_base::binary);

    //Ouverture du fichier sortie
    std::ofstream out(sortie);

    //On verifie que les fichiers sont bien ouverts*/
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

    //Pour obtenir la largeur et la hauteur
    double largeur = std::stod(entete[2]);
    double hauteur = std::stod(entete[3]);

    //---------------------------------------------------------

    //Choix de la palette de couleur
    std::cout << "Choisissez la palette (palette.txt, palette2.txt, palette2UTF8.txt, paletteUTF8.txt) sachant que palette.txt est utilisée par défaut : \n";

    std::string paleNum;
    std::cin >> paleNum;

    std::ifstream pal(paleNum);

    //On récupère la palette dans un tableau
    std::vector<std::string> paleTab;
    std::string paleCaractere;

    while (!pal.eof())
    {
        std::getline(pal, paleCaractere);
        paleTab.push_back(paleCaractere);
    }

    std::cout << " Voici la palette choisie : \n";
    for (auto n : paleTab)
    {
        std::cout << n << " __";
    }
    std::cout << "\n\n";

    //---------------------------------------------------------

    //Affichage de l'entete
    for (auto n : entete)
    {
        std::cout << n << "\n ";

    }
    std::cout << "---- Fin de l'entete ----\n\n";


    //--------------------------------------------------------------------------------

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


}