// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sprinter.generated.h"
UENUM(BlueprintType)
enum class EState: uint8
{
	IDLE UMETA(DisplayName = "Idle"),
	WALK UMETA(DisplayName = "Walk"),
	SPRINT UMETA(DisplayName = "Sprint"),
	EXHAUSTED UMETA(DisplayName = "Exhausted")
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PUZZLE3D_API USprinter : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USprinter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	// class UInputAction* GetSprintAction() const;
	UFUNCTION(BlueprintCallable,Category = Sprint)
	void Sprint(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable,Category = Sprint)
	void StopSprint(const FInputActionValue& Value);
	class UInputAction* GetSprintAction() const;
public:
	UFUNCTION(BlueprintPure,Category=Sprint)
	bool IsSprintingOnGroundWithinStamina();
public:
	UFUNCTION(BlueprintCallable,Category=Sprint)
	void DepleteStamina();

	UFUNCTION(BlueprintNativeEvent)
	void OnRegenerateStaminaNative();	

	void Regenerate();
	//void Exhausted();
	void RegenerateStamina();
	//void RecoveryWalkSpeed(const mEState& EState);

	float ConvertCurrStaminaToPercent();
private:
	FTimerHandle mDepletionTimer;
	FTimerHandle mExhaustionTimer;
	FTimerHandle mRegenerationTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* sprintAction;
#pragma region Property

	UPROPERTY(VisibleAnywhere, Category=Sprint)
	float mDefaultWalkSpeed;
	UPROPERTY(EditAnywhere, Category=Sprint)
	float mExhaustingSpeed = 300.0f;
	UPROPERTY(EditAnywhere, Category=Sprint)
	float mSprintSpeed =1000.0f;

	UPROPERTY(EditAnywhere)
	float mRotationRate = 10.0f;
	
	UPROPERTY(EditAnywhere, Category=Sprint)
	float mStaminaLevel;
	UPROPERTY(EditAnywhere, Category=Sprint)
	float mMaxStamina;
	UPROPERTY(VisibleInstanceOnly,Category=Sprint)
	float mStaminaPercent;
	
	UPROPERTY(EditAnywhere, Category=Sprint)
	float mStaminaDepletionRate;
	UPROPERTY(EditAnywhere, Category=Sprint)
	float mStaminaDepletionAmount;
	UPROPERTY(EditAnywhere, Category=Sprint)
	bool mbDepleteTimer;

	UPROPERTY(VisibleAnywhere)
	EState mEState;

public:
	const EState& GetCurrentEState() const;

private:
	UPROPERTY(EditAnywhere, Category=Sprint)
	bool mbExhausted;

	UPROPERTY(VisibleInstanceOnly, Category=Sprint)
	bool mbSprintKey;

	UPROPERTY(VisibleAnywhere, Category = Player)
	class AMainCharacter* player;
#pragma endregion 
};


