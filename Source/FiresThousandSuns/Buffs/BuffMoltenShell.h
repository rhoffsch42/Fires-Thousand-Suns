
#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "../Systems/HealthManager.h"
#include "BuffMoltenShell.generated.h"


UCLASS()
class FIRESTHOUSANDSUNS_API ABuffGuard : public ABuff
{
	GENERATED_BODY()
public:
	ABuffGuard();
	ABuffGuard(double HP);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHealthManager* HealthManager = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double	Absorption = 0.75;
private:

};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ABuffMoltenShell : public ABuffGuard
{
	GENERATED_BODY()
public:
	ABuffMoltenShell();
	ABuffMoltenShell(double HP);
private:

};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ABuffVaalMoltenShell : public ABuffGuard
{
	GENERATED_BODY()
public:
	ABuffVaalMoltenShell();
	ABuffVaalMoltenShell(double HP);
private:

};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ABuffSteelskin : public ABuffGuard
{
	GENERATED_BODY()
public:
	ABuffSteelskin();
	ABuffSteelskin(double HP);
private:

};
