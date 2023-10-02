
#include "FiresThousandSunsPlayerState.h"

constexpr float D_LEN = 5.0f;

AFiresThousandSunsPlayerState::AFiresThousandSunsPlayerState() {
}

void	AFiresThousandSunsPlayerState::PrintPlayerStats() const {
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Less Damage Taken       : %lf"), this->PlayerStats.CustomLessDamage));
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Fortify Stacks          : %lf"), this->PlayerStats.FortifyStacks));
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Spell Supression Effect : %lf"), this->PlayerStats.SpellSuppressionEffect));
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Fire Resistance         : %lf"), this->PlayerStats.FireResistance));
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Life Regeneration       : %lf"), this->PlayerStats.LifeRegeneration));
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Life                    : %lf"), this->PlayerStats.Life));
	GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Movement Speed          : %lf"), this->PlayerStats.MovementSpeed));
}
