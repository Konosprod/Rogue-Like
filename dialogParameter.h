#ifndef DIALOG_PARAMETER_H_INCLUDED
#define DIALOG_PARAMETER_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>

struct dialogParameter
{

public :
    std::string dialogText;
    int sizeDialog;
    int numberLines;
    sf::Vector2f position;
    std::string font;
    unsigned int fontSize;
    sf::Color textColor;
    std::string background;
};

#endif // DIALOG_PARAMETER_H_INCLUDED
