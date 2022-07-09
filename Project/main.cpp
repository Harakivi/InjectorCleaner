#include "..\Sources\Utils\CallbackWrapper.h"
#include "..\Sources\Utils\Threads.h"
#include "Board.h"
#include "Drivers.h"

typedef Hardware::InjectorCleaner::Board Board;
typedef Hardware::InjectorCleaner::Drivers<Board> Drivers;
typedef Board::WDG_Timer WDG_Timer;

int main()
{
  Board::Init();
  Drivers::Init();

  while (1)
  {
    Drivers::Run();
    WDG_Timer::ResetCounter();
  }
}
