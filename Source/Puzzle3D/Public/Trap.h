// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Trap.generated.h"

UCLASS()
class PUZZLE3D_API ATrap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	UFUNCTION()
	void OnHit(class UPrimitiveComponent* hitComponent, AActor* otherActor,class UPrimitiveComponent* otherComp, FVector NormalImpulse, const FHitResult& hit);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* overlappedComp, AActor* otherActor,class UPrimitiveComponent* otherComp, int32 otherBoxIndex, bool bFromSweep, const FHitResult& hit);
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Condition)
	TObjectPtr<class AActor> trigger;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class AActor> objForRestart;
private:
	UPROPERTY(VisibleInstanceOnly)
	FVector startLoc;
private:
	TObjectPtr<class USceneComponent> root;
	UPROPERTY(EditAnywhere,Category = Components)
	TObjectPtr<class UStaticMeshComponent> trap;
	
};
