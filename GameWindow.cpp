//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <utility>
#include "ABOUT.h"
#include "Rules.h"
#include "NewGameMenu.h"
#include "MainMenu.cpp"
#pragma hdrstop

#include "GameWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
// Logic Setter(for parent form)
void TForm3::SetLogic(Logic logic){
	Form3->logic = logic;
	if(logic.isTimer()) {
		Form3->Timer1->Enabled = true;
	}
}
void __fastcall TForm3::S21ContextPopup(TObject *Sender, TPoint &MousePos,
      bool &Handled)
{
	Form3->Label1->Caption = "Clicked";
}
//---------------------------------------------------------------------------
void __fastcall TForm3::TimerIMGClick(TObject *Sender)
{
	//Form3->logic->	
}
//---------------------------------------------------------------------------
// Вспомогательный метод снятия выделения с шашки
void TForm3::Uncheck(){
	if (Form3->is_checked){
		for (int i = 0; i < Form3->colored.end() - Form3->colored.begin(); i++) {
			TShape *colored_shape = Form3->colored[i];
			colored_shape->Brush->Color = clGray;
		}
		Form3->is_checked = false;
		Form3->colored.clear();
	}
}
//---------------------------------------------------------------------------
// Вспомогательный метод нахождения TShape по имени
TShape* TForm3::FindShape(AnsiString comp_name) {
	TComponent *CompShape = Form3->FindComponent(comp_name);
	if (CompShape) {
		TShape *ShapeFocused = (TShape*)(CompShape);
		if (ShapeFocused) {
			return ShapeFocused;
		}
	}

}
//---------------------------------------------------------------------------
// Метод выделения фигуры для хода(Неокончательная версия)
void __fastcall TForm3::FigureClick(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft) {
		Form3->Uncheck();
		// Формирование запроса к logic для получения доступных ходов
		std::pair<int, int> color_index_pair = this->FormIndex((TShape *)Sender);
		std::vector<std::pair<int, int> > moves = Form3->logic.GetMoves(color_index_pair.first, color_index_pair.second);

		//Покраска полей куда можно сделать ход
		for (int i = 0; i < moves.end() - moves.begin(); i++) {
			Form3->CheckedFigure = (TShape *)Sender;
			AnsiString comp_name = "S";
			comp_name += moves[i].first;
			comp_name += moves[i].second;
			//Поиск поля с индексами
			TShape *ShapeFocused = Form3->FindShape(comp_name);
			if (ShapeFocused) {
				// работаем с найденным полем
				ShapeFocused->Brush->Color = clRed;
				Form3->is_checked = true;
				Form3->colored.push_back(ShapeFocused);
			}
		}

	}

}
//---------------------------------------------------------------------------

// Закрытие всех окон(т.к. главное окно скрывается)
void __fastcall TForm3::CloseMain(TObject *Sender, bool &CanClose)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

std::pair<int,int> TForm3::FormIndex(TShape *Shape) {
	if (Shape->Shape == stRectangle) {
	   int i = Shape->Name[2] - '0';
	   int j = Shape->Name[3] - '0';
	   return std::pair<int,int>(i, j);

	} if (Shape->Shape == stEllipse) {
		int color;
		if (Shape->Name[2] == 'W') {
			color = 1;
		}
		if (Shape->Name[2] == 'B') {
			color = 2;
		}
		if (Shape->Name[1] == 'K' && color == 1) {
			color = 3;
		} else if (Shape->Name[1] == 'K' && color == 2) {
			color = 4;
		}
		int index = int(Shape->Tag);
		return std::pair<int,int>(color, index);
	  }
	  return std::pair<int,int>(0, 0);
}
//---------------------------------------------------------------------------
// Обработка хода на стороне UI и запрос к логике (Не окончено: нет дамок
// и неправильно удаляются срубленные фигуры)
void __fastcall TForm3::PlaceClick(TObject *Sender, TMouseButton Button,
	  TShiftState Shift, int X, int Y)
{
	TShape *place = (TShape *)Sender;
	if (Button == mbLeft && place->Brush->Color == clRed) {
		std::pair<int,int> place_index = Form3->FormIndex((TShape *)Sender);
		std::pair<int,int> figure_index = Form3->FormIndex(Form3->CheckedFigure);
		std::pair<int,std::pair<int,int> > move_pair =
		 Form3->logic.ReadMove(figure_index.first,figure_index.second,
		  place_index.first, place_index.second);
		if (move_pair.first) {
			if (move_pair.second.first != -1) {
				AnsiString comp_name;
				if (move_pair.second.first == 1 || move_pair.second.first == 2) {
					comp_name =  "E";
				} else {
					comp_name =  "K";
				}

				if (move_pair.second.first == 1 || move_pair.second.first == 3) {
					comp_name += "W";
				} else if(move_pair.second.first == 2 || move_pair.second.first == 4) {
					comp_name += "B";
				}
				comp_name += move_pair.second.second;
				if (move_pair.second.second < 12 && move_pair.second.second > -1) {
					TShape *killed_fig = Form3->FindShape(comp_name);
					killed_fig->~TShape();
				}

			}

			if (move_pair.first > 1) {
				if (Form3->CheckedFigure->Brush->Color == clBlack) {

				} else {
					Form3->CheckedFigure->Pen->Color = clWhite;
				}
				Form3->CheckedFigure->Brush->Style = bsClear;
				Form3->CheckedFigure->Pen->Width = 20;
				Form3->CheckedFigure->Name[1] = 'K';
			}
			Form3->CheckedFigure->Left = place->Left;
			Form3->CheckedFigure->Top = place->Top;
		}
	}
	Form3->Uncheck();
	if (Form3->logic.didGameEnd()) {
		Form3->EndGame();
	}
}
//---------------------------------------------------------------------------
//Кнопка меню - Выход
void __fastcall TForm3::N5Click(TObject *Sender)
{
   Application->Terminate();
}
//---------------------------------------------------------------------------
// Кнопка меню открытия окна о программе
void __fastcall TForm3::N8Click(TObject *Sender)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
// Кнопка меню открытия правил
void __fastcall TForm3::N7Click(TObject *Sender)
{
	Form4->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::TimerEvent(TObject *Sender)
{
	bool is_white_move = Form3->logic.is_it_your_move(1);
	int timer = is_white_move ? Form3->logic.GetWhiteTimer() : Form3->logic.GetBlackTimer();
	if(timer > 0 ) {
		--timer;
		AnsiString move = is_white_move ? "Белые \n": "Черные \n";
		AnsiString timer_str = AnsiString().sprintf("%02d:%02d",(int)(timer / 60), (int)(timer % 60));
		Form3->Label2->Caption = move + timer_str;
		is_white_move ? Form3->logic.SetWhiteTimer(timer) : Form3->logic.SetBlackTimer(timer);
		if (Form3->logic.didGameEnd()) {
			Form3->Timer1->Enabled = false;
			Form3->EndGame();
		}
		Application->ProcessMessages();
	} else {
		Form3->Timer1->Enabled = false;
	}

}
//---------------------------------------------------------------------------
void TForm3::EndGame() {
	int winner = Form3->logic.didGameEnd();
	winner = 1 ? MessageBox(NULL, "Белые победили поздравляем!!!", "", MB_OK) :
	 MessageBox(NULL, "Черные победили поздравляем!!!", "", MB_OK);
	Application->Terminate();
}
