#include "Collectable.h"
#include "Sci_Fi_ShooterCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

ACollectable::ACollectable()
{
    PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    RootComponent = SceneRoot;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(SceneRoot);

    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    Collision->SetupAttachment(SceneRoot);

    Collision->SetSphereRadius(75.0f);

    Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
    Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ACollectable::BeginPlay()
{
    Super::BeginPlay();
    
    Collision->OnComponentBeginOverlap.AddDynamic(this, &ACollectable::OnOverlap);
}

void ACollectable::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                             bool bFromSweep, const FHitResult& SweepResult)
{
    ASci_Fi_ShooterCharacter* Character = Cast<ASci_Fi_ShooterCharacter>(OtherActor);

    if (!Character || !Character->IsAlive)
    {
        return;
    }

    const bool bIsPlayer = Character->GetController() && Character->GetController()->IsA<APlayerController>();
    if (!bIsPlayer)
    {
        return;
    }

    OnCollected(Character);

    if (DestroyAfterCollect)
    {
        Destroy();
    }
}

void ACollectable::OnCollected_Implementation(ASci_Fi_ShooterCharacter* Collector)
{
   
}