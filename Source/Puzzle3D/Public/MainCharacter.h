// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle3D/Puzzle3DCharacter.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLE3D_API AMainCharacter : public APuzzle3DCharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	TObjectPtr<class USprinter> GetSprinterComp();
	//TObjectPtr<class UIceMakerComponent> GetIceMakerComp();
	
private:
	UPROPERTY(VisibleAnywhere,Category = Components)
	TObjectPtr<class USprinter> mSprinterComp;
	UPROPERTY(VisibleAnywhere,Category = Components)
	TObjectPtr<class UIceMakerComponent> mIceMakerComp;
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	// class UInputAction* sprintAction;
	
};


