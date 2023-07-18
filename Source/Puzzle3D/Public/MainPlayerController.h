// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLE3D_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainHUDWidget> mHUDclass;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMainHUDWidget> mHUD;
	
};
