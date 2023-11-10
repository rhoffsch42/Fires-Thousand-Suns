
#include "FiresThousandSunsGameInstance.h"
#include "UI/DebugWidget.h"
#include "FuncLib.h"
#include "Misc/DateTime.h"

UFiresThousandSunsGameInstance::UFiresThousandSunsGameInstance() {
	UFuncLib::Fires_GI = this;
	FDateTime now = FDateTime::Now();
	this->StartTime = FString::Printf(TEXT("%d-%02d-%02d_%02d-%02d-%02d_"),
										now.GetYear(), now.GetMonth(), now.GetDay(),
										now.GetHour(), now.GetMinute(), now.GetSecond());
	UFuncLib::LogFile = FString(*FPaths::ProjectLogDir()).Append(this->StartTime).Append(PATH_LOGFILE_RUNTIMEERRORS);
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
