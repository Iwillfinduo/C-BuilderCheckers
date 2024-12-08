//---------------------------------------------------------------------------

#ifndef SerializeServiceH
#define SerializeServiceH

#include "Logic.h"
#include <vcl.h>
//---------------------------------------------------------------------------
class Serializer {
  public:
	void SaveLogicObject (Logic logic, AnsiString path);
	Logic LoadFromObject (AnsiString path);
  private:
};
//---------------------------------------------------------------------------
#endif
