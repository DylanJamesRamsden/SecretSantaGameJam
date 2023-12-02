// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameplayCharacter.h"

#include "DPlayerCharacterInputConfig.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ADGameplayCharacter::ADGameplayCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);

	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = .95f;
	SpringArmComp->bDoCollisionTest = false;
	SpringArmComp->TargetArmLength = 1000.0f;

	SpringArmComp->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	SpringArmComp->SetAbsolute(false, true);
}

// Called when the game starts or when spawned
void ADGameplayCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADGameplayCharacter::MoveHorizontal(const FInputActionValue&  Value)
{
	// https://forums.unrealengine.com/t/frame-rate-independence/127007/5
	GetMovementComponent()->AddInputVector(FVector::RightVector * Value.Get<float>());

	// Triggers our turn logic
	if ((bIsFacingRight && Value.Get<float>() < 0) || (!bIsFacingRight && Value.Get<float>() > 0))
	{
		bIsFacingRight = !bIsFacingRight;
		bIsTurning = true;

		bIsFacingRight ? TargetTurnRotation = FRotator(0.0f, 0.0f, 0.0f) : TargetTurnRotation = FRotator(0.0f, 180.0f, 0.0f);
	}
}

void ADGameplayCharacter::ToggleSprint(const FInputActionValue&  Value)
{
	bIsSprinting = !bIsSprinting;

	float MovementSpeed = 0.0f;
	bIsSprinting ? MovementSpeed = 500.0f : MovementSpeed = 200.0f;
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

// Called every frame
void ADGameplayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsTurning)
	{
		// @TODO Look into this, I swear this number shouldn't be this large???
		GetMesh()->SetRelativeRotation(FMath::RInterpConstantTo(GetMesh()->GetRelativeRotation(),
			TargetTurnRotation, DeltaTime, 500.0f));

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, GetMesh()->GetRelativeRotation().ToString());

		if (GetMesh()->GetRelativeRotation() == TargetTurnRotation) bIsTurning = false;
	}
}

// Called to bind functionality to input
void ADGameplayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	check(EnhancedInputComponent);

	// By the time this function is called, the pawn already has a controller and local player
	APlayerController* PC = Cast<APlayerController>(GetController());
	check(PC);
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	check(EnhancedInputLocalPlayerSubsystem)
	
	EnhancedInputLocalPlayerSubsystem->ClearAllMappings();
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(PlayerCharacterInputConfig->PlayerCharacterIMC, 0);

	// @TODO Look into the different triggers for enhanced input again
	EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->MoveHorizontalIA, ETriggerEvent::Triggered, this, &ADGameplayCharacter::MoveHorizontal);
	EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->JumpIA, ETriggerEvent::Triggered, this, &ADGameplayCharacter::Jump);
	EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->SprintIA, ETriggerEvent::Triggered, this, &ADGameplayCharacter::ToggleSprint);
}

