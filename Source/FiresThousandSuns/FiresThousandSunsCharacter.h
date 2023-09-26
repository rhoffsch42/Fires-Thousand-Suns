// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Systems/HealthManager.h"
#include "Abilitys/AbilityFlameDash.h"
#include "Abilitys/AbilityMoltenShell.h"
#include "Buffs/BuffManager.h"

#include "FiresThousandSunsCharacter.generated.h"

#define DEFAULT_PLAYER_HP	6000.0


UCLASS(Blueprintable)
class AFiresThousandSunsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFiresThousandSunsCharacter();

	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintCallable)
	void	Die();

	// HealtManager
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHealthManager* HealthManager = nullptr;

	// Skills
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAbilityFlameDash*		FlameDash = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAbilityMoltenShell*	MoltenShell = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAbilityMoltenShell*	VaalMoltenShell = nullptr;

	// Buffs component
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBuffManager*	BuffManager = nullptr;
protected:
	virtual void BeginPlay() override;
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

};

