//---------------------------------------------------------------------------

#ifndef LogicH
#define LogicH
//---------------------------------------------------------------------------
#include <vector>
#include <utility>
#include "Logic.h"

//---------------------------------------------------------------------------
// Служебный класс, backend игры, где обрабатывается вся логика не связаная с UI
class Logic {
	public:
	  Logic() {}
	  Logic(int timer); // Базовый констркуктор при создании игры
	  Logic(std::vector<std::vector<std::pair<int,int> > > matrix,
	   int move, int extra_move, int is_timer,
		int timer_white, int timer_black); // конструктор для загрузки игры
	  std::vector<std::pair<int, int> > GetMoves(short color, short index); // Получение ходов для шашки
	  std::pair<int, std::pair<int,int> > ReadMove(short color, short index, short place_i, short place_j); // Считывание хода шашки
	  int didGameEnd(); // Проверка закончилась ли игра
	  int GetWhiteTimer(); // Геттеры и сеттеры таймера
	  int GetBlackTimer();
	  void SetWhiteTimer(int seconds);
	  void SetBlackTimer(int seconds);
	  bool isTimer(); // Проверка есть ли в игре таймер
	  bool is_it_your_move(short color); // Проверка чей ход
	  bool isExtraMove(); // Узнать есть ли дополнительный ход
	  std::vector<std::vector<std::pair<int,int> > > GetMatrix(); // геттер матрицы для сериализации

	private:
	  int timer_white; // Таймеры, счетчики и флаги
	  int timer_black;
	  int white_count;
	  int black_count;
	  bool is_timer;
	  bool is_white_move;
	  bool is_extra_move;
	  bool is_last_kill_moves;

	  // Служебные функции
	  bool isPieceUnderAttack(int x, int y, short color);
	  bool isAnyPieceUnderAttackAndHasMoves(short color);
	  bool hasMoves(int x, int y, short color);
	  bool hasMovesByColor(short color);

	  //Хранение игрового поля
	  std::pair<int, int> matrix[8][8]; // pair color and id of figure

	  // Кеширование больших проходов в соображениях оптимизации
	  std::pair<int, int> piece_with_extra_move;
	  int last_i;
	  int last_j;
};

#endif
