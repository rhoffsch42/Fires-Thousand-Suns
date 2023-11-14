
#include "Sun.h"
#include "../FiresThousandSunsGameMode.h"
#include "Kismet/KismetMathLibrary.h"


ASun::ASun() {
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
	} else {
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

void	ASun::BeginPlay() {
	Super::BeginPlay();
	this->_SpawnLocation = this->GetTargetLocation();
}

void	ASun::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	if (this->GetGameTimeSinceCreation() >= this->_TimeBeforeMoving) {
		this->bIsMoving = true;
	}
	if (this->bIsMoving) {
		this->Move(DeltaSeconds);
		if (this->bMavenCancelled && this->IsInRangeForMavenCancellation()) {
			this->SunMavenCancelled.Broadcast();
			this->Destroy();
		}
	}
}

void	ASun::Move(float DeltaSeconds) {
	FVector location = this->_DefaultSceneRoot->GetComponentLocation();
	FVector diff = this->_Destination - location;

	if (diff.Length() <= (DeltaSeconds * this->_Speed)) {
		this->_DefaultSceneRoot->SetWorldLocation(this->_Destination);
		this->bIsMoving = false;
		this->Explode();
	} else {
		diff.Normalize();
		diff = diff * DeltaSeconds * this->_Speed;
		this->_DefaultSceneRoot->SetWorldLocation(location + diff);
	}
}

void	ASun::SetDestination(FVector Desto) {
	this->_Destination = Desto;
	this->_TotalTravelDistance = (Desto - this->_SpawnLocation).Length();
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(this->_DefaultSceneRoot->GetComponentLocation(), this->_Destination);
	this->_DefaultSceneRoot->SetWorldRotation(rot);
}

void	ASun::Explode() {
	this->SunExploded.Broadcast(this->_DefaultSceneRoot->GetComponentLocation(), this->_Damage, this->_ExplosionRadius);
	this->Destroy();
}

bool	ASun::IsInRangeForMavenCancellation() const {
	double distanceTravelled = (this->GetActorLocation() - this->_SpawnLocation).Length();
	return ((distanceTravelled / this->_TotalTravelDistance) >= this->_MavenCancellationDistanceThreshold);
}

void	ASun::SetMavenCancellationDistanceThreshold(double Value) {
	this->_MavenCancellationDistanceThreshold = std::min(1.0, std::max(0.0, Value));
}

void	ASun::SetDamage(double Value) {
	this->_Damage = std::max(0.0, Value);
}

double	ASun::GetDamage(double Value) const { return this->_Damage; }
double	ASun::GetMavenCancellationDistanceThreshold() const { return this->_MavenCancellationDistanceThreshold; }
