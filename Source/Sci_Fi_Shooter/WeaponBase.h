// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "WeaponBase.generated.h"

UCLASS()
class SCI_FI_SHOOTER_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	UNiagaraComponent* MuzzleFlashParticleSystem;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UNiagaraSystem* ImpactParticleSystem;
	
	UPROPERTY(EditAnywhere)
	float MaxRange = 10000.0f;
	
	UPROPERTY(EditAnywhere)
	AController* OwnerController;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float Damage = 20.0f;
	
	UFUNCTION()
	void PullTrigger();
};
