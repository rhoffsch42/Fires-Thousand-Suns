
#include "BuffRubyFlask.h"
#include "../FuncLib.h"

ABuffRubyFlask::ABuffRubyFlask() {
	this->BuffType = EBuffType::RubyFlask;
	FString MatPath("/Script/Engine.Material'/Game/LevelPrototyping/Materials/flamer_UIMat.flamer_UIMat'");
	this->IconMaterial = LoadObject<UMaterial>(this, *MatPath);
	UFuncLib::CheckObject(this->IconMaterial, FString("LoadObject<UMaterial>() failed : ").Append(MatPath));
}

//void	ABuffRubyFlask::ApplyTo(AActor* Target) {
//	Super::ApplyTo(Target);
//}
//
//void	ABuffRubyFlask::Remove() {
//}
