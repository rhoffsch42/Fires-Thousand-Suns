// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "../Systems/HealthManager.h"
#include "BuffMoltenShell.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ABuffMoltenShell : public ABuff
{
	GENERATED_BODY()
public:
	ABuffMoltenShell();
	ABuffMoltenShell(double HP);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHealthManager* HealthManager = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double	ShellAbsorption = 0.75;
private:

};
