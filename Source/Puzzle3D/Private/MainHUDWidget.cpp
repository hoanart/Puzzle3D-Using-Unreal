// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDWidget.h"

#include "HeartWidget.h"
#include "StaminaWidget.h"
#include "Components/WrapBox.h"

void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	mStaminaImg = Cast<UStaminaWidget>(GetWidgetFromName("Stamina"));
	if(!mStaminaImg)
	{
		UE_LOG(LogTemp,Warning,TEXT("Need staminaImg"));
		return;
	}
	mHeartWrapBox = Cast<UWrapBox>(GetWidgetFromName("HeartWrapBox"));
	if(!IsValid(mHeartWrapBox))
	{
		UE_LOG(LogTemp,Warning,TEXT("Need WrapBox"));
		return;
	}
	
	for(int i=0;i<3;i++)
	{
		TObjectPtr<UHeartWidget> heartWidget = Cast<UHeartWidget>(CreateWidget(this,mHeartClass));
		if(!IsValid(heartWidget))
		{
			UE_LOG(LogTemp,Warning,TEXT("Need HeartWidget"));
			return;
		}
		mHearts.Add(heartWidget);
		mHeartWrapBox->AddChildToWrapBox(heartWidget);
	}
}

void UMainHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
