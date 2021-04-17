#pragma once

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include "figures/figure.hpp"
#include "factory.hpp"


struct Command
{
    virtual void Undo() = 0;
};

struct InsertComm: public Command
{
    std::vector<std::shared_ptr<Figure>>& buff;
    InsertComm(std::vector<std::shared_ptr<Figure>>& b): buff(b){};

    void Undo() override
    {
        buff.pop_back();
    }
};

struct DeleteComm: public Command
{
    std::vector<std::shared_ptr<Figure>>& buff;
    int index;
    std::shared_ptr<Figure> figure;
    DeleteComm(std::vector<std::shared_ptr<Figure>>& b, int ind, std::shared_ptr<Figure> fig):
        buff(b), index(ind), figure(fig){};

    void Undo() override
    {
        buff.insert(buff.begin() + index, figure);
    }

};

class Editor
{
private:
    std::vector<std::shared_ptr<Figure>> buff;
    std::string name;
    std::vector<std::shared_ptr<Command>> history;
public:
    Editor():name("") {}
    void CreateDoc(std::string& file); 
    bool ImportDoc(std::string& file);
    void ExportDoc();
    void PrintDoc(); 
    void InsertFigure(std::shared_ptr<Figure>& fig); 
    void DeleteFigure(size_t index); 
    void Undo();
};

void Editor::CreateDoc(std::string& file)
{
    name = file;
    buff.clear();
}

bool Editor::ImportDoc(std::string& file)
{
    std::ifstream in(file, std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Cant open file\n";
        return true;
    }

    int size;
    in >> size;
    std::vector<std::shared_ptr<Figure>> new_buf;
    Factory fac;
    for(int i = 0; i < size; i++)
    {
        try{
        new_buf.push_back(fac.CreateFigure(in));
        }
        catch(int){
            return false;
        }
    }

    name = file;
    buff = new_buf;
    history.clear();
    return true;
}

void Editor::ExportDoc()
{
    if(name.empty())
    {
        std::cout << "No document\n";
        return;
    }

    std::ofstream out(name, std::ios::out|std::ios::trunc);
    if(!out.is_open())
    {
        std::cout << "Cant open file\n";
        return;
    }
    out << buff.size() << '\n';
    for(auto f: buff)
    {
        f->PrintPoints(out);
        out << '\n';
    }
    
}

void Editor::PrintDoc(){
    if(buff.empty()){
        std::cout << "No figures\n";
        return;
    }

    for(size_t i = 0; i < buff.size(); i++){
        std::cout << i << ' '; buff[i]->PrintPoints(std::cout);
        std::cout << '\n'; 
    }  
    
}

void Editor::InsertFigure(std::shared_ptr<Figure>& fig)
{
    if(name.empty())
    {
        std::cout << "No document\n";
        return;
    }

    history.push_back(std::shared_ptr<Command>(new InsertComm(buff)));
    buff.push_back(fig);
}

void Editor::DeleteFigure(size_t index)
{
    if(name.empty())
    {
        std::cout << "No document\n";
        return;
    }
    if(index >= buff.size())
    {
        std::cout << "Out of range\n";
        return;
    }

    history.push_back(std::shared_ptr<Command>(new DeleteComm(buff, index, buff[index])));
    
    buff.erase(buff.begin() + index);
}

void Editor::Undo()
{
    if(history.empty())
    {
        std::cout << "No actions\n";
        return;
    }
    history.back()->Undo();
    history.pop_back();
}