#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "../FiresThousandSunsPlayerController.h"

#include "DebuffLockedMovement.generated.h"

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ADebuffLockedMovement : public ABuff
{
	GENERATED_BODY()
public:
	ADebuffLockedMovement();
	//virtual FString	GetDisplayString() const override;
	virtual void	ApplyTo(AActor* Target) override;
	virtual void	Remove() override;
private:
	AFiresThousandSunsPlayerController* PlayerController = nullptr;
};
