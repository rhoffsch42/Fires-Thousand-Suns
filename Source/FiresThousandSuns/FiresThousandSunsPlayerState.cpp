
#include "FiresThousandSunsPlayerState.h"
#include "FiresThousandSunsGameInstance.h"
#include "Systems/HealthManager.h"
#include "Abilitys/LifeFlask.h"

#include "FuncLib.h"

AFiresThousandSunsPlayerState::AFiresThousandSunsPlayerState() {
	this->_InitPreBeginPlay();
}

void	AFiresThousandSunsPlayerState::_InitPreBeginPlay() {
	// Buffs
	this->BuffManager = CreateDefaultSubobject<UBuffManager>(TEXT("BuffManager"));
	// must be built in the constructor, has to be done in a valid world (when the owner has a world)
	
	// HealthManager
	this->HealthManager = NewObject<UHealthManager>(this, GEN_UNAME(this));
	this->HealthManager->SetMaxHP(this->PlayerStatistics.Life);
	this->HealthManager->SetHP(this->PlayerStatistics.Life);

	// Abilitys
	this->_FlameDash = NewObject<UAbilityFlameDash>(this, GEN_UNAME(this));
	this->_MoltenShell = NewObject<UAbilityMoltenShell>(this, GEN_UNAME(this));
	this->_VaalMoltenShell = NewObject<UAbilityVaalMoltenShell>(this, GEN_UNAME(this));
	this->_Steelskin = NewObject<UAbilitySteelskin>(this, GEN_UNAME(this));


	this->AbilityManager = NewObject<UAbilityManager>(this, GEN_UNAME(this));
	this->AbilityManager->SetAbilityAmount(5);
	this->AbilityManager->SetAbility(0, nullptr); // used as a 'slot clearer'
	this->AbilityManager->SetAbility(1, this->_FlameDash);
	this->AbilityManager->SetAbility(2, this->_Steelskin);
	this->AbilityManager->SetAbility(3, this->_MoltenShell);
	this->AbilityManager->SetAbility(4, this->_VaalMoltenShell);
	//this->AbilityManager->SetAbility(5, VaalArcticArmor);
	// shieldCharge // /Script/Engine.Material'/Game/LevelPrototyping/Materials/shield-bash_100x100_UIMat.shield-bash_100x100_UIMat'

	// Flask
	ULifeFlask* LifeFlask = NewObject<ULifeFlask>(this, GEN_UNAME(this));
	URubyFlask* RubyFlask = NewObject<URubyFlask>(this, GEN_UNAME(this));

	this->FlaskManager = NewObject<UAbilityManager>(this, GEN_UNAME(this));
	this->FlaskManager->SetAbilityAmount(5);
	this->FlaskManager->SetAbility(0, nullptr); // used as a 'slot clearer'
	this->FlaskManager->SetAbility(1, LifeFlask);
	this->FlaskManager->SetAbility(2, RubyFlask);
	this->FlaskManager->SetAbility(3, nullptr);
	this->FlaskManager->SetAbility(4, nullptr);
}

void	AFiresThousandSunsPlayerState::_InitPostBeginPlay() {
	// Buffs
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

	UFuncLib::CheckObject(this->_FlameDash->CastTime->World, "AFires..PlayerState:: Missing CastTime->World on _FlameDash");
	UFuncLib::CheckObject(this->_Steelskin->CastTime->World, "AFires..PlayerState:: Missing CastTime->World on _Steelskin");
	UFuncLib::CheckObject(this->_MoltenShell->CastTime->World, "AFires..PlayerState:: Missing CastTime->World on _MoltenShell");
	UFuncLib::CheckObject(this->_VaalMoltenShell->CastTime->World, "AFires..PlayerState:: Missing CastTime->World on _VaalMoltenShell");
}
