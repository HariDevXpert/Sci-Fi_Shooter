// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "ShooterEnemy.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	EBTNodeResult::Type Result = EBTNodeResult::Failed;
	AShooterEnemy* OwnerController= Cast<AShooterEnemy>(OwnerComp.GetAIOwner());
	
	if (OwnerController)
	{
		ASci_Fi_ShooterCharacter* OwnerCharacter = OwnerController->MyCharacter;
		ASci_Fi_ShooterCharacter* PlayerCharacter = OwnerController->PlayerCharacter;
		
		if (PlayerCharacter && OwnerCharacter && PlayerCharacter->IsAlive)
		{
			OwnerCharacter->shoot();
			Result = EBTNodeResult::Succeeded;
		}
	}
	return Result;
}
