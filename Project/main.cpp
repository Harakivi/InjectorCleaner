#include "..\Sources\Utils\CallbackWrapper.h"
#include "..\Sources\Utils\Threads.h"
#include "Board.h"
#include "Drivers.h"

typedef Hardware::InjectorCleaner::Board Board;
typedef Hardware::InjectorCleaner::Drivers<Board> Drivers;

int main()
{
  Board::Init();
  Drivers::Init();

  while (1)
  {
    Drivers::Run();
  }
}
