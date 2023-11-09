
#include "FiresThousandSunsGameInstance.h"
#include "UI/DebugWidget.h"
#include "FuncLib.h"

UFiresThousandSunsGameInstance::UFiresThousandSunsGameInstance() {
	UFuncLib::Fires_GI = this;
}

void	UFiresThousandSunsGameInstance::InitSaveGame(FString SaveName, TSubclassOf<UFiresThousandSunsSaveGame> SaveGameClass) {
	this->Fires_SG = UFiresThousandSunsSaveGame::LoadSave(SaveName);
	if (!this->Fires_SG) {
		this->Fires_SG = UFiresThousandSunsSaveGame::CreateSave(SaveName, SaveGameClass);
	}
}

void	UFiresThousandSunsGameInstance::AddDebugMessage(FString Message) {
	UDebugWidget* debugW = Cast<UDebugWidget>(this->DebugWidget);
	if (debugW) {
		debugW->AddMessage(Message);
	}
	/*
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "[Fires..GI] Failed to cast Debug Widget");
		}
	}
	*/
}
