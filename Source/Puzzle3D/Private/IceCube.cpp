// Fill out your copyright notice in the Description page of Project Settings.


#include "IceCube.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AIceCube::AIceCube()
	: mbOnce(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	mIceCube = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("IceCube"));
	mIceCube->SetupAttachment(Root);
	
	mBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	mBox->SetupAttachment(Root);

	mCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	mCollision->SetupAttachment(Root);
	timeLineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("TIMELINE"));
}

// Called when the game starts or when spawned
void AIceCube::BeginPlay()
{
	Super::BeginPlay();
	if(IsValid(mCollisionExpansionCurve))
	{
		FOnTimelineFloat curveCallback;
		FOnTimelineEvent lerpTimeFinishedCallback;

		curveCallback.BindUFunction(this,FName("expandCollisionTimeLine"));

		timeLineComp->AddInterpFloat(mCollisionExpansionCurve,curveCallback);
		timeLineComp->SetLooping(false);
	}
}

// Called every frame
void AIceCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AIceCube::CheckForOverlap()
{
	FVector loc = mBox->GetComponentLocation();
	FVector size = mBox->GetScaledBoxExtent();
	FRotator rot = mBox->GetComponentRotation();
	TArray<FHitResult> hitInfos;
	TArray<AActor*> actorToIgnore = {GetOwner()};
	UKismetSystemLibrary::BoxTraceMulti(GetWorld(),loc,loc,size,rot,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,actorToIgnore,EDrawDebugTrace::None,hitInfos,
		true,FLinearColor::Red,FLinearColor::Green,0.1f);
	bool bOverlap = false;
	for(auto hitInfo : hitInfos)
	{
		//UE_LOG(LogTemp,Warning,TEXT("%s"),*hitInfo.GetActor()->GetFName().ToString());

		if(hitInfo.Component->GetCollisionObjectType()!=ECC_GameTraceChannel1)
		{
			//UE_LOG(LogTemp,Display,TEXT("%d"),hitInfo.GetComponent()->GetCollisionObjectType());
			//DrawDebugBox(GetWorld(),loc,size, rot.Quaternion(), FColor::Red,false,1.0f,0,1);
			bOverlap = !hitInfo.Component->IsSimulatingPhysics();
		}
	}
	
	return !bOverlap;
}

void AIceCube::EnableBuilding()
{
	
	if(!mbOnce)
	{
		mbOnce = true;
		//TObjectPtr<UAnimationAsset> anim = mIceCube->GetAnimInstance()->GetCurrentActiveMontage();
		if(IsValid(mIceCubeAnim))
		{
			mIceCube->PlayAnimation(mIceCubeAnim,true);
		}
		
		
		mIceCube->ClearMorphTargets();
		mCanPlace = true;
		mIceCube->SetMaterial(0,mEnableMat);
	}
}

void AIceCube::DisableBuilding()
{
	if(mbOnce)
	{
		mbOnce = false;
		
		mIceCube->Stop();
		mIceCube->SetMorphTarget(FName("Short"),0.0f,false);
		
		mCanPlace = false;
		mIceCube->SetMaterial(0,mDisableMat);
	}
	
}

void AIceCube::SpawnIceCube(const FTransform& transform)
{
	if(mCanPlace)
	{
		TObjectPtr<AIceCube> newIce = GetWorld()->SpawnActor<AIceCube>(GetClass(),transform);
		newIce->mCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		newIce->mIceCube->PlayAnimation(mIceCubeAnim,false);
		newIce->timeLineComp->PlayFromStart();
		//onSpawned();
	}
}

void AIceCube::onSpawned()
{
	mCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	mIceCube->PlayAnimation(mIceCubeAnim,false);
	mCollisionTimeline.Play();
}

TObjectPtr<UBoxComponent> AIceCube::GetBox() const
{
	return mBox;
}

void AIceCube::expandCollisionTimeLine(float value)
{
	
	FVector boxExtent = mCollision->GetScaledBoxExtent();
	boxExtent.Z= FMath::Lerp(boxExtent.Z,100,value);
	mCollision->SetBoxExtent(boxExtent);
	//UE_LOG(LogTemp,Warning,TEXT("%f"),boxExtent.Z);
	mCollision->SetRelativeLocation(FVector(0.0f,0.0f,boxExtent.Z));
}

void AIceCube::SetCanPlace(const bool& canPlace)
{
	mCanPlace = canPlace;
}

bool AIceCube::CanPlace() const
{
	return mCanPlace;
}

void AIceCube::ExpandCol()
{
	
}
