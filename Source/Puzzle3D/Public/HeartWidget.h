// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeartWidget.generated.h"
UENUM(BlueprintType)
enum class EHeartState : uint8
{
	EMPTY UMETA(DisplayName ="Empty"),
	PART UMETA(DisplayName ="Part"),
	FULL UMETA(DisplayName = "Full")
};
/**
 * 
 */
UCLASS()
class PUZZLE3D_API UHeartWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UHeartWidget(const FObjectInitializer& ObjectInitializer);
	void ModifyPercent(float percent);
public:
	const EHeartState& GetState() const;
	const float& GetPercent() const;
	void SetPercent(const float& percent);
private:
	EHeartState mEHeartState;
	float mPercent;
private:
	UPROPERTY(meta =(BindWidget))
	TObjectPtr<class UImage> heartImg;
	UPROPERTY(meta =(BindWidget))
	TObjectPtr<class USizeBox> sizeBox;
};
