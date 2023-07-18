// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle3D/Public/PuzzleModeBase.h"

#include "MainCharacter.h"
#include "Engine/TriggerBase.h"
#include "Kismet/GameplayStatics.h"

APuzzleModeBase::APuzzleModeBase()
{
	
}

void APuzzleModeBase::BeginPlay()
{
	Super::BeginPlay();
		player = CastChecked<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	TArray<AActor*> TriggerBases;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATriggerBase::StaticClass(),TriggerBases);
	if(!TriggerBases.Empty())
	{
		triggerToFinish = CastChecked<ATriggerBase>(TriggerBases[0]);	
	}
	
		if(IsValid(triggerToFinish))
		{
			triggerToFinish->OnActorBeginOverlap.AddDynamic(this,&APuzzleModeBase::OnOverlapBegin);
		}
	
}

void APuzzleModeBase::OnOverlapBegin(AActor* overlappedActor, AActor* otherActor)
{
	if(player ==CastChecked<AMainCharacter>(otherActor))
	{
		UE_LOG(LogTemp,Warning,TEXT("Finished"));
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,TEXT("FINISHED"));
		}
	}
}

