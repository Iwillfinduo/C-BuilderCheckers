//---------------------------------------------------------------------------

#ifndef LogicH
#define LogicH
//---------------------------------------------------------------------------
#include <vector>
#include <utility>
#include "Logic.h"

//---------------------------------------------------------------------------
class Logic {
	public:
	  Logic() {}
	  Logic(int timer);
	  //int StartTimer();
	  //int StopTimer();
	  std::vector<std::pair<int, int> > GetMoves(short color, short index);
	  std::pair<int, std::pair<int,int> > ReadMove(short color, short index, short place_i, short place_j);
	  //int SetField(std::pair<int,int> upper_left_angle,
	  // std::pair<int, int> lower_right_angle);
	  //std::vector<std::vector<int> > GetMatrix();

	private:
	  int timer;
	  bool isPieceUnderAttack(int x, int y, short color);
	  bool isAnyPieceUnderAttackAndHasMoves(short color);
	  bool hasMoves(int x, int y, short color);
	  std::pair<int, int> matrix[8][8]; // pair color and id of figure
	  std::vector<std::pair<int,int> > black_cords;
	  std::vector<std::pair<int, int> > white_cords;
	  std::pair<int, int> piece_with_extra_move;
	  bool is_white_move;
	  bool is_extra_move;
	  bool is_it_your_move(short color);
	  int last_i;
	  int last_j;
	  //std::map<int, int> log;
};

#endif
