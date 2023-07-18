// Fill out your copyright notice in the Description page of Project Settings.


#include "IceMakerComponent.h"

#include "IceCube.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UIceMakerComponent::UIceMakerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UIceMakerComponent::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp,Warning,TEXT("%s"),*GetAttachParent()->GetFName().ToString());
	// ...
	
}


// Called every frame
void UIceMakerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//TObjectPtr<USceneComponent> cam = GetAttachParent();
	//UE_LOG(LogTemp,Warning,TEXT("%s"),*cam->GetForwardVector().ToString());
	if(mbActive)
	{
		FVector loc = GetComponentLocation();

		TObjectPtr<USceneComponent> cam = GetAttachParent();
		FVector end = loc+(cam->GetForwardVector()*1000.0f);
	
		FHitResult hitInfo;
		FCollisionQueryParams params;
		params.AddIgnoredActor(GetOwner());
		if(GetWorld()->LineTraceSingleByObjectType(hitInfo,loc,end,ECollisionChannel::ECC_GameTraceChannel1,params))
		{
			FVector newLoc = FMath::VInterpTo(mIceCube->GetActorLocation(),hitInfo.Location,DeltaTime,20.0f);
			mIceCube->SetActorLocation(newLoc);
			mIceCube->SetActorRotation(FRotationMatrix::MakeFromZ(hitInfo.ImpactNormal).Rotator());

			if(mIceCube->CheckForOverlap())
			{
				mIceCube->EnableBuilding();	
			}
			else
			{
				mIceCube->DisableBuilding();
			}
			//UE_LOG(LogTemp,Warning,TEXT("%d"),mIceCube->CheckForOverlap());
		}
	}
}

const TObjectPtr<UInputAction>& UIceMakerComponent::GetActivateIceAction() const
{
	return mActivateIceAction;
}

const TObjectPtr<UInputAction>& UIceMakerComponent::GetCreateIceAction() const
{
	return mCreateIceAction;
}

void UIceMakerComponent::Operate()
{
	if(mbActive)
	{
		deActivateIceCube();
	}
	else
	{
		activateIceCube();
	}
}

void UIceMakerComponent::Spawn()
{
	if(mbActive)
	{
		mIceCube->SpawnIceCube(mIceCube->GetActorTransform());
	}
}

void UIceMakerComponent::HandleEnableIceEvent()
{
	OnEnableIce.ExecuteIfBound();
}

void UIceMakerComponent::activateIceCube()
{
	FVector loc = GetComponentLocation();

	TObjectPtr<USceneComponent> cam = GetAttachParent();
	FVector end = loc+(cam->GetForwardVector()*1000.0f);
	
	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(hitInfo,loc,end,ECollisionChannel::ECC_Visibility,params);

	TObjectPtr<AIceCube> iceCube = GetWorld()->SpawnActor<AIceCube>(mIceCubeClass,hitInfo.Location,FRotator::ZeroRotator);
	mIceCube = iceCube;
	mbActive = true;
}

void UIceMakerComponent::deActivateIceCube()
{
	if(IsValid(mIceCube))
	{
		GetWorld()->DestroyActor(mIceCube);
		mbActive = false;
		
	}
}

