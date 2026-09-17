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

