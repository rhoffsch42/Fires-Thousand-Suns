// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySlot.h"
#include "../Abilitys/AbilityManager.h"
#include "Components/HorizontalBox.h"

#include "AbilitySlotManager.generated.h"

/**
 * 
 */
UCLASS()
class FIRESTHOUSANDSUNS_API UAbilitySlotManager : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void	SetSlotClass(TSubclassOf<UAbilitySlot> Class);
	UFUNCTION(BlueprintCallable)
	void	LinkAbilityManager(UAbilityManager* InManager);
	UFUNCTION(BlueprintCallable)
	void	AddSlot(UAbilitySlot* NewSlot);
	UFUNCTION(BlueprintCallable)
	UAbilitySlot* CreateNewSlot();

	UFUNCTION(BlueprintCallable)
	void	TEST_ReplaceRoot();
	UFUNCTION(BlueprintCallable)
	void DebugRoot();


	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UHorizontalBox* ContainerHBox;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void Tick(FGeometry MyGeometry, float InDeltaTime);

	TSubclassOf<UAbilitySlot>	_SlotClass;
	TArray<UAbilitySlot*>		_Slots;
	UAbilityManager*			_Manager = nullptr;
};
