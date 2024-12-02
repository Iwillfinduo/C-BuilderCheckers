//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Logic.cpp"
#include "NewGameMenu.h"
#include "GameWindow.h"
#include "MainMenu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BitBtn1Click(TObject *Sender)
{
	int timer;
	switch (Form2->ComboBox1->ItemIndex) {
		case 0:
			timer = 0;
			break;
		case 1:
			timer = 5;
			break;
		case 2:
			timer = 15;
			break;
		case 3:
			timer = 45;
			break;
	}
	Logic logic = Logic(timer);
	Form3->SetLogic(logic);
	Form3->Show();
	Form1->Hide();
	Form2->Close();

}
//---------------------------------------------------------------------------
