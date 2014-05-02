#include "Dialog.h"

Dialog::Dialog()
{

}

Dialog::Dialog(dialogParameter parameter)
{
    setParameter(parameter);
}

Dialog::~Dialog()
{

}

void Dialog::setParameter(dialogParameter parameter)
{
    m_pos = 0;
    m_nlines = parameter.numberLines;
    m_text = "";
    m_size = parameter.sizeDialog;
    m_font.loadFromFile(parameter.font);

    m_texture.loadFromFile(parameter.background);

    m_sprite.setTexture(m_texture);

    m_currentText.setFont(m_font);
    m_currentText.setCharacterSize(parameter.fontSize);
    m_currentText.setColor(parameter.textColor);

    setPosition(parameter.position);

    textCut();
}

std::string Dialog::loadText(std::string file)
{
    std::fstream fichier(file.c_str());
    std::string text = "";
    std::string ligne;
    while(getline(fichier, ligne))
    {
        text += ligne + "\n";
    }
    fichier.close();

    return text;
}

void Dialog::textCut()
{
    int unsigned i = 0;
    int unsigned j = 0;
    bool agree = false;

    find_and_replace(m_text,"\\n","\n");
    find_and_replace(m_text,"...","…");

    while (i < m_text.size())
    {
        j = i;
        i += m_size;
        agree = false;

        std::size_t found = m_text.find("\n",j);
        if(found!=std::string::npos && found < i)
        {
            m_listDialog.push_back(m_text.substr(j,found-j));
            i = found+1;
            j = i;
            agree = true;
        }
        while(!agree)
        {
            if (i == j+1)
            {
                m_listDialog.push_back(m_text.substr(j,m_size+1));
                i += m_size+1;
                agree = true;
            }

            char c = m_text[i];

            if(c == '.' || c == ' ' || c == '\n' || c == '?' || c == ',' || c=='!')
            {
                m_listDialog.push_back(m_text.substr(j,i-j+1));
                if (c == '.' || c == '?' || c == ',' || c == '!')
                    i = i+2;

                agree = true;

            }
            else
               i--;
        }


    }

}

std::string Dialog::showNextPhrase()
{
    std::string nextText = "";
    unsigned int i = 0;

    if(!isFinished())
    {
        nextText = m_listDialog[m_pos];

        while(i < nextText.size())
        {
            if (nextText.at(i) == '\n')
            {
               nextText = nextText.substr(0,i) + " " + nextText.substr(i+1);
            }

            i++;
        }
        nextText += "\n";

        m_pos++;
    }

     return nextText;
}

void Dialog::showNext()
{

    if(!isFinished())
    {
        std::string m_text = "";

        for(int i =0; i < m_nlines && !isFinished(); i++)
        {
            m_text += showNextPhrase();
        }

        m_currentText.setString(m_text);
    }

}

bool Dialog::isFinished()
{
    return !(m_pos < m_listDialog.size());
}

void Dialog::draw(sf::RenderTarget& t, sf::RenderStates s) const
{
    t.draw(m_sprite);
    t.draw(m_currentText);
    (void)s;
}

void Dialog::setPosition(sf::Vector2f v)
{
  m_sprite.setPosition(v);
  m_currentText.setPosition(sf::Vector2f(v.x+5,v.y+10));
}

void find_and_replace(std::string& source, std::string const& find, std::string const& replace)
{
    for(std::string::size_type i = 0; (i = source.find(find, i)) != std::string::npos;)
    {
        source.replace(i, find.length(), replace);
        i += replace.length() - find.length() + 1;
    }
}

void Dialog::setText (std::string s)
{
    m_text = s;

    resetDialog();
}

void Dialog::setSizeLine(int n)
{
    m_size = n;

    resetDialog();

}

void Dialog::resetDialog()
{
  m_listDialog.clear();
  m_pos = 0;

  textCut();
  showNext();
}

void Dialog::setNumberLines(int n)
{
    m_nlines = n;

    m_pos = 0;
}

void Dialog::setFont(std::string f)
{
    m_font.loadFromFile(f);

    resetText();
}

void Dialog::setTextColor(sf::Color c)
{
    m_currentText.setColor(c);
    resetText();
}

void Dialog::resetText()
{
    m_pos = m_pos - m_nlines;
}

void Dialog::setTexture (std::string s)
{
    m_texture.loadFromFile(s);

    m_sprite.setTexture(m_texture);

    resetText();
}

void Dialog::setCharacterSize(unsigned int n)
{
    m_currentText.setCharacterSize(n);

    resetText();
}



