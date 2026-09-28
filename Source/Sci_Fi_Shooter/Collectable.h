#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class SCI_FI_SHOOTER_API ACollectable : public AActor
{
    GENERATED_BODY()

public:

    ACollectable();

protected:

    virtual void BeginPlay() override;

public:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collectable")
    USceneComponent* SceneRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collectable")
    UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collectable")
    USphereComponent* Collision;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collectable")
    bool DestroyAfterCollect = true;
};