#include "interpreter.h"

using namespace std;

Interpreter::Interpreter(GameEnvironment* gameEnvironment) : m_gameEnvironment(gameEnvironment)
{
    m_dialogParameter.font = "rc/font/arial.ttf";
    m_dialogParameter.background = "rc/images/tex.png";
    m_dialogParameter.textColor = sf::Color(0, 0, 0);
    m_dialogParameter.numberLines = 3;
    m_dialogParameter.sizeDialog = 70;
    m_dialogParameter.fontSize = 14;
    m_dialogParameter.position = sf::Vector2f(0, 0);

    m_dialogWindow.setParameter(m_dialogParameter);

    isDialogDone = false;
}

Interpreter::~Interpreter()
{
    clear();
}

int Interpreter::getCommandNumber (string firstWord)
{
    if (firstWord == "character")
        return CHARACTER;
    else if (firstWord == "move_character")
        return MOVE_CHARACTER;
    else if (firstWord == "print_text")
        return PRINT_TEXT;
    else if (firstWord == "music_play")
        return MUSIC_PLAY;
    else if (firstWord == "load_script")
        return LOAD_SCRIPT;
    else if (firstWord == "change_party")
        return CHANGE_PARTY;
    else if (firstWord == "start_fight")
        return START_FIGHT;
    else
        return -1;
}

bool Interpreter::getState (string state)
{
    return ((state == "true") ? true : false);
}



void Interpreter::interpretCommand(string command)
{
    Parser p;
    vector<string> words = m_p.cutString(command);
    string firstWord = words[0];

    switch (getCommandNumber(firstWord))
    {
        case CHARACTER:
        {
            string charName = words[1];
            string fileName = words[2];

            int x = atoi(words[3].c_str());
            int y = atoi(words[4].c_str());

            m_characters[charName] = new Character(fileName);
            m_characters[charName]->setEnvironment(m_gameEnvironment);
            m_characters[charName]->setPosition(x, y);
        }
        break;

        case MUSIC_PLAY:
        {
            string musicName = words[1];
            m_gameEnvironment->soundManager->stop();
            m_gameEnvironment->soundManager->loadMusic(musicName, 1);
            m_gameEnvironment->soundManager->play();
        }
        break;

        case LOAD_SCRIPT:
        {
            string fileName = words[1];
            clear();
            loadScript(fileName);
            update();
        }
        break;

        case CHANGE_PARTY:
        {
            string charName = words[1];
            bool state = getState(words[2]);
        }
        break;

        case START_FIGHT:
        {
            clear();
        }
        break;
    }
}


void Interpreter::update ()
{
    vector<string> words = m_p.cutString(m_commands[0]);
    string firstWord = words[0];

    std::map<std::string, Character*>::iterator itr;
    for(itr = m_characters.begin(); itr != m_characters.end(); ++itr)
    {
            m_gameEnvironment->window->draw(*m_characters[itr->first]);
    }

    if (firstWord == "move_character")
    {
        string charName = words[1];
        int x = atoi(words[2].c_str());
        int y = atoi(words[3].c_str());
        bool ended = m_characters[charName]->moveTo(x, y);

        if (ended)
        {
            m_commands.erase(m_commands.begin(), m_commands.begin()+1);
        }
    }
    else if(firstWord == "print_text")
    {
        if(!isDialogDone)
        {
            m_dialogWindow.setText(words[2]);
            m_dialogWindow.showNext();
            m_gameEnvironment->window->draw(m_dialogWindow);
        }
        else
        {
            m_commands.erase(m_commands.begin(), m_commands.begin()+1);
            isDialogDone = false;
        }
    }
    else if(firstWord == "load_script")
    {
        interpretCommand(m_commands[0]);
    }
    else
    {
        interpretCommand(m_commands[0]);
        m_commands.erase(m_commands.begin(), m_commands.begin()+1);
    }
}

void Interpreter::loadScript (string fileName)
{
    m_commands = m_p.cutFile(fileName);
}

bool Interpreter::isEmpty()
{
    return m_commands.empty();
}

void Interpreter::clear()
{
    std::map<std::string, Character*>::iterator itr;
    for(itr = m_characters.begin(); itr != m_characters.end(); ++itr)
    {
        delete m_characters[itr->first];
    }
    m_characters.clear();
    isDialogDone = false;
}

void Interpreter::nextDialog()
{
    if(!m_dialogWindow.isFinished())
    {
        m_dialogWindow.showNext();
        m_gameEnvironment->window->draw(m_dialogWindow);
    }
    else
    {
        isDialogDone = true;
    }
}

