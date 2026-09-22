// Copyright Epic Games, Inc. All Rights Reserved.

#include "Sci_Fi_ShooterGameMode.h"
#include "kismet/GameplayStatics.h"
#include "Sci_Fi_ShooterCharacter.h"
#include "Sci_Fi_Shooter.h"
#include "ShooterEnemy.h"

ASci_Fi_ShooterGameMode::ASci_Fi_ShooterGameMode()
{
	// stub
}
void ASci_Fi_ShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	ASci_Fi_ShooterCharacter* Player = Cast<ASci_Fi_ShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	TArray<AActor*> ShooterAiActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterEnemy::StaticClass(), ShooterAiActors);
	
	for (AActor* ShooterAiActor : ShooterAiActors)
	{
		AShooterEnemy* ShooterEnemy = Cast<AShooterEnemy>(ShooterAiActor);
		
		if (ShooterEnemy)
		{
			ShooterEnemy->StartBeahviourTree(Player);
		}
	}
}