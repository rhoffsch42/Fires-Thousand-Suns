// Fill out your copyright notice in the Description page of Project Settings.


#include "Sun.h"
#include "../FiresThousandSunsGameMode.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASun::ASun() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->_DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default"));
	this->SetRootComponent(this->_DefaultSceneRoot);
	//this->_initComponents();
}

void	ASun::_initComponents() {
	/*
		static ConstructorHelpers::FObjectFinder<UStaticMesh>	mesh(TEXT("/Engine/EditorMeshes/EditorSphere.EditorSphere"));
	static ConstructorHelpers::FObjectFinder<UMaterial>		material(TEXT("/Game/LevelPrototyping/Material/magma_Mat"));
	if (0) {
		// DefaultSceneRoot ?

		// CollisionSphere 
		this->CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));

		// Sphere Static Mesh
		this->SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
		if (mesh.Succeeded()) {
			this->SphereMesh->SetStaticMesh(mesh.Object);
		}

		// Material
		if (material.Succeeded()) {
			this->_storedMaterial = material.Object;
		}
	}
	else {
		this->_DefaultSceneRoot = Cast<USceneComponent>(this->AddComponentByClass(USceneComponent::StaticClass(), true, this->GetTransform(), false));
		this->CollisionSphere = Cast<USphereComponent>(this->AddComponentByClass(USphereComponent::StaticClass(), true, this->GetTransform(), false));
		this->SphereMesh = Cast<UStaticMeshComponent>(this->AddComponentByClass(UStaticMeshComponent::StaticClass(), true, this->GetTransform(), false));
		if (mesh.Succeeded()) {
			this->SphereMesh->SetStaticMesh(mesh.Object);
		}
		if (material.Succeeded()) {
			this->_storedMaterial = material.Object;
		}
	}

	// edits
	this->_dynamicMaterialInst = UMaterialInstanceDynamic::Create(this->_storedMaterial, this->SphereMesh);
	this->SphereMesh->SetMaterial(0, this->_dynamicMaterialInst);
	this->SphereMesh->GetRelativeTransform().SetScale3D(FVector(1.2275, 1.2275, 1.2275));
	this->CollisionSphere->SetSphereRadius(62.5);
*/
}

// Called when the game starts or when spawned
void	ASun::BeginPlay() {
	Super::BeginPlay();
	this->_spawnLocation = this->GetTargetLocation();
}

// Called every frame
void	ASun::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (this->GetGameTimeSinceCreation() >= this->_timeBeforeMoving) {
		this->bIsMoving = true;
	}
	if (this->bIsMoving) {
		this->Move(DeltaTime);
		if (this->bMavenCancelled && this->IsInRangeForMavenCancellation()) {
			this->SunMavenCancelled.Broadcast();
			this->Destroy();
		}
	}
}

void	ASun::Move(float DeltaTime) {
	FVector location = this->_DefaultSceneRoot->GetComponentLocation();
	FVector diff = this->_destination - location;

	if (diff.Length() <= (DeltaTime * this->_speed)) {
		this->_DefaultSceneRoot->SetWorldLocation(this->_destination);
		this->bIsMoving = false;
		this->Explode();
	} else {
		diff.Normalize();
		diff = diff * DeltaTime * this->_speed;
		this->_DefaultSceneRoot->SetWorldLocation(location + diff);
	}
}

void	ASun::SetDestination(FVector Desto) {
	this->_destination = Desto;
	this->_totalTravelDistance = (Desto - this->_spawnLocation).Length();
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(this->_DefaultSceneRoot->GetComponentLocation(), this->_destination);
	this->_DefaultSceneRoot->SetWorldRotation(rot);
}

void	ASun::Explode() {
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString("Boom"));
	this->SunExploded.Broadcast(this->_DefaultSceneRoot->GetComponentLocation(), this->_damage, this->_explosionRadius);
	this->Destroy();
}

bool	ASun::IsInRangeForMavenCancellation() const {
	double distanceTravelled = (this->GetActorLocation() - this->_spawnLocation).Length();
	//GEngine->AddOnScreenDebugMessage(2222, 15.0f, FColor::Yellow, FString::Printf(TEXT("travel progress: %lf"), (distanceTravelled / this->_totalTravelDistance)));
	return ((distanceTravelled / this->_totalTravelDistance) >= this->_mavenCancellationDistanceThreshold);
}

void	ASun::SetMavenCancellationDistanceThreshold(double Value) {
	this->_mavenCancellationDistanceThreshold = std::min(1.0, std::max(0.0, Value));
}

void	ASun::SetDamage(double Value) {
	this->_damage = std::max(0.0, Value);
}

double	ASun::GetDamage(double Value) const { return this->_damage; }
double	ASun::GetMavenCancellationDistanceThreshold() const { return this->_mavenCancellationDistanceThreshold; }
