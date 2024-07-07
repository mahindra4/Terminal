#include "terminal.h"

void error(){
    std::cerr<<"error: arguments count doesn't match\n";
}

std::string trim(std::string s){
    int l = 0,r = s.length()-1;
    while(l<s.length()-1){
        if(s[l]==' '){
            l++;
        }
        else break;
    }   
    while(r>=0){
        if(s[r]==' '){
            r--;
        }
        else break;
    }
    return s.substr(l,r-l+1);
}

void help(){
    std::cout<<"\nASSUME ALL THE COMMANDS HERE WILL BEHAVE EXACTLY LIKE THEY DID IN THE LINUX\n";
    std::cout<<"\nls {path}             --> here is path is not mentioned then the current directory will be the default path (&)\n"; 
    std::cout<<"                        shows the list of directories and files under the current directory\n";
    std::cout<<"\nmkdir {name or path}  --> makes a new directory with NAME = name\n";
    std::cout<<"\ntouch {name or path}  --> makes a new file with NAME = name\n";
    std::cout<<"\npwd                   --> shows the path of the current directory\n";
    std::cout<<"\ncd {path}             --> change of directory\n";
    std::cout<<"\nrm {path}             --> remove file/directory\n";
    std::cout<<"\nmv {path}             --> move file/directory\n";
    std::cout<<"\ncp {path}             --> copy file/directory\n";
    std::cout<<"\nquit (or) exit       --> exits from the terminal\n\n";
}
int main(){
    Terminal* terminal = new Terminal();
    std::map<std::string,int> commands = {{"ls",2},
                                          {"mkdir",2},
                                          {"touch",2},
                                          {"pwd",1},
                                          {"cd",2},
                                          {"rm",2},
                                          {"mv",3},
                                          {"cp",3}};
    while(1){
        std::cout<<"command: ";
        std::string command;
        getline(std::cin,command);
        command = trim(command);            // trimming the white spaces from the front and the last 
        if(command == "exit" || command == "quit"){
            break;
        }
        if(command == "help"){
            help();
            continue;
        }
        std::vector<std::string> tokens;
        std::string tmp = "";
        for(auto i:command){
            if(i==' '){
                if(tmp!="")
                    tokens.push_back(tmp);
                tmp = "";
            }
            else{
                tmp+=i;
            }
        }
        if(tmp!="") tokens.push_back(tmp);

        if(tokens.size()==0){
            continue;
        }
        else if(commands.find(tokens[0])==commands.end()){
            std::cerr<<"error: command not found!\n";
            continue;
        }
        else if(tokens[0]!="ls" && commands[tokens[0]]!=tokens.size()){
            error();
            continue;
        }


        if(tokens[0]=="ls"){
            std::string path = "";
            if(tokens.size()==commands["ls"]){
                path = tokens[1];
            }
            if(tokens.size()>commands["ls"]){
                error();
                continue;
            }
            terminal->ls(path);
        }
        else if(tokens[0]=="pwd"){
            std::cout << terminal->pwd() << "\n";
        }
        else if(tokens[0] == "mkdir"){
            terminal->create(tokens[1],0);
        }
        else if(tokens[0] == "touch"){
            terminal->create(tokens[1],1);
        }
        else if(tokens[0] == "cd"){
            terminal->cd(tokens[1]);
        }
        else if(tokens[0] == "rm"){
            terminal->remove_node(tokens[1]);
        }
        else if(tokens[0] == "mv"){
            terminal->mv(tokens[1],tokens[2]);
        }
        else if(tokens[0] == "cp"){
            terminal->cp(tokens[1],tokens[2]);
        }
    }
    return 0;
}
