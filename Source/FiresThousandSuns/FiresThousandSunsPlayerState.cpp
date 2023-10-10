
#include "FiresThousandSunsPlayerState.h"
#include "FiresThousandSunsGameInstance.h"
#include "Systems/HealthManager.h"
#include "FuncLib.h"

AFiresThousandSunsPlayerState::AFiresThousandSunsPlayerState() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "AFiresThousandSunsPlayerState()");
	this->_InitPreBeginPlay();
}

void	AFiresThousandSunsPlayerState::_InitPreBeginPlay() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "AFiresThousandSunsPlayerState::_Init()");
	
	// Buffs
	this->BuffManager = CreateDefaultSubobject<UBuffManager>(TEXT("BuffManager"));
	// must be built in the constructor, has to be done in a valid world (when the owner has a world)
	
	// HealthManager
	this->HealthManager = NewObject<UHealthManager>();
	this->HealthManager->SetMaxHP(this->PlayerStats.Life);
	this->HealthManager->SetHP(this->PlayerStats.Life);

	// Abilitys
	this->_FlameDash = NewObject<UAbilityFlameDash>();
	this->_FlameDash->Cooldown->World = this->GetWorld();

	this->_MoltenShell = NewObject<UAbilityMoltenShell>();
	this->_MoltenShell->Cooldown->World = this->GetWorld();

	this->_VaalMoltenShell = NewObject<UAbilityMoltenShell>();
	this->_VaalMoltenShell->ShellHP = 10000.0;
	this->_VaalMoltenShell->ShellDuration = 10.8;
	this->_VaalMoltenShell->ShellAbsorbtion = 0.39;
	this->_VaalMoltenShell->Cooldown->World = this->GetWorld();
	this->_VaalMoltenShell->Cooldown->SetDuration(50.0);
	this->_VaalMoltenShell->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/FireShield_red_01_50x50_UIMat.FireShield_red_01_50x50_UIMat'"));

	this->_Steelskin = NewObject<UAbilityMoltenShell>();
	this->_Steelskin->ShellHP = 2209;
	this->_Steelskin->ShellDuration = 1.5;
	this->_Steelskin->ShellAbsorbtion = 0.70;
	this->_Steelskin->Cooldown->World = this->GetWorld();
	this->_Steelskin->Cooldown->SetDuration(4.05);
	this->_Steelskin->SetNewMaterial(this->GetWorld(), FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/aura_100x100_UIMat.aura_100x100_UIMat'"));

	this->AbilityManager = NewObject<UAbilityManager>();
	this->AbilityManager->SetAbilityAmount(5);
	this->AbilityManager->SetAbility(0, nullptr); // shieldCharge // /Script/Engine.Material'/Game/LevelPrototyping/Materials/shield-bash_100x100_UIMat.shield-bash_100x100_UIMat'
	this->AbilityManager->SetAbility(1, this->_FlameDash);
	this->AbilityManager->SetAbility(2, this->_Steelskin);
	this->AbilityManager->SetAbility(3, this->_MoltenShell);
	this->AbilityManager->SetAbility(4, this->_VaalMoltenShell);
	//this->AbilityManager->SetAbility(5, VaalArcticArmor);
}

void	AFiresThousandSunsPlayerState::_InitPostBeginPlay() {
	// Abilitys
	//UGameInstance* GI = this->GetGameInstance();
	//if (UFuncLib::CheckObject(GI, "AFiresThousandSunsPlayerState::_Init() Couldn't get the GI")) {
	//	UFiresThousandSunsGameInstance* FiresGI = Cast<UFiresThousandSunsGameInstance>(GI);
	//	if (UFuncLib::CheckObject(FiresGI, "AFiresThousandSunsPlayerState::_Init() Couldn't cast as FiresGI")) {
	//		this->AbilityManager = FiresGI->AbilityManager;
	//	}
	//	else {
	//	}
	//}


	// Buffs
	//this->BuffManager = CreateDefaultSubobject<UBuffManager>(TEXT("BuffManager"));//has to be done in a valid world (so when the actor has a world)
	this->AddOwnedComponent(this->BuffManager);
	//this->BuffManager->RegisterComponent();
}

 void AFiresThousandSunsPlayerState::BeginPlay() {
	 Super::BeginPlay();

	 this->_InitPostBeginPlay();

	 // Check Cooldowns Worlds
	UFuncLib::CheckObject(this->_FlameDash->Cooldown->World, "AFires..PlayerState:: Missing Cooldown->World on _FlameDash");
	UFuncLib::CheckObject(this->_Steelskin->Cooldown->World, "AFires..PlayerState:: Missing Cooldown->World on _Steelskin");
	UFuncLib::CheckObject(this->_MoltenShell->Cooldown->World, "AFires..PlayerState:: Missing Cooldown->World on _MoltenShell");
	UFuncLib::CheckObject(this->_VaalMoltenShell->Cooldown->World, "AFires..PlayerState:: Missing Cooldown->World on _VaalMoltenShell");

}
