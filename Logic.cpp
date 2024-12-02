//---------------------------------------------------------------------------


#pragma hdrstop
#include "Logic.h"
#include <string>
#include <utility>
#include <vcl.h>
#include <cmath>
//---------------------------------------------------------------------------
// Метод взаимодействия логики и UI предоставление возможных ходов для фигуры
std::vector<std::pair<int, int> > Logic::GetMoves(short color, short index) {
	std::vector<std::pair<int, int> > moves;
	if (this->is_extra_move && (this->piece_with_extra_move.first != color ||
	 this->piece_with_extra_move.second != index)){

	}

    // Проверка на корректность хода данного цвета
    if (!this->is_it_your_move(color)) {
        return moves;
    }

    // Получаем координаты фигуры по индексу
    int x = -1, y = -1;
    for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->matrix[i][j].first == color && this->matrix[i][j].second == index) {
                x = i;
				y = j;
				this->last_i = i;
				this->last_j = j;
                break;
            }
        }
        if (x != -1) break; // Если нашли координаты, выходим из цикла
    }

    // Проверка на корректность найденных координат
    if (x == -1 || y == -1) {
        return moves; // Фигура не найдена
    }

    // Проверка на дамку
	bool isKing = (color == 3 || color == 4);

    // Вспомогательные переменные для направления движения
    const int directions[4][2] = {
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

	if (isKing) {
		// Логика для дамки
		for (int i = 0; i < 4; i++) {
			int dx = directions[i][0], dy = directions[i][1];
			int nx = x + dx, ny = y + dy;
			while (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && this->matrix[nx][ny].first == 0) {
				moves.push_back(std::make_pair(nx, ny));
				nx += dx;
				ny += dy;
			}

			// Проверка возможности прыжка через противника
			if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 &&
				(this->matrix[nx][ny].first != color && this->matrix[nx][ny].first != 0)) {
				int nnx = nx + dx, nny = ny + dy;
				if (nnx >= 0 && nnx < 8 && nny >= 0 && nny < 8 && this->matrix[nnx][nny].first == 0) {
					moves.push_back(std::make_pair(nnx, nny));
				}
			}
		}
	} else {
		// Логика для обычной пешки
		int direction = (color == 1) ? -1 : 1; // Направление движения: белые вверх, черные вниз
		for (int i = 0; i < 2; i++) {
			int dx = directions[i + (direction > 0 ? 2 : 0)][1];
			int nx = x + direction, ny = y + dx;

			// Проверка на границы поля
			if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
				if (this->matrix[nx][ny].first == 0) {
					moves.push_back(std::make_pair(nx, ny)); // Обычный ход
				} else if (this->matrix[nx][ny].first != color) {
                    // Проверка возможности прыжка через противника
					int nnx = nx + direction, nny = ny + dx;
                    if (nnx >= 0 && nnx < 8 && nny >= 0 && nny < 8 && this->matrix[nnx][nny].first == 0) {
                        moves.push_back(std::make_pair(nnx, nny));
					}
                }
            }
        }
	}

	return moves;
};
//---------------------------------------------------------------------------
// Инициаллизация логики и игрового поля в нем
Logic::Logic(int timer) {
	this->timer = timer;
	this->is_white_move = true;
	int board[8][8] = {
		{0, 2, 0, 2, 0, 2, 0, 2},
		{2, 0, 2, 0, 2, 0, 2, 0},
		{0, 2, 0, 2, 0, 2, 0, 2},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 1, 0, 1, 0, 1, 0},
		{0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 0}};
	int counter = 0;
	this->is_extra_move = false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j<8; j++) {
			if (board[i][j] == 1 || board[i][j] == 2) {
				std::pair<int,int> fig(board[i][j], counter++);
				this->matrix[i][j] =  fig;
				counter = counter%12;
			} else {
				std::pair<int,int> place(board[i][j], -1);
				this->matrix[i][j] =  place;
			}
		}
	}


};
//---------------------------------------------------------------------------
// Метод взаимодействия логики и UI Считывание ходов фигуры
std::pair<int, std::pair<int, int> > Logic::ReadMove(short color, short index, short place_i, short place_j) {
	// Получаем список доступных ходов для данной фигуры
	std::vector<std::pair<int, int> > moves = this->GetMoves(color, index);

	// Проверяем, входит ли целевое поле в список доступных ходов
    bool validMove = false;
	for (int i = 0; i < moves.size(); i++) {
        if (moves[i].first == place_i && moves[i].second == place_j) {
            validMove = true;
            break;
        }
    }

    // Если ход недопустим, возвращаем false
    if (!validMove) {
		return std::pair<int, std::pair<int, int> >(false, std::pair<int, int>(-1, -1));
    }

	// Получаем текущие координаты шашки, которая движется
	int x = this->last_i;
	int y = this->last_j;

	// Проверяем, был ли это прыжок через шашку противника
	int dx = (place_i - x) / 2;
	int dy = (place_j - y) / 2;
	std::pair<int, std::pair<int, int> > output_pair;
	output_pair.second = std::pair<int, int>(-1, -1);

	// Проверка прыжка через шашку
	if (abs(dx) == 1 && abs(dy) == 1) { // Прыжок через шашку
        int mid_x = x + dx;
		int mid_y = y + dy;

		// Определяем цвет противника
		int opponent = (color == 1 || color == 3) ? 2 : 1;
		int opponentKing = (opponent == 1) ? 3 : 4;

        // Удаляем шашку противника с доски
        if (this->matrix[mid_x][mid_y].first == opponent || this->matrix[mid_x][mid_y].first == opponentKing) {
			// Очистить клетку с противником
			output_pair.second = std::pair<int, int>(this->matrix[mid_x][mid_y].first, this->matrix[mid_x][mid_y].second);
			this->matrix[mid_x][mid_y] = std::pair<int, int>(0, -1); // Убираем фигуру противника с доски
		}
		// Проверка можно ли прыгнуть через еще одну шашку
		moves = this->GetMoves(color, index);

    	// Получаем текущие координаты шашки, которая движется
		int x = this->last_i;
		int y = this->last_j;

		// Проверяем, был ли это прыжок через шашку противника
		int dx = (place_i - x) / 2;
		int dy = (place_j - y) / 2;
		std::pair<int, std::pair<int, int> > output_pair;
		output_pair.second = std::pair<int, int>(-1, -1);

		// Проверка прыжка через шашку
		if (abs(dx) == 1 && abs(dy) == 1) {
			this->is_extra_move = true;
			this->piece_with_extra_move = std::pair<int,int>(color, index);
		} else {
			this->is_extra_move = false;
        }
	}

	// Перемещаем шашку на целевое поле
	this->matrix[place_i][place_j] = this->matrix[x][y];
	this->matrix[x][y] = std::pair<int, int>(0, -1);  // Очищаем исходное поле


	// Проверяем, становится ли шашка дамкой
	if ((color == 1 && place_i == 0) || (color == 2 && place_i == 7)) {
		output_pair.first = 2; // состояние обращение фигуры в дамку
		this->matrix[place_i][place_j].first = (color == 1) ? 3 : 4; // Сделать дамкой
	} else {
	   output_pair.first = true; // состояние простого успешного хода
	}

	// Меняем очередь ходов
	if (this->is_extra_move) {
        
	} else {
		this->is_white_move = !this->is_white_move;
	}

	// Возвращаем успешный ход

	return output_pair; // Ход успешно выполнен
}


//---------------------------------------------------------------------------
bool Logic::is_it_your_move(short color) {
	if (((color == 1 || color == 3) && !this->is_white_move) || (color == 2 || color == 4) && this->is_white_move) {
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
// Проверка, что шашка под боем
bool Logic::isPieceUnderAttack(int x, int y, short color) {
	// Определяем цвет противника
    int opponent = (color == 1 || color == 3) ? 2 : 1;  // Противник
    int opponentKing = (opponent == 1) ? 3 : 4;

    // Проверяем, есть ли шашки противника, которые могут атаковать указанную клетку
    for (int dx = -1; dx <= 1; dx += 2) {  // Пытаемся "пройти" по диагоналям
        for (int dy = -1; dy <= 1; dy += 2) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && this->matrix[nx][ny].first != 0) {
                if (this->matrix[nx][ny].first == opponent || this->matrix[nx][ny].first == opponentKing) {
                    // Проверка на возможность прыжка через шашку
                    int nnx = nx + dx;
					int nny = ny + dy;
                    if (nnx >= 0 && nnx < 8 && nny >= 0 && nny < 8 && this->matrix[nnx][nny].first == 0) {
                        return true;  // Шашка под боем
                    }
                }
            }
        }
    }
    return false;  // Если ни одна шашка противника не может атаковать
};
//---------------------------------------------------------------------------

#pragma package(smart_init)
