// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLE3D_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
private:
	UPROPERTY(meta =(BindWidgetOptional))
	class UStaminaWidget* mStaminaImg;
	UPROPERTY(meta =(BindWidgetOptional))
	TObjectPtr<class UWrapBox> mHeartWrapBox;
	UPROPERTY(EditAnywhere,Category = Widget)
	TSubclassOf<class UHeartWidget> mHeartClass;
	UPROPERTY(VisibleAnywhere,Category = Widget)
	TArray<TObjectPtr<class UHeartWidget>> mHearts;
};
