// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Abilitys/Ability.h"

#include "FiresThousandSunsPlayerController.generated.h"


UCLASS()
class AFiresThousandSunsPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AFiresThousandSunsPlayerController();
	UFUNCTION(BlueprintCallable)
	bool	SetCastedAbility(UAbility* Ability, const FEffectParameters& InParameters);
	UFUNCTION(BlueprintCallable)
	void	FinalizeCastedAbility();
	UFUNCTION(BlueprintCallable)
	void	IncrementBlockInputCounter();
	UFUNCTION(BlueprintCallable)
	void	DecrementBlockInputCounter();

	UFUNCTION(BlueprintCallable)
	bool	GetIsCasting() const;

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationTouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel>	ClickCollisionChannel = ECollisionChannel::ECC_Visibility;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

private:
	FVector	CachedDestination;
	bool	bIsTouch; // Is it a touch device
	float	FollowTime; // For how long it has been pressed
	int32	_BlockInputCounter = 0;

	UAbility* _CastedAbility;
	FEffectParameters _Parameters;
	bool	_bIsCasting = false;
	double	_MinimumDistanceToMove = 100.0;// this is the distance between the center of mass of the character and the point on the floor, they dont have the same Z
};
