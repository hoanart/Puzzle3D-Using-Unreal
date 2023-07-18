// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "MainHUDWidget.h"
#include "Blueprint/UserWidget.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	mHUD = Cast<UMainHUDWidget>( CreateWidget(this,mHUDclass));

	if(IsValid(mHUD))
	{
		mHUD->AddToViewport();
	}
}
