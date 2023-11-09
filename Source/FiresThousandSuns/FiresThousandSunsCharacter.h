// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FiresThousandSunsPlayerState.h"
#include "Buffs/BuffFortify.h"

#include "FiresThousandSunsCharacter.generated.h"

#define BP_PATH_BUFFFORTIFY	"/Game/TopDown/Blueprints/Actors/A_BuffFortify"

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDied);

UCLASS(Blueprintable)
class AFiresThousandSunsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFiresThousandSunsCharacter();
	UFUNCTION(BlueprintCallable)
	void	SetAllBuffActorClasses(TSubclassOf<ABuffFortify> Fortify,
									TSubclassOf<ABuffMoltenShell> MoltenShell,
									TSubclassOf<ABuffVaalMoltenShell> VaalMoltenShell,
									TSubclassOf<ABuffSteelskin> Steelskin);

	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintCallable)
	void	Debug_PlayerState();
	UFUNCTION(BlueprintCallable)
	void	UpdateStatistics(const FPlayerStatistics& NewStats);
	UFUNCTION(BlueprintCallable)
	void	ApplyLifeRegen(float DeltaSeconds);
	UFUNCTION(BlueprintCallable)
	void	Die();
	UFUNCTION(BlueprintCallable)
	void	SpawnFortifyBuff();

	// Custom PlayerState
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AFiresThousandSunsPlayerState* CustomPlayerState = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ABuffFortify>	BuffFortifyClass;

	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FPlayerDied	PlayerDied;

protected:
	virtual void BeginPlay() override;
	void	_InitPostBeginPlay();
	void	_InitPreBeginPlay();
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

