#include "parser.h"

using namespace std;
/**
*    character A tileset.png
*    move_character A 12 12
*    print_text A blah.txt
*    music_play blah.ogg
*/


// Variable :
// character (String name, Tileset name, int x, int y) : Ceci est un personnage o>


// Actions :
// move_character (String nom, int x, int y) : Permet le déplacement du personnage donné jusqu'à (x,y)
// print_text (String name, String filename) : Print le texte du fichier donné (dis par le personnage donné)
// music_play (String musicname) : Joue la musique donnée
// load_script (String filename) : Charge le fichier de script donné
// change_party (String name, String state) : Permet de modifier l'équipe (true ajoute le personnage, false le retire)
// start_fight : Lance le combat de la room

Parser::Parser(){}
Parser::~Parser(){}

// Découpage par ligne du fichier
std::vector<std::string> Parser::cutFile(std::string filename)
{
    std::vector<std::string> Prompts;
    std::ifstream fichier(filename.c_str(), std::ios::in);
    if(fichier)
    {
        std::string ligne;
        while(getline(fichier, ligne))
        {
            Prompts.push_back(ligne);
        }

        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    return Prompts;
}


std::vector<std::string> Parser::cutString(std::string sentence)
{
    vector<std::string> res;
    std::string temp = "";

    for(unsigned int i = 0; i < sentence.length(); i++)
    {
        if(sentence[i] == '"')
        {
            i++;
            while(sentence[i] != '"')
            {
                temp = temp + sentence[i];
                i++;
            }
            i++;
        }
        else
        {
            if(sentence[i] != ' ')
            {
                temp = temp + sentence[i];
            }
            else
            {
                res.push_back(temp);
                temp = "";
            }
        }
    }

    res.push_back(temp); // Dernier mot
    return res;
}
