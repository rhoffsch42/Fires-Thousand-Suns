
#include "FiresThousandSunsSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "FuncLib.h"

UFiresThousandSunsSaveGame* UFiresThousandSunsSaveGame::LoadSave(FString InSlotName) {
    D(FString("Save Game Path : ").Append(FPaths::EngineSavedDir()));
    D(FString("Save to user Dir ? ").Append(FPaths::ShouldSaveToUserDir() ? "yes" : "no"));
    USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(InSlotName, 0);
    UFiresThousandSunsSaveGame* SaveGameObject = nullptr;
    
    if (UFuncLib::CheckObject(LoadedGame, "Failed to load SaveGame")) {
        SaveGameObject = Cast<UFiresThousandSunsSaveGame>(LoadedGame);
        if (UFuncLib::CheckObject(SaveGameObject, "Cast failed UFiresThousandSunsSaveGame")) {
            D_(GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Saved game found. Loaded.")));
            if (SaveGameObject->bKrangledUnlocked) {
                D(FString("bKrangledUnlocked true"));
            }
        }
    }

    //if (SaveGameObject) { D(SaveGameObject->ToString()); }
    return SaveGameObject;
}

UFiresThousandSunsSaveGame* UFiresThousandSunsSaveGame::CreateSave(FString InSlotName, TSubclassOf<UFiresThousandSunsSaveGame> SaveGameClass) {
    D(FString("Save Game Path : ").Append(FPaths::EngineSavedDir()));
    D(FString("Save to user Dir ? ").Append(FPaths::ShouldSaveToUserDir() ? "yes" : "no"));
    //USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(SaveGameClass ? SaveGameClass->StaticClass() : UFiresThousandSunsSaveGame::StaticClass());
    USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(UFiresThousandSunsSaveGame::StaticClass());
    UFuncLib::CheckObject(SaveGame, "UFiresThousandSunsSaveGame::CreateSave() Failed to create USaveGame");
    UFiresThousandSunsSaveGame* Fires_SG = Cast<UFiresThousandSunsSaveGame>(SaveGame);
    if (UFuncLib::CheckObject(Fires_SG, "UFiresThousandSunsSaveGame::CreateSave() Failed to cast as UFiresThousandSunsSaveGame")) {
        Fires_SG->SlotName = InSlotName;
        Fires_SG->Save();
    }

    //D(Fires_SG->ToString());
    return Fires_SG;
}

///////////////////////////////////////////////////

UFiresThousandSunsSaveGame::UFiresThousandSunsSaveGame() {
}

bool    UFiresThousandSunsSaveGame::Save() {
    //D(this->ToString());
    bool success = UGameplayStatics::SaveGameToSlot(this, this->SlotName, 0);
    if (success) {
        D(FString("Saved !"));
    } else {
        UFuncLib::CheckObject(nullptr, "Failed to save game.");
    }
    return success;
}

void	UFiresThousandSunsSaveGame::TryUnlockKrangledMode(int32 PhasesSurvived) {
    if (!this->bKrangledUnlocked && PhasesSurvived >= 5 && this->PlayerStats == FPlayerStats()) {
        this->bKrangledUnlocked = true;
        this->Save();
        D(FString("bKrangledUnlocked true"));
    }
}

FString	UFiresThousandSunsSaveGame::ToString() const {
    return FString::Printf(TEXT("[name: %s, master:%f, effects:%f, music:%f, dialogues:%f, ambient:%f]\n\
[moveSpeed:%f, life:%d, lifeRegen:%d, fireRes:%f, suppChance:%f, suppEffect:%f, fortify:%f, lessDmg:%f]"),
        *this->SlotName,
        this->MasterVolume,
        this->EffectsVolume,
        this->MusicVolume,
        this->DialoguesVolume,
        this->AmbientVolume,

        this->PlayerStats.MovementSpeed,
        (int32)this->PlayerStats.Life,
        (int32)this->PlayerStats.LifeRegeneration,
        this->PlayerStats.FireResistance,
        this->PlayerStats.SpellSuppressionChance,
        this->PlayerStats.SpellSuppressionEffect,
        this->PlayerStats.FortifyEffect,
        this->PlayerStats.CustomLessDamage
    );
}

FString	UFiresThousandSunsSaveGame::GetSlotName() const { return this->SlotName; }
