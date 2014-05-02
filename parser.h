#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <fstream>


class Parser
{
    public:
        Parser();
        ~Parser();
        std::vector<std::string> cutFile(std::string filename);
        std::vector<std::string> cutString(std::string sentence);

};


#endif
