
#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "../Systems/HealthManager.h"
#include "BuffMoltenShell.generated.h"


UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ABuffGuard : public ABuff
{
	GENERATED_BODY()
public:
	ABuffGuard();
	virtual void	OnConstruction(const FTransform& Transform) override;// todo check every UObject that need to constructs UObjects in ctor
	virtual void	ApplyTo(AActor* Target);

	UFUNCTION(BlueprintCallable)
	virtual void	OnGuardHpEmpty();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHealthManager* HealthManager = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double	Absorption = 0.75;
protected:
	APawn* _TargetPawn = nullptr;
private:
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ABuffMoltenShell : public ABuffGuard
{
	GENERATED_BODY()
public:
	ABuffMoltenShell();
private:

};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ABuffVaalMoltenShell : public ABuffGuard
{
	GENERATED_BODY()
public:
	ABuffVaalMoltenShell();
private:

};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ABuffSteelskin : public ABuffGuard
{
	GENERATED_BODY()
public:
	ABuffSteelskin();
	virtual void	ApplyTo(AActor* Target);
	virtual void	Remove();
private:

};
