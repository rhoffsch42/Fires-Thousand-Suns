
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Buff.generated.h"

#define BUFF_DEFAULT_DURATION	0.0

UENUM(BlueprintType)
enum class EBuffType : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	MoltenShell UMETA(DisplayName = "MoltenShell"),
	VaalMoltenShell UMETA(DisplayName = "VaalMoltenShell"),
	Steelskin UMETA(DisplayName = "SteelSkin"),
	DebuffLockedMovement UMETA(DisplayName = "DebuffLockedMovement"),
	RubyFlask UMETA(DisplayName = "RubyFlask"),
	FortifyStacks UMETA(DisplayName = "FortifyStacks")
};

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuffExpired, ABuff*, Buff);

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ABuff : public AActor
{
	GENERATED_BODY()
	
public:
	ABuff();
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	virtual FString	GetDisplayString() const;

	UFUNCTION(BlueprintCallable)
	virtual void	ApplyTo(AActor* Target);
	UFUNCTION(BlueprintCallable)
	virtual void	Remove();
	UFUNCTION(BlueprintCallable)
	void	SetBaseDuration(double NewDuration);
	UFUNCTION(BlueprintCallable)
	void	AddDuration(double Duration);
	UFUNCTION(BlueprintCallable)
	void	RemoveDuration(double Duration);

	UFUNCTION(BlueprintCallable)
	double	GetBaseDuration() const;
	UFUNCTION(BlueprintCallable)
	double	GetRemainingDuration() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool		bIsDebuff = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EBuffType	BuffType = EBuffType::None;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterial* IconMaterial = nullptr;

	// Delegate / Event dispatcher
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FBuffExpired	BuffExpired;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void	_UpdateDuration(double Duration);

	AActor* _Target = nullptr;
	TObjectPtr<USceneComponent> _DefaultSceneRoot;
	double	_baseDuration = BUFF_DEFAULT_DURATION;
private:
};
