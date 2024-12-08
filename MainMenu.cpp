//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainMenu.h"
#include "ABOUT.h"
#include "Rules.h"
#include "NewGameMenu.h"
#include "GameWindow.h"
#include "SerializeService.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ExitBtnClick(TObject *Sender)
{
	Form1->Close();	
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AboutBtnClick(TObject *Sender)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::NewGameBtnClick(TObject *Sender)
{
	Form2->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RulesBtnClick(TObject *Sender)
{
	Form4->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LoadBtnClick(TObject *Sender)
{
	int Rc;
	Rc = OpenDialog1->Execute();
	if (Rc) {
		Form3->SetLogic(Serializer().LoadFromObject(OpenDialog1->FileName));
		Form3->Show();
		Form1->Hide();
	}
}
//---------------------------------------------------------------------------

