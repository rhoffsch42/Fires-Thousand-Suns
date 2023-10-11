
#include "AbilitySlotManager.h"
#include "../FuncLib.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/PanelSlot.h"

void	UAbilitySlotManager::NativeConstruct() {
	Super::NativeConstruct();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("UAbilitySlotManager::NativeConstruct()"));
}

void	UAbilitySlotManager::NativeOnInitialized() {
	Super::NativeOnInitialized();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("UAbilitySlotManager::NativeOnInitialized()"));
}

void	UAbilitySlotManager::Tick(FGeometry MyGeometry, float InDeltaTime) {
	Super::Tick(MyGeometry, InDeltaTime);
}

void	UAbilitySlotManager::SetSlotClass(TSubclassOf<UAbilitySlot> Class) {
	this->_SlotClass = Class;
}

void	UAbilitySlotManager::LinkAbilityManager(UAbilityManager* InManager) {
	this->_Manager = InManager;
	int32 amount = this->_Manager->GetAbilityAmount();
	this->_Slots.Empty();
	this->ClearContainer();
	this->_Slots.SetNum(amount);
	
	for (int32 index = 0; index < amount; index++) {
		if (!this->_Slots[index]) {
			this->_Slots[index] = this->CreateNewSlot();
			this->AddSlot(this->_Slots[index]);
		}
		if (this->_Slots[index]) {
			this->_Slots[index]->LinkAbility(this->_Manager->GetAbility(index));
		}
	}
}

void	UAbilitySlotManager::ClearContainer() const {
	if (!this->ContainerPanel) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("IAbilitySlotManager::ClearContainer() ContainerPanel is nullptr"));
	} else {
		this->ContainerPanel->ClearChildren();
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

UPanelSlot*	UAbilitySlotManager::AddSlot(UAbilitySlot* NewSlot) {
	if (!UFuncLib::CheckObject(NewSlot, "UAbilitySlotManagerHBox::AddSlot() arg is null")) {
		return nullptr;
	}
	NewSlot->SetDesiredSizeInViewport(FVector2D(100.0f, 100.0f));
	return this->ContainerPanel->AddChild(NewSlot);
}

void	UAbilitySlotManager::SetLayout(const TArray<EAbilityType> Layout) {
	int32 count = std::min(Layout.Num(), this->ContainerPanel->GetChildrenCount());

	for (int32 i = 0; i < count; i++) {
		UWidget* w = this->ContainerPanel->GetChildAt(i);
		if (UFuncLib::CheckObject(w, "UAbilitySlotManager::SetLayout() failed to get child")) {
			UAbilitySlot* slot = Cast<UAbilitySlot>(w);
			if (UFuncLib::CheckObject(slot, "UAbilitySlotManager::SetLayout() failed to cast<UAbilitySlot> widget ")) {
				slot->LinkAbility(this->_Manager->GetAbilityByType(Layout[i]));
			}
		}
	}
}

TArray<EAbilityType>	UAbilitySlotManager::GetLayoutAsAbilityType() const {
	TArray<EAbilityType> Layout;
	int32 count = this->ContainerPanel->GetChildrenCount();
	Layout.SetNum(count);

	for (int32 i = 0; i < count; i++) {
		Layout[i] = EAbilityType::None;
		UWidget* w = this->ContainerPanel->GetChildAt(i);
		if (UFuncLib::CheckObject(w, "UAbilitySlotManager::GetLayoutAsAbilityType() failed to get child")) {
			UAbilitySlot* slot = Cast<UAbilitySlot>(w);
			if (UFuncLib::CheckObject(slot, "UAbilitySlotManager::GetLayoutAsAbilityType() failed to cast<UAbilitySlot> widget ")) {
				UAbility* Ability = slot->GetLinkedAbility();
				if (Ability) {
					Layout[i] = Ability->AbilityType;
				}
			}
		}
	}

	return Layout;
}

UAbilityManager* UAbilitySlotManager::GetLinkedAbilityManager() const { return this->_Manager; }

//////////////////////////////////////////////////////////////////////////////////
//////////////////////   UAbilitySlotManagerHBox   ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void	UAbilitySlotManagerHBox::NativeConstruct() {
	Super::NativeConstruct();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("UAbilitySlotManagerHBox::NativeConstruct()"));
	//this->ContainerPanel = this->ContainerHBox;
}

void	UAbilitySlotManagerHBox::NativeOnInitialized() {
	Super::NativeOnInitialized();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("UAbilitySlotManagerHBox::NativeOnInitialized()"));
}

void	UAbilitySlotManagerHBox::Tick(FGeometry MyGeometry, float InDeltaTime) {
	Super::Tick(MyGeometry, InDeltaTime);
}

UPanelSlot* UAbilitySlotManagerHBox::AddSlot(UAbilitySlot* NewSlot) {
	UHorizontalBoxSlot* slot = Cast<UHorizontalBoxSlot>(Super::AddSlot(NewSlot));
	if (UFuncLib::CheckObject(slot, "UHorizontalBoxSlot::AddSlot() Containeris not a UHorizontalBox")) {
		slot->SetSize(ESlateSizeRule::Type::Automatic);
		slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
		slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Top);
	}
	return slot;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////   TESTS IAbilitySlotManager ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#ifdef TESTS_IABILITYMANAGER
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
void	IAbilitySlotManager::TEST_ReplaceRoot() {
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

void IAbilitySlotManager::DebugRoot() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("GetRootWidget() : %p"), this->GetRootWidget()));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("WidgetTree      : %p"), this->WidgetTree));
	TArray<UWidget*>	arr;
	this->WidgetTree->GetChildWidgets(this, arr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("this->GetChildWidgets() Num() : %d"), arr.Num()));
}
#endif