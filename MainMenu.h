//---------------------------------------------------------------------------

#ifndef MainMenuH
#define MainMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TButton *NewGameBtn;
	TButton *LoadBtn;
	TButton *RulesBtn;
	TButton *AboutBtn;
	TButton *ExitBtn;
	TShape *Shape1;
	TShape *Shape2;
	TShape *Shape3;
	TShape *Shape4;
	void __fastcall ExitBtnClick(TObject *Sender);
	void __fastcall AboutBtnClick(TObject *Sender);
	void __fastcall NewGameBtnClick(TObject *Sender);
	void __fastcall RulesBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
