
#include "Buff.h"
#include "Engine/EngineTypes.h"

ABuff::ABuff() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->_DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default"));
	this->SetRootComponent(this->_DefaultSceneRoot);
	this->InitialLifeSpan = this->_baseDuration;
}

void	ABuff::BeginPlay() {
	Super::BeginPlay();
}
void	ABuff::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("endplay: %d"), (int32)EndPlayReason));
	this->Remove();
}

void	ABuff::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void	ABuff::ApplyTo(AActor* Target) {
	this->_target = Target;
	this->SetLifeSpan(this->_baseDuration);
}

void	ABuff::Remove() {
	// Child class will define it
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
