// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "IceMakerComponent.generated.h"
DECLARE_DELEGATE(FOnEnableBuidlingDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLE3D_API UIceMakerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIceMakerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	const TObjectPtr<class UInputAction>& GetActivateIceAction() const;
	const TObjectPtr<class UInputAction>& GetCreateIceAction() const;
	void Operate();
	void Spawn();
	FOnEnableBuidlingDelegate OnEnableIce;
	void HandleEnableIceEvent();
private:
	void activateIceCube();
	void deActivateIceCube();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> mActivateIceAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> mCreateIceAction;
	bool mbActive;
	UPROPERTY(EditAnywhere, Category = IceCube)
	TSubclassOf<class AIceCube> mIceCubeClass;

	TObjectPtr<class AIceCube> mIceCube;
};
