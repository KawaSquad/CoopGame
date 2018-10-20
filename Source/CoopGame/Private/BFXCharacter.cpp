// Fill out your copyright notice in the Description page of Project Settings.

#include "BFXCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"


// Sets default values
ABFXCharacter::ABFXCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ABFXCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABFXCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}
void ABFXCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}



void ABFXCharacter::BeginCrouch()
{
	Crouch();
}
void ABFXCharacter::EndCrouch()
{
	UnCrouch();
}

FVector ABFXCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}
	else
	{
		return Super::GetPawnViewLocation();
	}
}

// Called every frame
void ABFXCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABFXCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABFXCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABFXCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ABFXCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &ABFXCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ABFXCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ABFXCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABFXCharacter::Jump);

}

