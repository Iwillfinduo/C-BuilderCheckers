//---------------------------------------------------------------------------


#pragma hdrstop

#include "SerializeService.h"
#include <fstream>
#include <string>
#include <iostream>
#include "Logic.h"
//---------------------------------------------------------------------------
// Запись файла в тектовый документ по своим правилам
void Serializer::SaveLogicObject (Logic logic, AnsiString path) {

	std::ofstream out(path.c_str()); // открываем файл для записи
	std::vector<std::vector<std::pair<int,int> > > matrix = logic.GetMatrix();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			out << matrix[i][j].first << " " << matrix[i][j].second << std::endl;
		}
	}
	AnsiString move = logic.is_it_your_move(1) ?  "1" : "2";
	out << move.c_str();
	out << std::endl;

	out << (int)logic.isExtraMove();
	out << std::endl;
	
	out << AnsiString((int)logic.isTimer()).c_str() << std::endl;
	if (logic.isTimer()) {
		out << logic.GetWhiteTimer() << " " << logic.GetBlackTimer(); 
	}
	out.close(); // Закрываем файл для записи
}
//---------------------------------------------------------------------------
// Cчитывание и генерация нового класса
Logic Serializer::LoadFromObject (AnsiString path) {
	std::string line;
	std::vector<std::vector<std::pair<int,int> > > matrix;
	std::ifstream in(path.c_str()); // окрываем файл для чтения
	int move;
	int extra_move;
	int is_timer;
	int timer_white = 0;
	int timer_black = 0;
	if (in.is_open())
	{
		for (int i = 0; i < 8; i++) {
			matrix.push_back(std::vector<std::pair<int, int> >());
			for (int j = 0; j < 8; j++) {
				int x, y;
				in >> x >> y;
				matrix[i].push_back(std::pair<int,int>(x, y));
			}
		}
		
		in >> move;

		in >> extra_move;
		
		in >> is_timer;
		
		if (is_timer) {
			in >> timer_white >> timer_black;	
		}
		
	}
	in.close();     // закрываем файл
	return Logic(matrix, move, extra_move, is_timer, timer_white, timer_black);
}

#pragma package(smart_init)
