// Fill out your copyright notice in the Description page of Project Settings.


#include "Rocket.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ARocket::ARocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
	Super::BeginPlay();

	FLatentActionInfo F;
	F.CallbackTarget = this;
	F.ExecutionFunction = FName(TEXT("DelayFunction"));
	F.Linkage = 1;
	F.UUID = 0;

	UE_LOG(LogTemp, Warning, TEXT("Hello"));

	UKismetSystemLibrary::Delay(GetWorld(),
		1.0f, F);


	
}

void ARocket::DelayFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("World"));

	UE_LOG(LogTemp, Warning, TEXT("DelayFunction"));
}

// Called every frame
void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

