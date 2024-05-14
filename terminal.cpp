#include "terminal.h"
std::vector<std::string> Terminal::path_tokenization(std::string path){
    std::string tmp = "";
    std::vector<std::string> v;
    for(auto i:path){
        if(i=='/'){
            if(tmp!="")
                v.push_back(tmp);
            tmp = "";
        }
        else{
            tmp+=i;
        }
    }
    if(tmp!="") v.push_back(tmp);
    return v;
}

std::string Terminal::path_conversion(std::string path){
    if(path[0] != '/'){
        path = "./"+path;
    }
    return path;
}

TerminalNode* Terminal::search(std::string path,bool &error,bool &file){
    path = path_conversion(path);
    std::vector<std::string> v = path_tokenization(path);
    TerminalNode *cur = current;
    if(path[0]=='/'){
        cur = head;
    }
    for(auto i:v){
        bool flag = 1;
        if(i==".") continue;
        else if(i==".."){
            cur = cur->parent;
            flag = 0;
        }
        else{
            for(auto j:cur->child){
                if(i == j->name){
                    flag = 0;
                    cur = j;
                    if(j->file){
                        file = 1;
                    }
                    break;
                }
            }
        }
        if(error){
            break;
        }
        if(cur == nullptr || flag){
            std::cerr <<"There is no such file or directory\n";
            error = 1;
            break;
        }
    }
    return cur;
}

void Terminal::add_node(std::string path,std::string name,bool file){
    bool error = 0,f = 0;
    TerminalNode *cur = search(path,error,f);
    if(error) return;
    TerminalNode *tmp = new TerminalNode(name,file,cur);
    bool flag = 1;
    for(auto i:cur->child){
        if(i->name == name){
            flag = 0;
            delete tmp;
            break;
        }
    }
    if(flag) cur->child.push_back(tmp);
    else{
        std::cerr<<"already exists!\n";
    }
    // cur->child.insert(tmp);
}
void remove_parent(TerminalNode *parent,TerminalNode *child){
    std::vector<TerminalNode *>::iterator it = parent->child.begin();
    // std::set<TerminalNode *>::iterator it = parent->child.begin();
    for(;it!=parent->child.end();it++){
        if((*it)->name == child->name){
            parent->child.erase(it);
            break;
        }
    }
}
void remove(TerminalNode *node){
    if(node == nullptr) return;
    for(auto i:node->child){
        remove(i);
    }
    delete node;
}

bool is_ansester(TerminalNode *a,TerminalNode *b){   // checks if a is the ansester of b 
    while(b && b!=a){
        b = b->parent;
    }
    if(b) return true;
    return false;
}

void Terminal::remove_node(std::string path){
    path = path_conversion(path);
    bool error = 0,file = 0;
    TerminalNode *cur = search(path,error,file),*tmp = current;
    if(error) return;
    if(cur->parent == nullptr){
        std::cout<<"deleting root is illegal\n";
        return;
    }
    if(is_ansester(cur,tmp)){
        current = cur->parent;
    }
    // while(tmp && (tmp!=cur)){   // checking if the ansester of the current node is the node that we need to delete
    //     tmp = tmp->parent;
    // }
    // if(tmp)                     // if the removing node is ansester than move the current pointer to the location of the parent of the removing node
    //     current = cur->parent;
    remove_parent(cur->parent,cur);
    remove(cur);
}

void Terminal::ls(std::string path){
    bool error = 0,file = 0;
    TerminalNode *cur = (path=="")?current:search(path,error,file);
    if(error) return;
    // cout<<cur->child.size()<<" ls -\n";
    for(auto i:cur->child){
        std::cout<<i->name<<" ";
    }
    std::cout<<"\n";
}

std::string Terminal::path_split(std::string &path){
    int i = path.length()-1;
    std::string dir_name = "";
    while(i>=0){
        if(path[i]=='/'){
            break;
        }
        else{
            dir_name = path[i]+dir_name;
        }
        i--;
    }
    path = path.substr(0,i);
    if(path=="") path = "/";
    return dir_name;
}
void Terminal::create(std::string path,bool file){
    path = path_conversion(path);
    // std::cout<<path<<"\n";
    std::string dir_name = path_split(path);
    add_node(path,dir_name,file);
}

void Terminal::cd(std::string path){
    bool error = 0,file = 0; 
    path = path_conversion(path);
    TerminalNode *cur = search(path,error,file);
    if(error) return;
    if(file){
        std::string tmp = "";
        int i = path.length()-1;
        while(i>=0){
            if(path[i]=='/'){
                break;
            }
            else{
                tmp = path[i]+tmp;
            }
            i--;
        }
        std::cerr <<"error: not a directory - "<<tmp<<std::endl;
        return;
    }
    current = cur;
}

std::string Terminal::pwd(){
    std::string output = "";
    TerminalNode *cur = current;
    if(cur->parent == nullptr){
        output = "/";
    }
    while(cur->parent){
        output = "/" + cur->name + output;
        cur = cur->parent;
    }
    return output;
}

void Terminal::mv(std::string path,std::string destination){
    bool error = 0,file = 0;
    path = path_conversion(path);
    destination = path_conversion(destination);
    TerminalNode *source_node = search(path,error,file);
    if(error) return;
    error = 0,file = 0;
    TerminalNode *destination_node = search(destination,error,file);
    if(error) return;
    bool flag = 0;
    if(is_ansester(source_node,destination_node)){
        std::cerr<<"can't move "<<path<<" to its subdirectory "<<destination<<"\n";
        flag = 1;
    }
    if(file){
        std::cerr<<"can't move to a file "<<destination<<"\n";
        flag = 1;
    }
    if(flag) return;
    remove_parent(source_node->parent,source_node);
    source_node->parent = destination_node;
    destination_node->child.push_back(source_node);
}
TerminalNode* duplicate(TerminalNode *node){
    TerminalNode *tmp = new TerminalNode(node->name,node->file,node->parent); // created a duplicate of the current node
    for(auto i:node->child){
        TerminalNode *dup = duplicate(i);
        tmp->child.push_back(dup); 
    }
    return tmp;
}
void Terminal::cp(std::string path,std::string destination){
    bool error = 0,file = 0;
    path = path_conversion(path);
    destination = path_conversion(destination);
    TerminalNode *source_node = search(path,error,file);
    if(error) return;
    error = 0,file = 0;
    TerminalNode *destination_node = search(destination,error,file);
    if(error) return;
    // bool flag = 0;
    // if(is_ansester(source_node,destination_node)){
    //     std::cerr<<"can't copy "<<path<<" to its subdirectory "<<destination<<"\n";
    //     flag = 1;
    // }
    if(file){
        std::cerr<<"can't copy to a file "<<destination<<"\n";
        // flag = 1;
        return;
    }
    // if(flag) return;
    TerminalNode *duplicate_source = duplicate(source_node);
    duplicate_source->parent = destination_node;
    destination_node->child.push_back(duplicate_source);
}