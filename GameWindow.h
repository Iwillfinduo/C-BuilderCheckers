//---------------------------------------------------------------------------

#ifndef GameWindowH
#define GameWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
#include "Logic.h"
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TShape *S60;
	TShape *S61;
	TShape *S62;
	TShape *S63;
	TShape *S64;
	TShape *S65;
	TShape *S66;
	TShape *S67;
	TShape *S70;
	TShape *S71;
	TShape *S72;
	TShape *S73;
	TShape *S74;
	TShape *S75;
	TShape *S76;
	TShape *S77;
	TShape *S40;
	TShape *S41;
	TShape *S42;
	TShape *S43;
	TShape *S44;
	TShape *S45;
	TShape *S46;
	TShape *S47;
	TShape *S50;
	TShape *S51;
	TShape *S52;
	TShape *S53;
	TShape *S54;
	TShape *S55;
	TShape *S56;
	TShape *S57;
	TShape *S20;
	TShape *S21;
	TShape *S22;
	TShape *S23;
	TShape *S24;
	TShape *S25;
	TShape *S26;
	TShape *S27;
	TShape *S30;
	TShape *S31;
	TShape *S32;
	TShape *S33;
	TShape *S34;
	TShape *S35;
	TShape *S36;
	TShape *S37;
	TShape *S00;
	TShape *S01;
	TShape *S02;
	TShape *S03;
	TShape *S04;
	TShape *S05;
	TShape *S06;
	TShape *S07;
	TShape *S10;
	TShape *S11;
	TShape *S12;
	TShape *S13;
	TShape *S14;
	TShape *S15;
	TShape *S16;
	TShape *S17;
	TImage *TimerIMG;
	TShape *EW8;
	TShape *EW9;
	TShape *EW10;
	TShape *EW11;
	TShape *EW4;
	TShape *EW5;
	TShape *EW6;
	TShape *EW7;
	TShape *EW0;
	TShape *EW1;
	TShape *EW2;
	TShape *EW3;
	TShape *EB0;
	TShape *EB4;
	TShape *EB5;
	TShape *EB1;
	TShape *EB6;
	TShape *EB2;
	TShape *EB7;
	TShape *EB3;
	TShape *EB8;
	TShape *EB9;
	TShape *EB10;
	TShape *EB11;
	TLabel *Label2;
	TTimer *Timer1;
	void __fastcall S21ContextPopup(TObject *Sender, TPoint &MousePos,
          bool &Handled);
	void __fastcall TimerIMGClick(TObject *Sender);
	void __fastcall FigureClick(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall CloseMain(TObject *Sender, bool &CanClose);
	void __fastcall PlaceClick(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall TimerEvent(TObject *Sender);
private:
	Logic logic;	// User declarations
	bool is_checked;
	std::vector<TShape*> colored;
	void Uncheck();
	std::pair<int, int> FormIndex(TShape *Shape);
	TShape* CheckedFigure;
	TShape* FindShape(AnsiString comp_name);
	void EndGame();
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
	void SetLogic(Logic logic);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
