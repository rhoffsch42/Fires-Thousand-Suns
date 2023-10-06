
#include "AbilitySlotManager.h"
#include "../FuncLib.h"
#include "Components/HorizontalBoxSlot.h"

void	UAbilitySlotManager::NativeConstruct() {
	Super::NativeConstruct();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("UAbilitySlotManager::NativeConstruct()"));
}

void	UAbilitySlotManager::NativeOnInitialized() {
	Super::NativeOnInitialized();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("UAbilitySlotManager::NativeOnInitialized()"));
}

void	UAbilitySlotManager::SetSlotClass(TSubclassOf<UAbilitySlot> Class) {
	this->_SlotClass = Class;
}

void	UAbilitySlotManager::Tick(FGeometry MyGeometry, float InDeltaTime) {
	Super::Tick(MyGeometry, InDeltaTime);
}

void	UAbilitySlotManager::LinkAbilityManager(UAbilityManager* InManager) {
	this->_Manager = InManager;
	int32 amount = this->_Manager->GetAbilityAmount();
	this->_Slots.Empty();
	this->ContainerHBox->ClearChildren();
	this->_Slots.SetNum(amount);
	
	for(int32 index = 0; index < amount; index++) {
		if (!this->_Slots[index]) {
			this->_Slots[index] = this->CreateNewSlot();
			this->AddSlot(this->_Slots[index]);
		}
		this->_Slots[index]->LinkAbility(this->_Manager->GetAbility(index));
	}
}

UAbilitySlot* UAbilitySlotManager::CreateNewSlot() {
	if (!UFuncLib::CheckObject(this->_SlotClass.Get(), "UAbilitySlotManager::CreateNewSlot() _SlotClass is not set.")) {
		return nullptr;
	}
	UAbilitySlot* slot = CreateWidget<UAbilitySlot>(this, this->_SlotClass);
	UFuncLib::CheckObject(slot, "Slot creation failed");
	return slot;
}

void	UAbilitySlotManager::AddSlot(UAbilitySlot* NewSlot) {
	if (!UFuncLib::CheckObject(NewSlot, "UAbilitySlotManager::AddSlot() arg is null")) {
		return;
	}
	//UPanelSlot* slot = this->ContainerHBox->AddChild(NewSlot);
	UHorizontalBoxSlot* slot = Cast<UHorizontalBoxSlot>(this->ContainerHBox->AddChild(NewSlot));
	slot->SetSize(ESlateSizeRule::Type::Automatic);
	NewSlot->SetDesiredSizeInViewport(FVector2D(100.0f, 100.0f));
	slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
	slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Top);
}


#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Engine/Texture2D.h"
#include "Blueprint/WidgetTree.h"
#include "GroundTruthData.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Styling/SlateBrush.h"
#ifdef CreateWidget_POSSIBLE_OVERLOADS
static void f() {
	UUserWidget* UUserWidget::CreateWidgetInstance(	UWorld&,				TSubclassOf<UUserWidget>, FName);
	UUserWidget *UUserWidget::CreateWidgetInstance(	UGameInstance &,		TSubclassOf<UUserWidget>, FName);
	UUserWidget *UUserWidget::CreateWidgetInstance(	APlayerController &,	TSubclassOf<UUserWidget>, FName);
	UUserWidget *UUserWidget::CreateWidgetInstance(	UWidgetTree &,			TSubclassOf<UUserWidget>, FName);
	UUserWidget *UUserWidget::CreateWidgetInstance(	UWidget &,				TSubclassOf<UUserWidget>, FName);
}
#endif
/*
	/Game = /Content
	Object soft path:	/Game/LevelPrototyping/Textures/Default.Default
	Object path:		/Game/LevelPrototyping/Textures/Default.Default
	Object system path:	C:/_dev/Content/LevelPrototyping/Textures/Default.uasset
*/
void	UAbilitySlotManager::TEST_ReplaceRoot() {
	const FString tempIconPath = "/Game/LevelPrototyping/Textures/FireShield_01_50x50.FireShield_01_50x50";
	UTexture2D* tempTexture = LoadObject<UTexture2D>(this->GetWorld(), *tempIconPath);
	if (!UFuncLib::CheckObject(tempTexture, "LoadObject<UTexture2D> failed")) {
		return;
	}
	UCanvasPanel* MyCanvas = this->WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	if (!UFuncLib::CheckObject(MyCanvas, "WidgetTree->ConstructWidget<UCanvasPanel> failed")) {
		return;
	}
	this->WidgetTree->RootWidget = MyCanvas;
	Super::RebuildWidget();
	auto tmpImage = WidgetTree->ConstructWidget<UImage>();
	if (!UFuncLib::CheckObject(MyCanvas, "WidgetTree->ConstructWidget<UImage> failed")) {
		return;
	}
	tmpImage->SetBrush(UWidgetBlueprintLibrary::MakeBrushFromTexture(tempTexture));
	//tmpImage->SetBrushSize(FVector2D(16.0f,16.0f));
	UFuncLib::CheckObject(MyCanvas->AddChild(tmpImage), "MyCanvas->AddChild(tmpImage) no slot");
	const auto tempSlot = Cast<UCanvasPanelSlot>(tmpImage->Slot);
	UFuncLib::CheckObject(tempSlot, "Cast<UCanvasPanelSlot>(tmpImage->Slot) failed");
	if (tempSlot)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("SetAnchors"));
		//tempSlot->SetSize(FVector2D(0.0f, 1.0f));
		tempSlot->SetOffsets(FMargin(0, 0));
		tempSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
	}

	return;
}

void UAbilitySlotManager::DebugRoot() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("GetRootWidget() : %p"), this->GetRootWidget()));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("WidgetTree      : %p"), this->WidgetTree));
	TArray<UWidget*>	arr;
	this->WidgetTree->GetChildWidgets(this, arr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("this->GetChildWidgets() Num() : %d"), arr.Num()));
}