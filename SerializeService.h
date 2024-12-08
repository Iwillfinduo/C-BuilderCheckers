//---------------------------------------------------------------------------

#ifndef SerializeServiceH
#define SerializeServiceH

#include "Logic.h"
#include <vcl.h>
//---------------------------------------------------------------------------
// Служебный класс для сериализации/десериализации и сохранения/загрузки игры по пути
class Serializer {
  public:
	void SaveLogicObject (Logic logic, AnsiString path);
	Logic LoadFromObject (AnsiString path);
  private:
};
//---------------------------------------------------------------------------
#endif
