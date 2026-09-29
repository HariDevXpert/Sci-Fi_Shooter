// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "WeaponBase.h"
#include "Sci_Fi_ShooterCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UUserWidget;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(abstract)
class ASci_Fi_ShooterCharacter : public ACharacter
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* ShootAction;

public:

	ASci_Fi_ShooterCharacter();	

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

public:

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* SwitchWeaponAction;
	
	//Weapon
	
	void shoot();
	UPROPERTY(EditAnywhere, Category="Weapons")
	TSubclassOf<AWeaponBase> RifleClass;

	UPROPERTY(EditAnywhere, Category="Weapons")
	TSubclassOf<AWeaponBase> LauncherClass;

	UPROPERTY()
	AWeaponBase* Rifle;

	UPROPERTY()
	AWeaponBase* Launcher;

	UPROPERTY()
	AWeaponBase* CurrentWeapon;

	UFUNCTION()
	void SwitchWeapon();
	
	//Health
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health")
	float Health ;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsAlive = true;	
	
	UFUNCTION(BlueprintCallable, Category="Health")
	void Heal(float Amount);
	
	UFUNCTION()
	void OnDamageTaken( AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	//Diamonds

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Diamonds")
	int32 TotalDiamonds = 4;

	UPROPERTY(BlueprintReadOnly, Category="Diamonds")
	int32 DiamondsCollected = 0;

	UFUNCTION(BlueprintCallable, Category="Diamonds")
	void CollectDiamond();
	
	//Kills
	UPROPERTY(BlueprintReadOnly, Category="Kills")
	int32 Kills = 0;

	UFUNCTION(BlueprintCallable, Category="Kills")
	void AddKill();
	
	//UI

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TSubclassOf<UUserWidget> LoseWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TSubclassOf<UUserWidget> WinWidgetClass;

	void ShowEndScreen(TSubclassOf<UUserWidget> WidgetClass);
	
};
