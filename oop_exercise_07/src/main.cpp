// Харьков П.А., М80-206Б-19

// Спроектировать простейший «графический» векторный редактор. 
// Требование к функционалу редактора:
// создание нового документа.
// импорт документа из файла.
// экспорт документа в файл.
// создание графического примитива (согласно варианту задания).
// удаление графического примитива.
// отображение документа на экране (печать перечня графических объектов и их характеристик в std::cout).
// реализовать операцию undo, отменяющую последнее сделанное действие. Должно действовать для операций добавления/удаления фигур. 


#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include "figures/figure.hpp"
#include "editor.hpp"


using namespace std;

void ClearInput()
{
    // очистка потока до конца строки
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void PrintError()
{  
    cout << "Wrong input!" << endl;
}


int main()
{
    string command;
    Editor editor;
    cout << ">> ";
    while(cin >> command)
    {
        if(command == "create")
        {
            string filename;
            cin >> filename;
            editor.CreateDoc(filename);
        }
        else if(command == "import")
        {
            string filename;
            cin >> filename;
            editor.ImportDoc(filename);
        }
        else if(command == "export")
        {
            editor.ExportDoc();
        }
        else if(command == "print")
        {
            editor.PrintDoc();
        }
        else if(command == "insert")
        {
            Factory fac;
            shared_ptr<Figure> fac_ptr;
            try{
            fac_ptr = fac.CreateFigure(cin);
            }
            catch(int){
                cout << "Invalid figure\n";
            }
            editor.InsertFigure(fac_ptr);
        }
        else if(command == "delete")
        {
            int index;
            cin >> index;
            editor.DeleteFigure(index);
        }
        else if(command == "undo")
        {
            editor.Undo();
        }
        else
        {
            PrintError();
        }
        
        ClearInput();
        cout << ">> ";

    }
    


    return 0;
}
