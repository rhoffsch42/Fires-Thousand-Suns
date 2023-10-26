
#include "BuffManager.h"
#include "../FuncLib.h"

constexpr int32 UNREAL_ENUM_MAX_MEMBER_COUNT = 256;

UBuffManager::UBuffManager() {
	PrimaryComponentTick.bCanEverTick = false;
	this->_buffs.Reserve(UNREAL_ENUM_MAX_MEMBER_COUNT);
	this->_buffs.Init(nullptr, UNREAL_ENUM_MAX_MEMBER_COUNT);
}

void UBuffManager::BeginPlay() {
	Super::BeginPlay();
}

void UBuffManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void	UBuffManager::AddBuff(ABuff* Buff) {
	int32	enumVal = CAST_NUM(Buff->BuffType);
	if (!this->_buffs[enumVal]) {
		this->_buffs[enumVal] = Buff;
	} else {
		// merging with one ot these:
		this->_buffs[enumVal]->Destroy(); // ie replace
		this->_buffs[enumVal] = Buff;
		//this->_buffs[enumVal]->Absorb(Buff);
		//this->_buffs[enumVal]->Stack(Buff); // list ?
		/*
			a buff can be stronger than another one but expire sooner
			we need to stack them, and display only the strongest at the current time
		*/
	}
	this->OnBuffAdded.Broadcast(Buff);
}

void	UBuffManager::RemoveBuff(ABuff* Buff) {
	int32	enumVal = CAST_NUM(Buff->BuffType);
	if (!this->_buffs[enumVal]) {
		// should not happen
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("UBuffManager::RemoveBuff() error: trying to remove an unregistered buff : %d"), Buff));
	} else {
		// unmerging with one ot these:
		this->_buffs[enumVal] = nullptr;
		//this->_buffs[enumVal]->Absorb(Buff); // obsolete, original buff was absorbed and a special EndPlay/destruction should have been called
		//this->_buffs[enumVal]->UnStack(Buff); // list ?
	}
}

ABuff*	UBuffManager::GetBuff(EBuffType BuffType) const {
	return this->_buffs[CAST_NUM(BuffType)];
}
