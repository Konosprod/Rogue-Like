#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <map>
#include "parser.h"
#include "Character.h"
#include "Dialog.h"
#include "dialogParameter.h"
#include "SoundManager.h"
#include "GameEnvironment.h"

#define CHARACTER 1
#define MOVE_CHARACTER 2
#define PRINT_TEXT 3
#define MUSIC_PLAY 4
#define LOAD_SCRIPT 5
#define CHANGE_PARTY 6
#define START_FIGHT 7


class Interpreter
{
    public:
        Interpreter(GameEnvironment* gameEnvironment);
        ~Interpreter();
        void interpretCommand(std::string command);
        void update ();
        void nextDialog();
        void clear();
        void loadScript (std::string fileName);
        bool isEmpty();


    private:
        std::map<std::string, Character*> m_characters;
        Dialog m_dialogWindow;
        dialogParameter m_dialogParameter;
        bool isDialogDone;
        bool firstDialog;
        int getCommandNumber (std::string firstWord);
        bool getState (std::string state);
        GameEnvironment* m_gameEnvironment;
        std::vector<std::string> m_commands;
        Parser m_p;
};

#endif
