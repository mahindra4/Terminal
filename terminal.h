#ifndef TERMINAL
#define TERMINAL

#include "terminalNode.h"

class Terminal{
public:
    TerminalNode *head = new TerminalNode("",0,nullptr);
    TerminalNode *current = head;                          // shows the current node
    TerminalNode* search(std::string path,bool &error,bool &file);         // search the node based on the path
    std::vector<std::string> path_tokenization(std::string path);
    std::string path_conversion(std::string path);
    void add_node(std::string path,std::string name,bool file);                // mkdir or touch
    void remove_node(std::string path);
    void ls(std::string path);
    void create(std::string path,bool file);
    void cd(std::string path);
    std::string path_split(std::string &path);
    std::string pwd();
    void mv(std::string path,std::string destination);
    void cp(std::string path,std::string destination);
};

#endif
