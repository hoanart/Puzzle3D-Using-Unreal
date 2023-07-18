// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle3D/Public/MainCharacter.h"

#include "EnhancedInputComponent.h"
#include "Sprinter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "IceMakerComponent.h"
#include "Camera/CameraComponent.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	mSprinterComp = CreateDefaultSubobject<USprinter>(TEXT("SprintComponent"));
	if(!IsValid(mSprinterComp))
	{
		UE_LOG(LogTemp,Warning,TEXT("Need SprinterComp"));
		return;
	}
	mIceMakerComp = CreateDefaultSubobject<UIceMakerComponent>(TEXT("IceMakerComponent"));
	mIceMakerComp->SetupAttachment(GetFollowCamera(),GetFollowCamera()->GetFName());
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(mSprinterComp->GetSprintAction(),ETriggerEvent::Triggered,mSprinterComp.Get(),&USprinter::Sprint);
		EnhancedInputComponent->BindAction(mSprinterComp->GetSprintAction(),ETriggerEvent::Completed,mSprinterComp.Get(),&USprinter::StopSprint);

		check(mIceMakerComp != nullptr)
		EnhancedInputComponent->BindAction(mIceMakerComp->GetActivateIceAction(),ETriggerEvent::Triggered,mIceMakerComp.Get(),&UIceMakerComponent::Operate);
		EnhancedInputComponent->BindAction(mIceMakerComp->GetCreateIceAction(),ETriggerEvent::Triggered,mIceMakerComp.Get(),&UIceMakerComponent::Spawn);	
	}
}
TObjectPtr<USprinter> AMainCharacter::GetSprinterComp() 
{
	if(IsValid(mSprinterComp))
	{
		return mSprinterComp;
	}
	return nullptr;
}
