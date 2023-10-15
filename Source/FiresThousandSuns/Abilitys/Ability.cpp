#include "Ability.h"
#include "../Funclib.h"

UAbility::UAbility() {
	FString name = FString::FormatAsNumber((int64)this);
	this->Cooldown = CreateDefaultSubobject<UCooldown>(*name); 
	if (UFuncLib::CheckObject(this->Cooldown, FString("UAbility() NewObject<UCooldown>() failed : "))) {
		this->Cooldown->World = this->GetWorld();
		//UFuncLib::CheckObject(this->Cooldown->World, FString("UAbility() GetWorld() failed "));
	}
}

void	UAbility::TryActivate(FEffectParameters Parameters) {
	if (this->Cooldown->IsReady()) {
		this->Activate(Parameters);
	} else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("[Ability] failed to used, remaining : %lf sec"), this->Cooldown->Remaining()));
	}
}

void	UAbility::Activate(FEffectParameters Parameters) {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("[Ability] used ! CD:%d "), this->Cooldown->GetAvailableUses()));
	this->Cooldown->Use();
}

void	UAbility::SetNewMaterial(UObject* Outer, const FString MatPath) {
	this->IconMaterial = LoadObject<UMaterial>(this->GetWorld(), *MatPath);
	UFuncLib::CheckObject(this->IconMaterial, FString("LoadObject<UMaterial>() failed : ").Append(MatPath));
	//tmpImage->SetBrush(UWidgetBlueprintLibrary::MakeBrushFromTexture(tempTexture));
}
