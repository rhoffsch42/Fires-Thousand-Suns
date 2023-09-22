
#include "Buff.h"
#include "BuffManager.h"
#include "Engine/EngineTypes.h"

ABuff::ABuff() {
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
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("ABuff::EndPlay():%d. Removed buff."), (int32)EndPlayReason));
}

void	ABuff::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void	ABuff::ApplyTo(AActor* Target) {
	this->_target = Target;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(">>> ABuff::ApplyTo(AActor* Target) _target : %d "), this->_target));
	UBuffManager* bm = this->_target->GetComponentByClass<UBuffManager>();// not mandatory
	if (bm) {
		bm->AddBuff(this);
	}
	//else {
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("ABuff::Remove() error: target has no BuffManager Component."));
	//}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(">>> ABuff::ApplyTo(AActor* Target) setLifeSpan(_baseDuration) : %f "), this->_baseDuration));
	this->SetLifeSpan(this->_baseDuration);
}

void	ABuff::Remove() {
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(">>> ABuff::Remove() _target : %d "), this->_target));
	UBuffManager* bm = this->_target->GetComponentByClass<UBuffManager>();// not mandatory
	if (bm) {
		bm->RemoveBuff(this);
	}
	//else {
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("ABuff::Remove() error: target has no BuffManager Component."));
	//}
}

void	ABuff::SetBaseDuration(double NewDuration) {
	this->_baseDuration = NewDuration;// save
	this->InitialLifeSpan = NewDuration;
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
		this->EndPlay(EEndPlayReason::Destroyed);
	}
}

void	ABuff::_UpdateDuration(double NewDuration) {
	this->SetLifeSpan(NewDuration); // it overrides InitialLifeSpan too..
	this->InitialLifeSpan = this->_baseDuration; // ..so we restore it 
}

double	ABuff::GetBaseDuration() const { return this->InitialLifeSpan; }
double	ABuff::GetRemainingDuration() const { return this->GetLifeSpan(); }
