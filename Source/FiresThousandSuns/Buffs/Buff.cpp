
#include "Buff.h"
#include "BuffManager.h"
#include "Engine/EngineTypes.h"
#include "../FuncLib.h"

ABuff::ABuff() {
	// WHEREAMI(this);
	PrimaryActorTick.bCanEverTick = false;

	this->_DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default"));
	this->SetRootComponent(this->_DefaultSceneRoot);
	this->InitialLifeSpan = this->_baseDuration;
}

void	ABuff::BeginPlay() {
	Super::BeginPlay();
}

void	ABuff::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	this->Remove();
	this->BuffExpired.Broadcast(this);
}

void	ABuff::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

// string to display in UI (eg: buff stacks, power, state, etc...)
FString	ABuff::GetDisplayString() const {
	return FString("");
}


void	ABuff::ApplyTo(AActor* Target) {
	this->_Target = Target;
	UBuffManager* bm = this->_Target->GetComponentByClass<UBuffManager>(); // not mandatory
	if (bm) {
		bm->AddBuff(this);
	}
	this->SetLifeSpan(this->_baseDuration);
}

void	ABuff::Remove() {
	if (this->_Target) {
		UBuffManager* bm = this->_Target->GetComponentByClass<UBuffManager>(); // not mandatory
		if (bm) {
			bm->RemoveBuff(this);
		}
	}
}

void	ABuff::SetBaseDuration(double NewDuration) {
	this->_baseDuration = NewDuration; // save it
	this->InitialLifeSpan = NewDuration; // because SetLifeSpan() will override it
}

void	ABuff::AddDuration(double Duration) {
	Duration = std::max(0.0, Duration);
	this->_UpdateDuration(this->GetLifeSpan() + Duration);
}

void	ABuff::RemoveDuration(double Duration) {
	Duration -= std::min(0.0, Duration);
	if (this->GetLifeSpan() > Duration) {
		this->_UpdateDuration(this->GetLifeSpan() - Duration);
	} else { // puting negative value will set no/infinite lifespan, we don't want that.
		// this->_UpdateDuration(0.001);
		// this->EndPlay(EEndPlayReason::Destroyed);
		this->Destroy();
	}
}

void	ABuff::_UpdateDuration(double NewDuration) {
	this->SetLifeSpan(NewDuration); // it overrides InitialLifeSpan too..
	this->InitialLifeSpan = this->_baseDuration; // ..so we restore it 
}

double	ABuff::GetBaseDuration() const { return this->InitialLifeSpan; }
double	ABuff::GetRemainingDuration() const { return this->GetLifeSpan(); }
