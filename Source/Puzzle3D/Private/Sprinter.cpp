#include "Puzzle3D/Public/Sprinter.h"

#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

USprinter::USprinter()
	: mStaminaLevel(10.0f)
	, mMaxStamina(100.0f)
	, mStaminaDepletionRate(0.1f)
	, mStaminaDepletionAmount(1.0f)
	, mEState(EState::WALK)
{
	//PrimaryComponentTick.bCanEverTick = true;
}

void USprinter::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AMainCharacter>(GetOwner());
	if(!player)
	{
		return;
	}
	mDefaultWalkSpeed = player->GetCharacterMovement()->MaxWalkSpeed;
}

void USprinter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UInputAction* USprinter::GetSprintAction() const
{
	return sprintAction;
}

void USprinter::Sprint(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp,Warning,TEXT("SPRINT"));
	if(!player)
	{
		UE_LOG(LogTemp,Display,TEXT("Need Player"));
		return;
	}
	//mbDepleteTimer = Value.Get<bool>();
	if(IsSprintingOnGroundWithinStamina())
	{
		if(!mbDepleteTimer&&mEState==EState::WALK)
		{
			mEState = EState::SPRINT;
			mbDepleteTimer = true;
		}
	}
	
	if(mEState == EState::SPRINT)
	{
		player->GetCharacterMovement()->MaxWalkSpeed = mSprintSpeed;
		//UE_LOG(LogTemp,Display,TEXT("%f"),player->GetCharacterMovement()->MaxWalkSpeed);
		GetOwner()->GetWorldTimerManager().ClearTimer(mRegenerationTimer);
		if(mbDepleteTimer)
		{
			if(player->GetWorldTimerManager().IsTimerPaused(mDepletionTimer))
			{
				player->GetWorldTimerManager().UnPauseTimer(mDepletionTimer);
			}
			else
			{
			player->GetWorldTimerManager().SetTimer(mDepletionTimer,this,&USprinter::DepleteStamina,mStaminaDepletionRate,true);
				
			}
			mbDepleteTimer =false;
		}
		
	}
		
}

void USprinter::StopSprint(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Display,TEXT("stop"));
	mEState = mEState == EState::EXHAUSTED ? EState::EXHAUSTED : EState::WALK;
	mbDepleteTimer = false;
	Regenerate();
}

bool USprinter::IsSprintingOnGroundWithinStamina()
{
	return player->GetCharacterMovement()->IsMovingOnGround()
		&& player->GetVelocity().SquaredLength()>0&&mStaminaLevel>0 ;
}

void USprinter::DepleteStamina()
{
	UE_LOG(LogTemp,Warning,TEXT("Deplete"));
	if(mStaminaLevel<=0)
	{
		player->GetCharacterMovement()->MaxWalkSpeed = mExhaustingSpeed;
		mEState = EState::EXHAUSTED;
		Regenerate();
	}
	else
	{
		if(IsSprintingOnGroundWithinStamina())
		{
			mStaminaLevel = FMath::Clamp(mStaminaLevel-mStaminaDepletionAmount,0,mMaxStamina);
			UE_LOG(LogTemp,Display,TEXT("현재 레벨 %f"),mStaminaLevel);	
		}
		
	}
}

void USprinter::OnRegenerateStaminaNative_Implementation()
{
}

void USprinter::Regenerate()
{
	player->GetWorldTimerManager().ClearTimer(mDepletionTimer);
	player->GetWorldTimerManager().SetTimer(mRegenerationTimer,this,&USprinter::RegenerateStamina,mStaminaDepletionRate,true);
}

void USprinter::RegenerateStamina()
{
	if(mStaminaLevel<mMaxStamina)
	{
		mStaminaLevel = FMath::Clamp(mStaminaLevel+mStaminaDepletionAmount,0,mMaxStamina);
	}
	else
	{
		player->GetWorldTimerManager().ClearTimer(mRegenerationTimer);
		player->GetCharacterMovement()->MaxWalkSpeed = mDefaultWalkSpeed;
		if(mEState == EState::EXHAUSTED)
		{
			mEState = EState::WALK;
		}
	}
}

float USprinter::ConvertCurrStaminaToPercent()
{
	mStaminaPercent = mStaminaLevel/mMaxStamina;
	return mStaminaPercent;
}


const EState& USprinter::GetCurrentEState() const
{
	return mEState;
}

