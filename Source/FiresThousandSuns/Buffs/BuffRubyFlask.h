
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
	//virtual void	ApplyTo(AActor* Target);
	//virtual void	Remove();

	double	BonusFireResistance = 0.5;
	double	LessFireDamage = 0.2;
protected:
private:
};
