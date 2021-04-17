// Харьков П.А., М8О-206Б-19

// Создать приложение, которое будет считывать из стандартного ввода данные фигур, согласно варианту задания, выводить их характеристики на экран и записывать в файл. Фигуры могут задаваться как своими вершинами, так и другими характеристиками (например, координата центра, количество точек и радиус).
// Программа должна:
// 1.	Осуществлять ввод из стандартного ввода данных фигур, согласно варианту задания;
// 2.	Программа должна создавать классы, соответствующие введенным данных фигур;
// 3.	Программа должна содержать внутренний буфер, в который помещаются фигуры. Для создания буфера допускается использовать стандартные контейнеры STL. Размер буфера задается параметром командной строки. Например, для буфера размером 10 фигур: oop_exercise_08 10
// 4.	При накоплении буфера они должны запускаться на асинхронную обработку, после чего буфер должен очищаться;
// 5.	Обработка должна производиться в отдельном потоке;
// 6.	Реализовать два обработчика, которые должны обрабатывать данные буфера:
// a.	Вывод информации о фигурах в буфере на экран;
// b.	Вывод информации о фигурах в буфере в файл. Для каждого буфера должен создаваться файл с уникальным именем.
// 7.	Оба обработчика должны обрабатывать каждый введенный буфер. Т.е. после каждого заполнения буфера его содержимое должно выводиться как на экран, так и в файл.
// 8.	Обработчики должны быть реализованы в виде лямбда-функций и должны хранится в специальном массиве обработчиков. Откуда и должны последовательно вызываться в потоке – обработчике.
// 9.	В программе должно быть ровно два потока (thread). Один основной (main) и второй для обработчиков;
// 10.	В программе должен явно прослеживаться шаблон Publish-Subscribe. Каждый обработчик должен быть реализован как отдельный подписчик.
// 11.	Реализовать в основном потоке (main) ожидание обработки буфера в потоке-обработчике. Т.е. после отправки буфера на обработку основной поток должен ждать, пока поток обработчик выведет данные на экран и запишет в файл.

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <functional>
#include <fstream>
#include <mutex>
#include "factory.hpp"
#include "myqueue.hpp"


std::string genName() {
	std::string res;
	for (size_t i = 0; i < 5; ++i) {
		res.push_back('a' + rand() % 26);
	}
	return res;
}

std::ofstream file;
std::string folder = "results/";
MyQueue<std::vector< std::shared_ptr<Figure>>> messages;
void thread_func()
{
    using fType = std::function<void(std::shared_ptr<Figure> fig)>;
	fType PrintToScreen = [](std::shared_ptr<Figure> fig) {
		fig->PrintPoints(std::cout); std::cout << std::endl;
	};
	fType WriteToFile = [](std::shared_ptr<Figure> fig) {
		fig->PrintPoints(file); file << std::endl;
	};
	std::vector<fType> funcs({PrintToScreen, WriteToFile});
	while (true) {
		if (!messages.Empty()) {
			std::vector< std::shared_ptr< Figure > > elem = messages.Front();
			if (elem.empty()) {
				break;
			}
			file.open((folder + genName()).c_str(), std::ios::out|std::ios::trunc);
			while (!elem.empty()) {
				std::shared_ptr<Figure> figPtr = elem.back();
				elem.pop_back();
				for (auto func : funcs) {
					func(figPtr);
				}
			}
			messages.Pop();
		}
	}
}

int main(int argc, char** argv)
{
    size_t buff_size;
    if (argc < 2) {
		std::cout << "Missing argument!" << std::endl;
		return -1;
	}
    try {
		buff_size = stoi(std::string(argv[1]));
	} catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return -1;
	}


    std::thread myThread(thread_func);
	std::vector<std::shared_ptr<Figure>> figures;
    std::string figure;
    while(std::cin >> figure){
        auto fig = std::shared_ptr<Figure>(Factory::CreateFigure(std::cin, figure));
        if(fig == nullptr)
        {
            std::cout << "Wrong fugure!\n";
            continue;
        }
        figures.push_back(fig);

        if(figures.size() == buff_size){
            messages.Push(figures);
			while (!messages.Empty()) {
			}
			figures.clear();
        }
    }   
    messages.Push(figures);
	figures.clear();
	messages.Push(figures);
	myThread.join();


    return 0;
}
