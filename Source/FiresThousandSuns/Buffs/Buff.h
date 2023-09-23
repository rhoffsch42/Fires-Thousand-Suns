// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Buff.generated.h"


#define BUFF_DEFAULT_DURATION	0.0

UENUM(BlueprintType)
enum class EBuffType : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	MoltenShell = 0 UMETA(DisplayName = "MoltenShell"),
	VaalMoltenShell UMETA(DisplayName = "VaalMoltenShell"),
	DebuffLockedMovement UMETA(DisplayName = "DebuffLockedMovement"),
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ABuff : public AActor
{
	GENERATED_BODY()
	
public:
	ABuff();
	virtual void Tick(float DeltaTime) override;

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

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void	_UpdateDuration(double Duration);

	AActor* _target = nullptr;
	TObjectPtr<USceneComponent> _DefaultSceneRoot;
	double	_baseDuration = BUFF_DEFAULT_DURATION;
private:
};
