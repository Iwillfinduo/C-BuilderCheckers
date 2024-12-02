//---------------------------------------------------------------------------


#pragma hdrstop
#include "Logic.h"
#include <string>
#include <utility>
#include <vcl.h>
#include <cmath>
//---------------------------------------------------------------------------
// ����� �������������� ������ � UI �������������� ��������� ����� ��� ������
std::vector<std::pair<int, int> > Logic::GetMoves(short color, short index) {
	std::vector<std::pair<int, int> > moves;
	if (this->is_extra_move && (this->piece_with_extra_move.first != color ||
	 this->piece_with_extra_move.second != index)){

	}

    // �������� �� ������������ ���� ������� �����
    if (!this->is_it_your_move(color)) {
        return moves;
    }

    // �������� ���������� ������ �� �������
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
        if (x != -1) break; // ���� ����� ����������, ������� �� �����
    }

    // �������� �� ������������ ��������� ���������
    if (x == -1 || y == -1) {
        return moves; // ������ �� �������
    }

    // �������� �� �����
	bool isKing = (color == 3 || color == 4);

    // ��������������� ���������� ��� ����������� ��������
    const int directions[4][2] = {
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

	if (isKing) {
		// ������ ��� �����
		for (int i = 0; i < 4; i++) {
			int dx = directions[i][0], dy = directions[i][1];
			int nx = x + dx, ny = y + dy;
			while (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && this->matrix[nx][ny].first == 0) {
				moves.push_back(std::make_pair(nx, ny));
				nx += dx;
				ny += dy;
			}

			// �������� ����������� ������ ����� ����������
			if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 &&
				(this->matrix[nx][ny].first != color && this->matrix[nx][ny].first != 0)) {
				int nnx = nx + dx, nny = ny + dy;
				if (nnx >= 0 && nnx < 8 && nny >= 0 && nny < 8 && this->matrix[nnx][nny].first == 0) {
					moves.push_back(std::make_pair(nnx, nny));
				}
			}
		}
	} else {
		// ������ ��� ������� �����
		int direction = (color == 1) ? -1 : 1; // ����������� ��������: ����� �����, ������ ����
		for (int i = 0; i < 2; i++) {
			int dx = directions[i + (direction > 0 ? 2 : 0)][1];
			int nx = x + direction, ny = y + dx;

			// �������� �� ������� ����
			if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
				if (this->matrix[nx][ny].first == 0) {
					moves.push_back(std::make_pair(nx, ny)); // ������� ���
				} else if (this->matrix[nx][ny].first != color) {
                    // �������� ����������� ������ ����� ����������
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
// �������������� ������ � �������� ���� � ���
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
// ����� �������������� ������ � UI ���������� ����� ������
std::pair<int, std::pair<int, int> > Logic::ReadMove(short color, short index, short place_i, short place_j) {
	// �������� ������ ��������� ����� ��� ������ ������
	std::vector<std::pair<int, int> > moves = this->GetMoves(color, index);

	// ���������, ������ �� ������� ���� � ������ ��������� �����
    bool validMove = false;
	for (int i = 0; i < moves.size(); i++) {
        if (moves[i].first == place_i && moves[i].second == place_j) {
            validMove = true;
            break;
        }
    }

    // ���� ��� ����������, ���������� false
    if (!validMove) {
		return std::pair<int, std::pair<int, int> >(false, std::pair<int, int>(-1, -1));
    }

	// �������� ������� ���������� �����, ������� ��������
	int x = this->last_i;
	int y = this->last_j;

	// ���������, ��� �� ��� ������ ����� ����� ����������
	int dx = (place_i - x) / 2;
	int dy = (place_j - y) / 2;
	std::pair<int, std::pair<int, int> > output_pair;
	output_pair.second = std::pair<int, int>(-1, -1);

	// �������� ������ ����� �����
	if (abs(dx) == 1 && abs(dy) == 1) { // ������ ����� �����
        int mid_x = x + dx;
		int mid_y = y + dy;

		// ���������� ���� ����������
		int opponent = (color == 1 || color == 3) ? 2 : 1;
		int opponentKing = (opponent == 1) ? 3 : 4;

        // ������� ����� ���������� � �����
        if (this->matrix[mid_x][mid_y].first == opponent || this->matrix[mid_x][mid_y].first == opponentKing) {
			// �������� ������ � �����������
			output_pair.second = std::pair<int, int>(this->matrix[mid_x][mid_y].first, this->matrix[mid_x][mid_y].second);
			this->matrix[mid_x][mid_y] = std::pair<int, int>(0, -1); // ������� ������ ���������� � �����
		}
		// �������� ����� �� �������� ����� ��� ���� �����
		moves = this->GetMoves(color, index);

    	// �������� ������� ���������� �����, ������� ��������
		int x = this->last_i;
		int y = this->last_j;

		// ���������, ��� �� ��� ������ ����� ����� ����������
		int dx = (place_i - x) / 2;
		int dy = (place_j - y) / 2;
		std::pair<int, std::pair<int, int> > output_pair;
		output_pair.second = std::pair<int, int>(-1, -1);

		// �������� ������ ����� �����
		if (abs(dx) == 1 && abs(dy) == 1) {
			this->is_extra_move = true;
			this->piece_with_extra_move = std::pair<int,int>(color, index);
		} else {
			this->is_extra_move = false;
        }
	}

	// ���������� ����� �� ������� ����
	this->matrix[place_i][place_j] = this->matrix[x][y];
	this->matrix[x][y] = std::pair<int, int>(0, -1);  // ������� �������� ����


	// ���������, ���������� �� ����� ������
	if ((color == 1 && place_i == 0) || (color == 2 && place_i == 7)) {
		output_pair.first = 2; // ��������� ��������� ������ � �����
		this->matrix[place_i][place_j].first = (color == 1) ? 3 : 4; // ������� ������
	} else {
	   output_pair.first = true; // ��������� �������� ��������� ����
	}

	// ������ ������� �����
	if (this->is_extra_move) {
        
	} else {
		this->is_white_move = !this->is_white_move;
	}

	// ���������� �������� ���

	return output_pair; // ��� ������� ��������
}


//---------------------------------------------------------------------------
bool Logic::is_it_your_move(short color) {
	if (((color == 1 || color == 3) && !this->is_white_move) || (color == 2 || color == 4) && this->is_white_move) {
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
// ��������, ��� ����� ��� ����
bool Logic::isPieceUnderAttack(int x, int y, short color) {
	// ���������� ���� ����������
    int opponent = (color == 1 || color == 3) ? 2 : 1;  // ���������
    int opponentKing = (opponent == 1) ? 3 : 4;

    // ���������, ���� �� ����� ����������, ������� ����� ��������� ��������� ������
    for (int dx = -1; dx <= 1; dx += 2) {  // �������� "������" �� ����������
        for (int dy = -1; dy <= 1; dy += 2) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && this->matrix[nx][ny].first != 0) {
                if (this->matrix[nx][ny].first == opponent || this->matrix[nx][ny].first == opponentKing) {
                    // �������� �� ����������� ������ ����� �����
                    int nnx = nx + dx;
					int nny = ny + dy;
                    if (nnx >= 0 && nnx < 8 && nny >= 0 && nny < 8 && this->matrix[nnx][nny].first == 0) {
                        return true;  // ����� ��� ����
                    }
                }
            }
        }
    }
    return false;  // ���� �� ���� ����� ���������� �� ����� ���������
};
//---------------------------------------------------------------------------

#pragma package(smart_init)
