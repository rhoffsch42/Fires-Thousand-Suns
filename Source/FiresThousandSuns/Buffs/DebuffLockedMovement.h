// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "DebuffLockedMovement.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ADebuffLockedMovement : public ABuff
{
	GENERATED_BODY()
public:
	ADebuffLockedMovement();
	virtual void	ApplyTo(AActor* Target);
	virtual void	Remove();

private:
};
