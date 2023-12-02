// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameplayCharacter.h"

#include "Camera/CameraComponent.h"
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
	SpringArmComp->CameraLagSpeed = .5f;
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

// Called every frame
void ADGameplayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADGameplayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

