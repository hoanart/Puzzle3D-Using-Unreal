// Fill out your copyright notice in the Description page of Project Settings.


#include "HeartWidget.h"

#include "Components/Image.h"

void UHeartWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHeartWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

UHeartWidget::UHeartWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, mPercent(1.0f)
{
}

void UHeartWidget::ModifyPercent(float percent)
{
	mPercent = FMath::Clamp(mPercent+percent,0.0f,1.0f);
	if(mPercent<=0.0f)
	{
		mEHeartState = EHeartState::EMPTY;
	}
	else if(mPercent>=1.0f)
	{
		mEHeartState = EHeartState::FULL;
	}
	else
	{
		mEHeartState = EHeartState::PART;
	}
	heartImg->GetDynamicMaterial()->SetScalarParameterValue("percent",mPercent);
}

const EHeartState& UHeartWidget::GetState() const
{
	return mEHeartState;
}

const float& UHeartWidget::GetPercent() const
{
	return mPercent;
}

void UHeartWidget::SetPercent(const float& percent)
{
	mPercent = percent;
}
