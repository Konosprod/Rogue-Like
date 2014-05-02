#ifndef DIALOG_H
#define DIALOG_H

#include "dialogParameter.h"

class Dialog : public sf::Drawable, public sf::Transformable
{
public :

    Dialog(dialogParameter parameter);
    Dialog();
    virtual ~Dialog();
    bool isFinished();
    void showNext();

    void setParameter(dialogParameter parameter);
    void setPosition(sf::Vector2f v);
    void setText (std::string s);
    void setSizeLine(int n);
    void setNumberLines (int n);
    void setFont (std::string f);
    void setTextColor (sf::Color c);
    void setTexture(std::string s);
    void setCharacterSize(unsigned int n);


protected :

    std::string loadText(std::string file);
    std::string showNextPhrase();
    void textCut();
    void resetDialog();
    void resetText();



private :
    std::vector<std::string> m_listDialog;
    sf::Text m_currentText;
    unsigned int m_pos;
    std::string m_text;
    int m_size;
    int m_nlines;
    sf::Font m_font;
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
};

void find_and_replace(std::string& source, std::string const& find, std::string const& replace);

#endif // DIALOG_H
