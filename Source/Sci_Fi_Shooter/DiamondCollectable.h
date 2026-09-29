#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "DiamondCollectable.generated.h"

UCLASS()
class SCI_FI_SHOOTER_API ADiamondCollectable : public ACollectable
{
	GENERATED_BODY()

public:
	virtual void OnCollected_Implementation(ASci_Fi_ShooterCharacter* Collector) override;
};