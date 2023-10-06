
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Cooldown.generated.h"

#define RESET_VALUE -999999.9

/**
 * 
 */
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UCooldown : public UObject
{
	GENERATED_BODY()
public:
	UCooldown();
	UCooldown(UObject* WorldObject);

	UFUNCTION(BlueprintCallable)
	bool	TryUse();
	UFUNCTION(BlueprintCallable)
	void	Use();
	UFUNCTION(BlueprintCallable)
	void	Reset();
	UFUNCTION(BlueprintCallable)
	bool	IsReady();
	UFUNCTION(BlueprintCallable)
	double	Remaining();
	UFUNCTION(BlueprintCallable)
	double	RemainingRelative();

	UFUNCTION(BlueprintCallable)
	int32	GetAvailableUses();
	UFUNCTION(BlueprintCallable)
	int32	GetMaxUses() const;
	UFUNCTION(BlueprintCallable)
	void	SetMaxUses(const int32 Uses);
	UFUNCTION(BlueprintCallable)
	void	SetDuration(const double Duration);
	UFUNCTION(BlueprintCallable)
	double	GetDuration() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (ExposeOnSpawn = "true"))
	UObject* World = nullptr;

private:
	double	_duration = 1.0;
	double	_lastUse = RESET_VALUE;
	int32	_availableUses = 1;
	int32	_maxUses = 1;

	void	_update();//could call this during a tick()
	double	_safeGetTimeSeconds() const;
};
