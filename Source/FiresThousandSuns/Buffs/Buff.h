// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Buff.generated.h"

#define BUFF_DEFAULT_DURATION	50.0

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ABuff : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuff();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void	ApplyTo(AActor* Target);
	UFUNCTION(BlueprintCallable)
	void	Remove();
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
	bool	bIsDebuff = false;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void	_UpdateDuration(double Duration);

private:	
	TObjectPtr<USceneComponent> _DefaultSceneRoot;

	AActor* _target = nullptr;
	double	_baseDuration = BUFF_DEFAULT_DURATION;
};
