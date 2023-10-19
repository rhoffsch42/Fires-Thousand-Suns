
#include "FiresThousandSunsGameInstance.h"
#include "FuncLib.h"

UFiresThousandSunsGameInstance::UFiresThousandSunsGameInstance() {
}

void	UFiresThousandSunsGameInstance::InitSaveGame(FString SaveName) {
	this->Fires_SG = UFiresThousandSunsSaveGame::LoadSave(SaveName);
	if (!this->Fires_SG) {
		this->Fires_SG = UFiresThousandSunsSaveGame::CreateSave(SaveName);
	}
}
