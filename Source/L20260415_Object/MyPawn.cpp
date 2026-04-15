// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Rocket.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);

	Left->SetRelativeLocation(FVector(39.4f, -20.0f, 1.4f));

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);
	Right->SetRelativeLocation(FVector(39.4f, 20.0f, 1.4f));


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	static ConstructorHelpers::FClassFinder<ARocket> BP_Rocket(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Rocket.BP_Rocket_C'"));
	if (BP_Rocket.Succeeded())
	{
		RocketTemplate = BP_Rocket.Class;
	}
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), BoostValue);

	Left->AddRelativeRotation(FRotator(0, 0, DeltaTime * 4800.0f));
	Right->AddRelativeRotation(FRotator(0, 0, DeltaTime * 4800.0f));

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UIC->BindAction(IA_Rotate, ETriggerEvent::Triggered, this, &AMyPawn::Rotate);
		UIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyPawn::Fire);
		UIC->BindAction(IA_Boost, ETriggerEvent::Triggered, this, &AMyPawn::Boost);
		UIC->BindAction(IA_Boost, ETriggerEvent::Completed, this, &AMyPawn::Unboost);

	}
}

void AMyPawn::Rotate(const FInputActionValue& Value)
{
	FVector2D Rot = Value.Get<FVector2D>();
	Rot = Rot * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f;

	AddActorLocalRotation(FRotator(Rot.Y, 0, Rot.X));

}

void AMyPawn::Fire(const FInputActionValue& Value)
{
	GetWorld()->SpawnActor<ARocket>(RocketTemplate, Arrow->K2_GetComponentToWorld());
}

void AMyPawn::Boost(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Boost %d"), Value.Get<bool>());
	BoostValue = 1.0f;
}

void AMyPawn::Unboost(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Unboost"));
	BoostValue = 0.5f;
}

