
#include "BuffFortify.h"
#include "../FuncLib.h"

ABuffFortify::ABuffFortify() {
	this->BuffType = EBuffType::FortifyStacks;
	FString MatPath("/Script/Engine.Material'/Game/LevelPrototyping/Materials/fortify_UIMat.fortify_UIMat'");
	this->IconMaterial = LoadObject<UMaterial>(this, *MatPath);
	UFuncLib::CheckObject(this->IconMaterial, FString("LoadObject<UMaterial>() failed : ").Append(MatPath));
}

FString	ABuffFortify::GetDisplayString() const {
	return FString::FromInt(this->FortifyStacks);
}
