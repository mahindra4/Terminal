#ifndef TERMINAL_NODE
#define TERMINAL_NODE

#include "include.h"

class TerminalNode{
public:
    TerminalNode(std::string name,bool file,TerminalNode *parent){
        this->name = name;
        this->file = file;
        this->parent = parent;
    }
    std::string name;
    bool file = 0;
    TerminalNode *parent = nullptr;
    std::vector<TerminalNode *> child;
    // std::set<TerminalNode *> child;
};

#endif