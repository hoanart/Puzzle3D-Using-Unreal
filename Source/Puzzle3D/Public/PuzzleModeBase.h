// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PuzzleModeBase.generated.h"


/**
 * 
 */
UCLASS()
class PUZZLE3D_API APuzzleModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	APuzzleModeBase();
	
public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class AActor* overlappedActor,class AActor* otherActor);


private:
	UPROPERTY(EditAnywhere,Category=Trigger)
	TObjectPtr<class ATriggerBase> triggerToFinish;
	TObjectPtr<class AMainCharacter> player;
	
};
