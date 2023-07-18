// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StaminaWidget.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PUZZLE3D_API UStaminaWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	class UImage* GetStaminaBar() const;
private:
	void changeStaminaColor(const FLinearColor& color, FLinearColor& target);
private:
	UPROPERTY(meta = (BindWidgetOptional))
	class UImage* mStaminaBar = nullptr;
	class AMainCharacter* mMainCharacter;
	
	FLinearColor mBarColor;
	
};
