//---------------------------------------------------------------------------

#ifndef LogicH
#define LogicH
//---------------------------------------------------------------------------
#include <vector>
#include <utility>
#include "Logic.h"

//---------------------------------------------------------------------------
// ��������� �����, backend ����, ��� �������������� ��� ������ �� �������� � UI
class Logic {
	public:
	  Logic() {}
	  Logic(int timer); // ������� ������������ ��� �������� ����
	  Logic(std::vector<std::vector<std::pair<int,int> > > matrix,
	   int move, int extra_move, int is_timer,
		int timer_white, int timer_black); // ����������� ��� �������� ����
	  std::vector<std::pair<int, int> > GetMoves(short color, short index); // ��������� ����� ��� �����
	  std::pair<int, std::pair<int,int> > ReadMove(short color, short index, short place_i, short place_j); // ���������� ���� �����
	  int didGameEnd(); // �������� ����������� �� ����
	  int GetWhiteTimer(); // ������� � ������� �������
	  int GetBlackTimer();
	  void SetWhiteTimer(int seconds);
	  void SetBlackTimer(int seconds);
	  bool isTimer(); // �������� ���� �� � ���� ������
	  bool is_it_your_move(short color); // �������� ��� ���
	  bool isExtraMove(); // ������ ���� �� �������������� ���
	  std::vector<std::vector<std::pair<int,int> > > GetMatrix(); // ������ ������� ��� ������������

	private:
	  int timer_white; // �������, �������� � �����
	  int timer_black;
	  int white_count;
	  int black_count;
	  bool is_timer;
	  bool is_white_move;
	  bool is_extra_move;
	  bool is_last_kill_moves;

	  // ��������� �������
	  bool isPieceUnderAttack(int x, int y, short color);
	  bool isAnyPieceUnderAttackAndHasMoves(short color);
	  bool hasMoves(int x, int y, short color);
	  bool hasMovesByColor(short color);

	  //�������� �������� ����
	  std::pair<int, int> matrix[8][8]; // pair color and id of figure

	  // ����������� ������� �������� � ������������ �����������
	  std::pair<int, int> piece_with_extra_move;
	  int last_i;
	  int last_j;
};

#endif
