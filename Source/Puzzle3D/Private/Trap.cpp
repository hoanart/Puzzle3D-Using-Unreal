// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(root);
	trap = CreateDefaultSubobject<UStaticMeshComponent>(FName("Trap"));
	trap->SetupAttachment(root);
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	startLoc = GetActorLocation();
	trap->OnComponentHit.AddDynamic(this,&ATrap::OnHit);
	if(trigger)
	{
		CastChecked<UStaticMeshComponent>( trigger->GetRootComponent())->OnComponentBeginOverlap.AddDynamic(this,&ATrap::ATrap::OnOverlapBegin);
	}
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ATrap::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp,
	FVector NormalImpulse, const FHitResult& hit)
{

	if(IsValid(otherActor))
	{
		UE_LOG(LogTemp,Display,TEXT("%s"),*otherActor->GetFName().ToString());
		if(IsValid(objForRestart))
		{
			otherActor->SetActorLocation(objForRestart->GetActorLocation());
			trap->SetEnableGravity(false);
			
			trap->SetWorldLocation(startLoc);
		}
	}
}

void ATrap::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 otherBoxIndex, bool bFromSweep, const FHitResult& hit)
{
	if(IsValid(otherActor)&&!trap->IsGravityEnabled())
	{
		if(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->GetFName() == otherActor->GetFName())
		{
			UE_LOG(LogTemp,Display,TEXT("중력 시작"));
			
			trap->SetEnableGravity(true);
		}
	}
}


