// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaWidget.h"

#include "MainCharacter.h"
#include "Sprinter.h"
#include "Components/Image.h"

void UStaminaWidget::NativeConstruct()
{
	Super::NativeConstruct();
	mStaminaBar = Cast<UImage>(GetWidgetFromName("StaminaBar"));
	if(!IsValid(mStaminaBar))
	{
		UE_LOG(LogTemp,Warning,TEXT("Need staminaImg"));
		return;
	}
	const APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	mMainCharacter = Cast<AMainCharacter>(playerController->GetPawn());
	if(!IsValid(mMainCharacter))
	{
		UE_LOG(LogTemp,Warning,TEXT("Need mMainCharacter"));
		return;
	}
}

void UStaminaWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	check(mMainCharacter->GetSprinterComp()!=nullptr);
	 TObjectPtr<USprinter> sprintComp = mMainCharacter->GetSprinterComp();
	//TODO: MainCharacter Need Exhausted state check
	//Exhausted 상태인 경우 레드
	//아닌 경우 그린
	switch (mMainCharacter->GetSprinterComp()->GetCurrentEState())
	{
	case  EState::EXHAUSTED:
		changeStaminaColor(FLinearColor::Red,mBarColor);
		break;
	default:
		changeStaminaColor(FLinearColor::Green,mBarColor);
	}
	
	//TODO: Set gageValue 현재 스테미너 레벨 / 전체 스테미너 레벨로 백분율로 변환
	//이후 머테리얼에 스칼라 파라미터값 변환
	float gageValue = sprintComp->ConvertCurrStaminaToPercent();
	mStaminaBar->GetDynamicMaterial()->SetScalarParameterValue("Decimal",gageValue);
}

UImage* UStaminaWidget::GetStaminaBar() const
{
	return mStaminaBar;
}

void UStaminaWidget::changeStaminaColor(const FLinearColor& color, FLinearColor& target)
{
	if(target!=color)
	{
		target = color;
		mStaminaBar->GetDynamicMaterial()->SetVectorParameterValue("Color",target);
	}
}
