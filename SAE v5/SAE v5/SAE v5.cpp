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



    //Affichage de l'entete
    for (auto n : entete)
    {
        std::cout << n << "\n ";

    }
    std::cout << "---- Fin de l'entete ----\n\n";


    //---------------------------------------------------------

    //Choix de la palette de couleur
    std::cout << "Choisissez la palette :\npalette 1 - [1]\npalette 2 - [2]\npalette 3 - [3]\npalette 4 - [4]\n(Par défaut, palette 1) : ";

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

    //--------------------------------------------------------

    //Rééchantillonnage
    double width;
    double height;
    std::cout << "\nEntrez la largeur, par défaut la largeur de base : ";
    std::cin >> width;
    std::cout << "\nEntrez la hauteur, par défaut la hauteur de base : ";
    std::cin >> height;


    int facteurlarg = round(largeur / width);
    int facteurhaute = round(hauteur / height);


    //Création d'une mémoire de largeur octets :
    std::vector<char> donnees(largeur);


    std::vector<std::vector<double>> donneesReduit;
    std::vector<double>ligneReduit;
    std::vector<double>ligneReduit2;


    //Lecture de 10 octets depuis le fichier et stockage dans le tableau donnees :
    in.read(donnees.data(), largeur);


    for (int y = 0; y <= height; y++)
    {
        int compteur2 = 0;
        for (int v = 0; v <= width; v++)
        {

            int compteur1 = 0;
            int somme = 0;
            //Calcul des moyennes sur une ligne :
            while (compteur1 < facteurlarg && compteur2 < donnees.size() - 1)
            {
                if (donnees[compteur2] < 0)
                {
                    int npos, necart;
                    npos = donnees[compteur2] * (-1);
                    necart = 128 - npos;
                    somme += (128 + necart);
                }
                else
                {
                    somme += donnees[compteur2];
                }
                compteur2++;
                compteur1++;

            }
            somme /= facteurlarg;
            ligneReduit.push_back(somme);
            std::cout << somme << " ";
        }
        donneesReduit.push_back(ligneReduit);
        in.read(donnees.data(), largeur);



        //Le calcul des moyennes dans le sens de la hauteur n'est pas terminé
        int compteur3 = 0;
        int compteur4 = 0;
        int somme2 = 0;
        for (int h = 0; h <= facteurlarg; h++)
        {
            while (compteur3 < facteurhaute)
            {
                somme2 += donneesReduit[compteur3][compteur4];
                compteur3++;
            }



        }

    }










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