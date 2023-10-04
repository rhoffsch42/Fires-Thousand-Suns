
#include "FuncLib.h"

constexpr float D_LEN = 5.0f;

bool	UFuncLib::CheckObject(UObject* obj, FString ErrorMsg) {
	if (!obj) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, ErrorMsg);
		return false;
	}
	return true;
}

void	UFuncLib::PrintStats(const FPlayerStats& Stats) {
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Less Damage Taken       : %lf"), Stats.CustomLessDamage));
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Fortify Stacks          : %lf"), Stats.FortifyEffect));
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Spell Supression Effect : %lf"), Stats.SpellSuppressionEffect));
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Spell Supression Chance : %lf"), Stats.SpellSuppressionChance));
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Fire Resistance         : %lf"), Stats.FireResistance));
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Life Regeneration       : %lf"), Stats.LifeRegeneration));
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Life                    : %lf"), Stats.Life));
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Movement Speed          : %lf"), Stats.MovementSpeed));
}
