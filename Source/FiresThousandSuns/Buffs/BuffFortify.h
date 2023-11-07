#pragma once

#include "CoreMinimal.h"
#include "Buff.h"

#include "BuffFortify.generated.h"

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ABuffFortify : public ABuff
{
	GENERATED_BODY()
public:
	ABuffFortify();
	virtual FString	GetDisplayString() const override;
	//virtual void	ApplyTo(AActor* Target) override;
	//virtual void	Remove() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32	FortifyStacks = 0;
protected:
private:
};
