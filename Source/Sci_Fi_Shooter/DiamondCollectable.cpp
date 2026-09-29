#include "DiamondCollectable.h"
#include "Sci_Fi_ShooterCharacter.h"

void ADiamondCollectable::OnCollected_Implementation(ASci_Fi_ShooterCharacter* Collector)
{
	if (Collector)
	{
		Collector->CollectDiamond();
	}
}