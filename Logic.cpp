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
        this->is_last_kill_moves = false;
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
	bool is_opponent_under_attack = false;
	// �������� �� ���������� ��� ���� ����� ���� �����
	if (this->isAnyPieceUnderAttackAndHasMoves((color == 1 || color == 3) ? 2 : 1)) {
		is_opponent_under_attack = true;
	}

	// �������� �� ������������ ��������� ���������
	if (x == -1 || y == -1) {
	  this->is_last_kill_moves = false;
	  return moves; // ������ �� �������
	}

	// �������� �� �����
	bool isKing = (color == 3 || color == 4);
	// ��������������� ���������� ��� ����������� ��������
	const int directions[4][2] = {
		{-1, -1}, {-1, 1}, {1, -1}, {1, 1}
	};

	// ���������� ���� ����������
	int opponent = (color == 1 || color == 3) ? 2 : 1;
	int opponentKing = (opponent == 1) ? 3 : 4;

	// ���������� ���� ��������
	int teammates = (color == 1 || color == 3) ? 1 : 2;  // �������
	int teammatesKing = (teammates == 1) ? 3 : 4;


	std::vector<std::pair<int, int> > kill_moves;
	if (isKing) {
		int dx = 1, dy = 1;
		bool directions_stop[4] = {false, false, false, false};
		bool met_opponent_by_direction[4] = {false, false, false, false};
		int dx_start[4] = {0, 0, 0, 0};
		int dx_stop[4] = {0, 0, 0, 0};
		while(dx <= 7) {

			for (int d = 0; d < 4; d++) {
				if (directions_stop[d]) {
					continue;
				}

				int x_multiplyer = directions[d][0];
				int y_multiplyer = directions[d][1];

				int nx =  x + (x_multiplyer * dx);
				int ny = y + (y_multiplyer * dx);

				if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) {
					directions_stop[d] = true;
					dx_stop[d] = met_opponent_by_direction[d] ? dx - 1 : dx ;
					continue;
				}

				if (met_opponent_by_direction[d] && (dx_start[d] == 0 || dx_start[d] == 1)) {
					dx_start[d] = dx;
				}
				if (this->matrix[nx][ny].first == teammates ||
				this->matrix[nx][ny].first == teammatesKing) {
					directions_stop[d] = true;
					dx_stop[d] = dx;
					continue;
				} else if ((this->matrix[nx][ny].first == opponent ||
				this->matrix[nx][ny].first == opponentKing) &&
				 met_opponent_by_direction[d] == false) {
					met_opponent_by_direction[d] = true;
				} else if ((this->matrix[nx][ny].first == opponent ||
				this->matrix[nx][ny].first == opponentKing) &&
				met_opponent_by_direction[d] == true) {
					dx_stop[d] = dx;
					directions_stop[d] = true;
					continue;
				}
				if (dx_start[d] == 0) {
					dx_start[d] = 1;
					dx_stop[d] = 1;
				}
			}
			dx++;
		}
		// �������������� �����
		for (int d = 0; d < 4; d++) {
			if (dx_start[d] != dx_stop[d] && dx_start[d] != 0) {
				for(int j = dx_start[d]; j < dx_stop[d]; j++) {
					int x_multiplyer = directions[d][0];
					int y_multiplyer = directions[d][1];

					int nx =  x + (x_multiplyer * j);
					int ny = y + (y_multiplyer * j);

					if(dx_start[d] != 1 && dx_start[d] != 0) {
						kill_moves.push_back(std::make_pair(nx,ny));

					} else {
						moves.push_back(std::make_pair(nx, ny));
					}
				}
			}
		}
	} else {
		// ������ ��� ������� �����
		int direction = (color == 1) ? -1 : 1; // ����������� ��������: ����� �����, ������ ����
		// �������� ���� ������
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
						kill_moves.push_back(std::make_pair(nnx, nny));
					}
				}
			}
		}
		// �������� ������ ����� ���������� �����
		for (int i = 0; i < 2; i++) {
			int dx = directions[i + (direction > 0 ? 0 : 2)][1];
			int nx = x - direction, ny = y + dx;
			// �������� �� ������� ����
			if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
				if (this->matrix[nx][ny].first != teammates && this->matrix[nx][ny].first != 0
				 && this->matrix[nx][ny].first != teammatesKing) {
					// �������� ����������� ������ ����� ����������
					int nnx = nx - direction, nny = ny + dx;
					if (nnx >= 0 && nnx < 8 && nny >= 0 && nny < 8 && this->matrix[nnx][nny].first == 0) {
						kill_moves.push_back(std::make_pair(nnx, nny));
					}
				}
			}
		}
	}
	if (kill_moves.size() != 0) {

		this->is_last_kill_moves = true;
		return kill_moves;

	}
	if(is_opponent_under_attack) {
		this->is_last_kill_moves = false;
		return std::vector<std::pair<int, int> > ();
	}
	this->is_last_kill_moves = false;
	return moves;
};
//---------------------------------------------------------------------------
// �������������� ������ � �������� ���� � ���
Logic::Logic(int timer) {

	if (timer > 0) {
    	this->timer_white = timer / 2;
		this->timer_black = timer / 2;
		this->is_timer = true;
	} else {
		this->is_timer = false;
	}
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
	this->white_count = 12;
	this->black_count = 12;

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
	// �������� �� �����
	bool isKing = (color == 3 || color == 4);
	// �������� ������� ���������� �����, ������� ��������
	int x = this->last_i;
	int y = this->last_j;

	// ���������, ��� �� ��� ������ ����� ����� ����������
	std::pair<int, std::pair<int, int> > output_pair;
	output_pair.second = std::pair<int, int>(-1, -1);
	// �������� ������ ����� �����
	// ���������� ���� ����������
	int opponent = (color == 1 || color == 3) ? 2 : 1;
	int opponentKing = (opponent == 1) ? 3 : 4;
	bool is_attack = false;
	if (isKing) {
		int dx = abs(place_i - x);
		int x_multiplyer = ((place_i - x) > 0) ? 1 : -1;
		int y_multiplyer = ((place_j - y) > 0) ? 1 : -1;
		for (int i = 0; i < dx; i++) {
			int nx = x + (i * x_multiplyer);
			int ny = y + (i * y_multiplyer);
			if (this->matrix[nx][ny].first == opponent || this->matrix[nx][ny].first == opponentKing) {
				is_attack = true;
                // �������� ������ � �����������
				output_pair.second = std::pair<int, int>(this->matrix[nx][ny].first, this->matrix[nx][ny].second);
				this->matrix[nx][ny] = std::pair<int, int>(0, -1); // ������� ������ ���������� � �����
				opponent == 1 ? this->white_count-- : this->black_count--;

			}
		}
	} else {

    	int dx = (place_i - x) / 2;
		int dy = (place_j - y) / 2;
		if (abs(dx) == 1 && abs(dy) == 1) { // ������ ����� �����
			is_attack = true;
			int mid_x = x + dx;
			int mid_y = y + dy;

			// ������� ����� ���������� � �����
			if (this->matrix[mid_x][mid_y].first == opponent || this->matrix[mid_x][mid_y].first == opponentKing) {
				// �������� ������ � �����������
				output_pair.second = std::pair<int, int>(this->matrix[mid_x][mid_y].first, this->matrix[mid_x][mid_y].second);
				this->matrix[mid_x][mid_y] = std::pair<int, int>(0, -1); // ������� ������ ���������� � �����
				opponent == 1 ? this->white_count-- : this->black_count--;
			}
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
	if (is_attack) {
		// �������� ����� �� �������� ����� ��� ���� �����
		moves = this->GetMoves(color, index);
		if (this->is_last_kill_moves) {
			this->is_extra_move = true;
			this->piece_with_extra_move = std::pair<int,int>(color, index);
		} else {
			this->is_extra_move = false;
		}
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
	int opponent = (color == 1 || color == 3) ? 2 : 1;
	int opponentKing = (opponent == 1) ? 3 : 4;

	// ���������� ���� ��������
	int teammates = (color == 1 || color == 3) ? 1 : 2;  // �������
	int teammatesKing = (teammates == 1) ? 3 : 4;

	 // ����������� ��� ��������: �� ���������� (�����-�����, �����-������, ����-�����, ����-������)
	const int directions[4][2] = {
		{-1, -1}, {-1, 1},  // �����-�����, �����-������
		{1, -1}, {1, 1}     // ����-�����, ����-������
	};
	int dx = 1, dy = 1;
	bool directions_stop[4] = {false, false, false, false};
	while(dx <= 7 && dy <= 7) {
		// ��������� ��� ����������� ��� �������� �����
		for (int d = 0; d < 4; d++) {
			if (directions_stop[d]) {
				continue;
			}

			int x_multiplyer = directions[d][0];
			int y_multiplyer = directions[d][1];

			int nx =  x + (x_multiplyer * dx);
			int ny = y + (y_multiplyer * dy);

			if ((nx < 0 || nx >= 8 || ny < 0 || ny >= 8) ||
			 (this->matrix[nx][ny].first == teammates ||
			  this->matrix[nx][ny].first == teammatesKing)) {
				directions_stop[d] = true;
				continue;
			} else {
				int behind_x = x - (x_multiplyer * 1);
				int begind_y = y - (y_multiplyer * 1);
				if ((behind_x < 0 || behind_x >= 8 || begind_y < 0 || begind_y >= 8) ||
				  (this->matrix[behind_x][begind_y].first != 0 ||
				  this->matrix[behind_x][begind_y].first != 0)) {
					directions_stop[d] = true;
					continue;
				}
				if ((nx < 0 || nx >= 8 || ny < 0 || ny >= 8) ||
				  (this->matrix[nx][ny].first != 0 ||
				  this->matrix[nx][ny].first != 0)) {
					if(abs(dx) == 1 && abs(dy) == 1 &&
					 (this->matrix[nx][ny].first == opponent ||
					 this->matrix[nx][ny].first == opponentKing)) {
					 	return true;
					} else if(this->matrix[nx][ny].first == opponentKing) {
						return true;
					}
				}
			}
		}
		++dx;
		++dy;
	}

	// ���� ��� ������, ���������� false
	return false;
}
//---------------------------------------------------------------------------
// �������� ��������� �� ���� ���� ����� ������� ����� ��� ����
bool Logic::isAnyPieceUnderAttackAndHasMoves(short color) {
	// ���������� ���� ��������
	int teammates = (color == 1 || color == 3) ? 1 : 2;  // �������
	int teammatesKing = (teammates == 1) ? 3 : 4;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->matrix[i][j].first == 0) {
				continue;
			} else {
				if((this->matrix[i][j].first == teammates ||
				 this->matrix[i][j].first == teammatesKing) &&
				  this->isPieceUnderAttack(i,j,this->matrix[i][j].first) &&
				  this->hasMoves(i,j, color)) {
						return true;
				  }
			}

		}
	}
	return false;
};
//---------------------------------------------------------------------------
bool Logic::hasMoves(int x, int y, short color) {
	// �������� �� �����
	bool isKing = (color == 3 || color == 4);

	// ��������������� ���������� ��� ����������� ��������
	const int directions[4][2] = {
		{-1, -1}, {-1, 1}, {1, -1}, {1, 1}
	};

	if (isKing) {
		// ���������� ���� ��������
    	int teammates = (color == 1 || color == 3) ? 1 : 2;  // �������
		int teammatesKing = (teammates == 1) ? 3 : 4;

		// ���������� ���� ����������
		int opponent = (color == 1 || color == 3) ? 2 : 1;
		int opponentKing = (opponent == 1) ? 3 : 4;

    	int dx = 1, dy = 1;
		bool directions_stop[4] = {false, false, false, false};
		bool met_opponent_by_direction[4] = {false, false, false, false};
		int dx_start[4] = {0, 0, 0, 0};
		int dx_stop[4] = {0, 0, 0, 0};
		while(dx <= 7) {

			for (int d = 0; d < 4; d++) {
				if (directions_stop[d]) {
					continue;
				}

				int x_multiplyer = directions[d][0];
				int y_multiplyer = directions[d][1];

				int nx =  x + (x_multiplyer * dx);
				int ny = y + (y_multiplyer * dx);

				if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) {
					directions_stop[d] = true;
					dx_stop[d] = met_opponent_by_direction[d] ? dx - 1 : dx ;
					continue;
				}

				if (met_opponent_by_direction[d] && (dx_start[d] == 0 || dx_start[d] == 1)) {
					dx_start[d] = dx;
					return true;
				}
				if (this->matrix[nx][ny].first == teammates ||
				this->matrix[nx][ny].first == teammatesKing) {
					directions_stop[d] = true;
					dx_stop[d] = dx;
					continue;
				} else if ((this->matrix[nx][ny].first == opponent ||
				this->matrix[nx][ny].first == opponentKing) &&
				 met_opponent_by_direction[d] == false) {
					met_opponent_by_direction[d] = true;
				} else if ((this->matrix[nx][ny].first == opponent ||
				this->matrix[nx][ny].first == opponentKing) &&
				met_opponent_by_direction[d] == true) {
					dx_stop[d] = dx;
					directions_stop[d] = true;
					continue;
				}
				if (dx_start[d] == 0) {
					return true;
				}
			}
			dx++;
		}
		return false;

	} else {
		// ������ ��� ������� �����
		int direction = (color == 1) ? -1 : 1; // ����������� ��������: ����� �����, ������ ����
		for (int i = 0; i < 2; i++) {
			int dx = directions[i + (direction > 0 ? 2 : 0)][1];
			int nx = x + direction, ny = y + dx;

			// �������� �� ������� ����
			if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
				if (this->matrix[nx][ny].first == 0) {
					return true;
				} else if (this->matrix[nx][ny].first != color) {
					// �������� ����������� ������ ����� ����������
					int nnx = nx + direction, nny = ny + dx;
					if (nnx >= 0 && nnx < 8 && nny >= 0 && nny < 8 && this->matrix[nnx][nny].first == 0) {
						return true;
					}
				}
			}
		}
        // �������� ������ ����� ���������� �����
		for (int i = 0; i < 2; i++) {
			int dx = directions[i + (direction > 0 ? 0 : 2)][1];
			int nx = x - direction, ny = y + dx;
			// �������� �� ������� ����
			if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
				if (this->matrix[nx][ny].first != color && this->matrix[nx][ny].first != 0) {
					// �������� ����������� ������ ����� ����������
					int nnx = nx - direction, nny = ny + dx;
					if (nnx >= 0 && nnx < 8 && nny >= 0 && nny < 8 && this->matrix[nnx][nny].first == 0) {
						return true;
					}
				}
			}
		}
	}
	return false;
}
//---------------------------------------------------------------------------
bool Logic::hasMovesByColor(short color) {
    // ���������� ���� ��������
	int teammates = (color == 1 || color == 3) ? 1 : 2;  // �������
	int teammatesKing = (teammates == 1) ? 3 : 4;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->matrix[i][j].first == teammates ||
			this->matrix[i][j].first == teammatesKing) {
				if (this->hasMoves(i,j, this->matrix[i][j].first)) {
					return true;
				}
			}
		}
	}
	return false;
}
//---------------------------------------------------------------------------
int Logic::didGameEnd(){
	if (this->white_count <= 0) {
		return 2;
	} else if (this->black_count <= 0) {
		return 1;
	} else if (!this->hasMovesByColor(1)) {
		return 2;
	} else if (!this->hasMovesByColor(2)) {
    	return 1;
	} else if (this->timer_white <= 0 && this->is_timer) {
		return 2;
	} else if (this->timer_black <= 0 && this->is_timer) {
		return 1;
	}
	return 0;
}
//---------------------------------------------------------------------------
int Logic::GetWhiteTimer(){
	return this->timer_white;
}
//---------------------------------------------------------------------------
int Logic::GetBlackTimer(){
	return this->timer_black;
}
//---------------------------------------------------------------------------
void Logic::SetWhiteTimer(int seconds) {
	this->timer_white = seconds;
}
//---------------------------------------------------------------------------
void Logic::SetBlackTimer(int seconds) {
	this->timer_black = seconds;
}
//---------------------------------------------------------------------------
bool Logic::isTimer() {
	return this->is_timer;
}
#pragma package(smart_init)
