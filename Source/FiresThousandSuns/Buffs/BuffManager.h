
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Buff.h"

#include "BuffManager.generated.h"

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuffAdded, ABuff*, Buff);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRESTHOUSANDSUNS_API UBuffManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuffManager();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void	AddBuff(ABuff* Buff);
	UFUNCTION(BlueprintCallable)
	void	RemoveBuff(ABuff* Buff);
	UFUNCTION(BlueprintCallable)
	ABuff*	GetBuff(EBuffType BuffType) const;

	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FBuffAdded	OnBuffAdded;

protected:
	virtual void BeginPlay() override;
private:
	// Maximum 256 different buffs EBuffType (Unreal Enum size being 1bytes)
	TArray<ABuff*>	_buffs;
};
