#include "CGameMode.h"
#include "Characters/CPlayer.h"

ACGameMode::ACGameMode()
{
	DefaultPawnClass = ACPlayer::StaticClass();
}