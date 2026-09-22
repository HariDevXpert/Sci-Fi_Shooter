// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Sci_Fi_ShooterCharacter.h"
#include "ShooterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SCI_FI_SHOOTER_API AShooterEnemy : public AAIController
{
	GENERATED_BODY()
	
protected:
virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	UBehaviorTree* EnemyBehaviourTree;
	
	ASci_Fi_ShooterCharacter* PlayerCharacter;
	ASci_Fi_ShooterCharacter* MyCharacter;
	UFUNCTION()
	void StartBeahviourTree(ASci_Fi_ShooterCharacter* Player);

};
