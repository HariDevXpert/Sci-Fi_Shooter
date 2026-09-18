// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = SceneRoot;
	
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Gun Mesh");
	GunMesh->SetupAttachment(SceneRoot);
	
	//MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>("Muzzle Flash");
	//MuzzleFlashParticleSystem->SetupAttachment(GunMesh);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	//MuzzleFlashParticleSystem->Deactivate();
	
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::PullTrigger()
{
	if (OwnerController)
	{
		FVector ViewpointLocation;
		FRotator ViewPointRotation;
		OwnerController->GetPlayerViewPoint(ViewpointLocation,ViewPointRotation);
		
		FVector EndLocation = ViewpointLocation + ViewPointRotation.Vector() * MaxRange;
		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult , ViewpointLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel1, Params);
		if (IsHit)
		{
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 16, FColor::Red, true, 2.0f);
		}
	}
}

