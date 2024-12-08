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
	  Logic(std::vector<std::vector<std::pair<int,int> > > matrix, int move, int extra_move, int is_timer, int timer_white, int timer_black);
	  //int StartTimer();
	  //int StopTimer();
	  std::vector<std::pair<int, int> > GetMoves(short color, short index);
	  std::pair<int, std::pair<int,int> > ReadMove(short color, short index, short place_i, short place_j);
	  //int SetField(std::pair<int,int> upper_left_angle,
	  //std::pair<int, int> lower_right_angle);
	  //std::vector<std::vector<int> > GetMatrix();
	  int didGameEnd();
	  int GetWhiteTimer();
	  int GetBlackTimer();
	  void SetWhiteTimer(int seconds);
	  void SetBlackTimer(int seconds);
	  bool isTimer();
	  bool is_it_your_move(short color);
	  bool isExtraMove();
	  std::vector<std::vector<std::pair<int,int> > > GetMatrix();

	private:
	  int timer_white;
	  int timer_black;
	  int white_count;
	  int black_count;
	  bool is_timer;
	  bool isPieceUnderAttack(int x, int y, short color);
	  bool isAnyPieceUnderAttackAndHasMoves(short color);
	  bool hasMoves(int x, int y, short color);
	  bool is_last_kill_moves;
	  std::pair<int, int> matrix[8][8]; // pair color and id of figure
	  std::pair<int, int> piece_with_extra_move;
	  bool is_white_move;
	  bool is_extra_move;
	  int last_i;
	  int last_j;
	  bool hasMovesByColor(short color);
	  //std::map<int, int> log;
};

#endif
