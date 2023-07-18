// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "IceCube.generated.h"

UCLASS()
class PUZZLE3D_API AIceCube : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIceCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	bool CheckForOverlap();
	void EnableBuilding();
	void DisableBuilding();

	void SpawnIceCube(const FTransform& transform);
	void onSpawned();
public:
	TObjectPtr<class UBoxComponent> GetBox() const;
private:
	UPROPERTY(VisibleAnywhere)
	bool mCanPlace;
	bool mbOnce;
	
	FTimeline mCollisionTimeline;
	UFUNCTION()
	void expandCollisionTimeLine(float value);
public:
	void SetCanPlace(const bool& canPlace);

	bool CanPlace() const;

	void ExpandCol();
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Compontnets,meta =(AllowPrivateAccess="true"))
	TObjectPtr<USkeletalMeshComponent> mIceCube;
	UPROPERTY(EditAnywhere,Category=Components)
	TObjectPtr<class UBoxComponent> mBox;
	
	UPROPERTY(EditAnywhere,Category=Components)
	TObjectPtr<class UBoxComponent> mCollision;
	UPROPERTY(EditAnywhere,Category=Components)
	TObjectPtr<class UTimelineComponent> timeLineComp;
	UPROPERTY(EditAnywhere,Category=Curve)
	TObjectPtr<class UCurveFloat> mCollisionExpansionCurve;
	
	UPROPERTY(EditAnywhere,Category= Anim)
	TObjectPtr<class UAnimationAsset> mIceCubeAnim;
	UPROPERTY(EditAnywhere,Category=Materials)
	TObjectPtr<class UMaterialInterface> mEnableMat;
	UPROPERTY(EditAnywhere,Category=Materials)
	TObjectPtr<class UMaterialInterface> mDisableMat;
};


