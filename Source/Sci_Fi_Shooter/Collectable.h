#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

class ASci_Fi_ShooterCharacter;
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
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Collectable")
            void OnCollected(ASci_Fi_ShooterCharacter* Collector);
            virtual void OnCollected_Implementation(ASci_Fi_ShooterCharacter* Collector);
    
    protected:
        UFUNCTION()
        void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                       bool bFromSweep, const FHitResult& SweepResult);
    
        
};