// Fill out your copyright notice in the Description page of Project Settings.

#include "BFXWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Gameframework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABFXWeapon::ABFXWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ABFXWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABFXWeapon::Fire()
{
	AActor * MyOwner = GetOwner();
	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;

		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShootDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			AActor * HitActor = Hit.GetActor();

			if (HitActor)
			{
				UGameplayStatics::ApplyPointDamage(HitActor,20.0f,ShootDirection,Hit,MyOwner->GetInstigatorController(),this, DamageType);
			}

		}
		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::White, false, 1.0f,0, 1.0f);
	}
}

// Called every frame
void ABFXWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

