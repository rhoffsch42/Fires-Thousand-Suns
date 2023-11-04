
#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "BuffRubyFlask.generated.h"


UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API ABuffRubyFlask : public ABuff
{
	GENERATED_BODY()
public:
	ABuffRubyFlask();
	//virtual FString	GetDisplayString() const override;
	//virtual void	ApplyTo(AActor* Target) override;
	//virtual void	Remove() override;

	double	BonusFireResistance = 0.5;
	double	LessFireDamage = 0.2;
protected:
private:
};
