// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShooterEnemy::StartBeahviourTree(ASci_Fi_ShooterCharacter* Player)
{
	if (EnemyBehaviourTree)
	{
		MyCharacter = Cast<ASci_Fi_ShooterCharacter>(GetPawn());
		if (Player)
		{
			PlayerCharacter = Player;
		}
		RunBehaviorTree(EnemyBehaviourTree);
		
		UBlackboardComponent* MyBlackboard = GetBlackboardComponent();
		if (MyBlackboard && PlayerCharacter && MyCharacter)
		{
			MyBlackboard->SetValueAsVector("PlayerLocation", PlayerCharacter->GetActorLocation());
			
			MyBlackboard->SetValueAsVector("StartLocation", MyCharacter->GetActorLocation());
		}
	}
}
