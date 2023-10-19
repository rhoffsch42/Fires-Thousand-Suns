
#include "MenuContent.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/WidgetSwitcherSlot.h"
#include "Components/SlateWrapperTypes.h"
#include "Internationalization/Text.h"

#include "../FuncLib.h"

#define DBUG_L			3.0f
#define GET_WPOS(x)		(x->GetPaintSpaceGeometry().GetAbsolutePosition())
#define GET_WSIZE(x)	(x->GetPaintSpaceGeometry().GetAbsoluteSize())


void UMenuContentButton::NativeConstruct() {
	this->bHasScriptImplementedTick = false;
	Super::NativeConstruct();
	FScriptDelegate script;
	script.BindUFunction(this, "OnButtonClicked");
	this->Button->OnClicked.Add(script);
}

void UMenuContentButton::OnButtonClicked() {
	this->OnClickedDelegate.Broadcast(this);
}

void UMenuContent::NativeConstruct() {
	Super::NativeConstruct();
}

void	UMenuContent::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void	UMenuContent::SetMenuWidget(UPanelWidget* Widget) {
	if (UFuncLib::CheckObject(Widget, FString("Menu Widget is null"))) {
		this->MenuWidget = Widget;
	}
}

//void	UMenuContent::SetContentWidgetSwitcher(UWidgetSwitcher* Widget) {
//	if (UFuncLib::CheckObject(Widget, FString("WidgetSwitcher is null"))) {
//		this->ContentWidgetSwitcher = Widget;
//	}
//}

void	UMenuContent::AddMenuContent(UUserWidget* Content, FString Title) {
	//UMenuContentButton* NewButton = Create<>();
	//NewButton->ButtonText->SetText(FText("-"));
	//this->AddMenuContentAndButton(Content, NewButton);
}

void	UMenuContent::AddContentAndButton(UUserWidget* Content, UMenuContentButton* Button) {
	//GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("AddContentCustomButton() %p"), this));
	//this->_debugWidgets();
	if (!Button) {
		this->AddMenuContent(Content, FString("-"));
		return;
	}
	this->AddButtonOnly(Button);
	this->AddContentOnly(Content);
	this->LinkButtonToContent(Button, Content);
}

void	UMenuContent::AddButtonOnly(UMenuContentButton* Button) {
	if (Button && this->MenuWidget) {
		if (UFuncLib::CheckObject(Button, FString("Button is null"))) {
			this->MenuWidget->AddChild(Button);
			UVerticalBoxSlot* slot = Cast<UVerticalBoxSlot>(Button->Slot);//tmp UVerticalBox is hardcoded (MenuWidget is UPanelWidget
			if (UFuncLib::CheckObject(slot, FString("Button slot is null"))) {
				slot->SetSize(ESlateSizeRule::Type::Automatic);
				slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Top);
			}
			//GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString("added Button"));
		}
	}
}

void	UMenuContent::AddContentOnly(UUserWidget* Content) {
	if (Content && this->ContentWidgetSwitcher) {
		if (UFuncLib::CheckObject(Content, FString("Content is null"))) {
			UFuncLib::CheckObject(this->ContentWidgetSwitcher->AddChild(Content), "UMenuContent::AddContentOnly() failed to add content to switcher.");
			UWidgetSwitcherSlot* slot = Cast<UWidgetSwitcherSlot>(Content->Slot);
			if (UFuncLib::CheckObject(slot, FString("Content slot is null"))) {
				slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
				//slot->SetPadding
			}
			//GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString("added Content"));
		}
	}
}

void	UMenuContent::LinkButtonToContent(UMenuContentButton* Button, UUserWidget* Content) {
	Button->Content = Content;
	FScriptDelegate delegateScript;
	delegateScript.BindUFunction(this, "SwitchContent");
	Button->OnClickedDelegate.Add(delegateScript);
}

void	UMenuContent::SwitchContent(UMenuContentButton* Button) {
	this->ContentWidgetSwitcher->SetActiveWidget(Button->Content);
}

void	UMenuContent::SetMenuFlex(double Value) {}
void	UMenuContent::SetContentFlex(double Value) {}
int32	UMenuContent::GetAmount() const { return 0; }

///////////////////////////////////////////////////////////////////////////////
/*
void	UMenuContent::_construct() {
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("_construct() %p"), this));

	// construct hierarchy
	UCanvasPanel* Canvas = this->WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), FName("Canvas"));
	this->WidgetTree->RootWidget = Canvas;
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("RootCanvas       %p"), Canvas));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("Tree->RootWidget %p"), this->WidgetTree->RootWidget));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("GetRootWidget    %p"), this->GetRootWidget()));
	UHorizontalBox* Container = this->WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass(), FName("MainHbox"));
	UVerticalBox* MenuBox = this->WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), FName("MenuBox"));
	UWidgetSwitcher* ContentSwitcher = this->WidgetTree->ConstructWidget<UWidgetSwitcher>(UWidgetSwitcher::StaticClass(), FName("Switcher"));
	Canvas->AddChild(Container);
	Container->AddChild(MenuBox);
	Container->AddChild(ContentSwitcher);
	//this->AddToViewport();
	this->SetDesiredSizeInViewport(FVector2D(800, 800));
	Canvas->AccessibleBehavior = ESlateAccessibleBehavior::Auto;

	this->_debugWidgets(Canvas, Container, MenuBox, ContentSwitcher);
}


void	UMenuContent::_initSlotSizes(UVerticalBox* MenuBox, UHorizontalBox* Container) {

	UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(Container->Slot);
	UFuncLib::CheckObject(Cast<UObject>(canvasSlot), FString("Container's herited canvasSlot is null"));
	if (canvasSlot) {
		canvasSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
		canvasSlot->SetOffsets(FMargin(0.0f, 0.0f));
		canvasSlot->SetSize(FVector2D(800, 800));
		GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString("canvasSlot for Container : size set"));
	}

	UHorizontalBoxSlot* HboxSlot = Cast<UHorizontalBoxSlot>(MenuBox->Slot);
	UFuncLib::CheckObject(Cast<UObject>(HboxSlot), FString("MenuBox's herited HboxSlot is null"));
	if (HboxSlot) {
		HboxSlot->SetSize(ESlateSizeRule::Type::Fill);
		HboxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		HboxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString("HboxSlot for MenuBox : size set"));
	}

	//UVerticalBoxSlot* VboxSlot = Cast<UVerticalBoxSlot>(this->MenuBox->Slot);
	//UFuncLib::CheckObject(Cast<UObject>(VboxSlot), FString("VboxSlot is null"));
	//VboxSlot->SetSize(ESlateSizeRule::Type::Fill);
	//VboxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	//VboxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

	this->GetRootWidget()->SynchronizeProperties();

	//this->_debugWidgets();
}

void	UMenuContent::_debugWidgets(UCanvasPanel* Canvas, UHorizontalBox* Container, UVerticalBox* MenuBox, UWidgetSwitcher* ContentSwitcher) const {
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString("_debugWidgets"));
	UFuncLib::CheckObject(this->WidgetTree, FString("WidgetTree is null"));
	if (this->WidgetTree) { UFuncLib::CheckObject(this->WidgetTree->RootWidget, FString("WidgetTree->RootWidget is null")); }
	UFuncLib::CheckObject(Container, FString("Container is null"));
	UFuncLib::CheckObject(MenuBox, FString("MenuBox is null"));
	UFuncLib::CheckObject(ContentSwitcher, FString("ContentSwitcher is null"));

	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString("RootCanvas paint pos       : ").Append(GET_WPOS(Canvas).ToString()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString("RootCanvas paint size      : ").Append(GET_WSIZE(Canvas).ToString()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString("Container paint pos        : ").Append(GET_WPOS(Container).ToString()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString("Container paint size       : ").Append(GET_WSIZE(Container).ToString()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString("MenuBox paint pos          : ").Append(GET_WPOS(MenuBox).ToString()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString("MenuBox paint size         : ").Append(GET_WSIZE(MenuBox).ToString()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString("ContentSwitcher paint pos  : ").Append(GET_WPOS(ContentSwitcher).ToString()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString("ContentSwitcher paint size : ").Append(GET_WSIZE(ContentSwitcher).ToString()));

	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("RootCanvas       %p"), Canvas));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("Tree->RootWidget %p"), this->WidgetTree->RootWidget));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("GetRootWidget    %p"), this->GetRootWidget()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("RootCanvas childs : %d"), Canvas->GetChildrenCount()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("Container childs  : %d"), Container->GetChildrenCount()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("MenuBox   childs  : %d"), MenuBox->GetChildrenCount()));

	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("this in viewport : %d"), this->IsInViewport()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("this IsVisible : %d"), this->IsVisible()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("WidgetTree->RootWidget in viewport : %d"), this->WidgetTree->RootWidget->IsInViewport()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("WidgetTree->RootWidget IsVisible : %d"), this->WidgetTree->RootWidget->IsVisible()));

	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("RootCanvas in viewport : %d"), Canvas->IsInViewport()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("Container in viewport : %d"), Container->IsInViewport()));
	GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("MenuBox in viewport : %d"), MenuBox->IsInViewport()));

	UWidget* w = MenuBox->GetChildAt(0);
	if (w) { GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("MenuBox child[0] in viewport : %d"), w->IsInViewport())); }
	else { GEngine->AddOnScreenDebugMessage(-1, DBUG_L, FColor::Orange, FString::Printf(TEXT("MenuBox child[0] is null"))); }
}

*/
