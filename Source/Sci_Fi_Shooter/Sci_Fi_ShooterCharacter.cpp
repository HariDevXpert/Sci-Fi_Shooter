// Copyright Epic Games, Inc. All Rights Reserved.

#include "Sci_Fi_ShooterCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Sci_Fi_Shooter.h"

void ASci_Fi_ShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(
		this,
		&ASci_Fi_ShooterCharacter::OnDamageTaken
	);

	Health = MaxHealth;

	GetMesh()->HideBoneByName(
		TEXT("weapon_r"),
		EPhysBodyOp::PBO_None
	);

	// ---------------- RIFLE ----------------

	Rifle = GetWorld()->SpawnActor<AWeaponBase>(RifleClass);

	if (Rifle)
	{
		Rifle->SetOwner(this);
		Rifle->OwnerController = GetController();

		Rifle->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			TEXT("WeaponSocket")
		);
	}

	// ---------------- LAUNCHER ----------------

	Launcher = GetWorld()->SpawnActor<AWeaponBase>(LauncherClass);
	if (Launcher)
	{
		Launcher->SetOwner(this);
		Launcher->OwnerController = GetController();

		Launcher->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			TEXT("WeaponSocket")
		);

		Launcher->SetActorHiddenInGame(true);
	}

	CurrentWeapon = Rifle;
}

ASci_Fi_ShooterCharacter::ASci_Fi_ShooterCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
}

void ASci_Fi_ShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASci_Fi_ShooterCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ASci_Fi_ShooterCharacter::Look);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASci_Fi_ShooterCharacter::Look);
		
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ASci_Fi_ShooterCharacter::shoot);
		
		EnhancedInputComponent->BindAction(SwitchWeaponAction,ETriggerEvent::Started,this,&ASci_Fi_ShooterCharacter::SwitchWeapon);

	}
}

void ASci_Fi_ShooterCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	DoMove(MovementVector.X, MovementVector.Y);
}

void ASci_Fi_ShooterCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ASci_Fi_ShooterCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ASci_Fi_ShooterCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ASci_Fi_ShooterCharacter::DoJumpStart()
{
	Jump();
}

void ASci_Fi_ShooterCharacter::DoJumpEnd()
{

	StopJumping();
}

void ASci_Fi_ShooterCharacter::shoot()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->PullTrigger();
	}
}

void ASci_Fi_ShooterCharacter::Heal(float Amount)
{
	if (!IsAlive || Amount <= 0.0f)
	{
		return;
	}

	Health = FMath::Clamp(
		Health + Amount,
		0.0f,
		MaxHealth
	);
}
/*
void ASci_Fi_ShooterCharacter::OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
											 class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || !IsAlive)
	{
		return;
	}

	Health -= Damage;

	if (Health <= 0.0f)
	{
		IsAlive = false;
		Health = 0.0f;
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		APlayerController* PC = Cast<APlayerController>(GetController());

		if (PC && LoseWidgetClass)
		{
			UUserWidget* LoseWidget = CreateWidget<UUserWidget>(PC, LoseWidgetClass);
			if (LoseWidget)
			{
				LoseWidget->AddToViewport();

				PC->SetShowMouseCursor(true);
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(LoseWidget->TakeWidget());
				PC->SetInputMode(InputMode);
			}
		}

		DetachFromControllerPendingDestroy();

		UE_LOG(LogTemp, Display, TEXT("Character is dead"));
	}
}
*/
void ASci_Fi_ShooterCharacter::OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
											 class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || !IsAlive)
	{
		return;
	}

	Health -= Damage;

	if (Health <= 0.0f)
	{
		IsAlive = false;
		Health = 0.0f;
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		const bool bIsPlayer = GetController() && GetController()->IsA<APlayerController>();

		if (bIsPlayer)
		{
			// The player died
			ShowEndScreen(LoseWidgetClass);
		}
		else
		{
			// An enemy died — was the SHOOTER the player?
			if (InstigatedBy && InstigatedBy->IsA<APlayerController>())
			{
				if (ASci_Fi_ShooterCharacter* PlayerChar =
					Cast<ASci_Fi_ShooterCharacter>(InstigatedBy->GetPawn()))
				{
					PlayerChar->AddKill();
				}
			}
		}

		DetachFromControllerPendingDestroy();

		UE_LOG(LogTemp, Display, TEXT("Character is dead"));
	}
}

void ASci_Fi_ShooterCharacter::SwitchWeapon()
{
	if (!Rifle || !Launcher)
	{
		return;
	}

	if (CurrentWeapon == Rifle)
	{
		Rifle->SetActorHiddenInGame(true);
		Launcher->SetActorHiddenInGame(false);

		CurrentWeapon = Launcher;
	}
	else
	{
		Launcher->SetActorHiddenInGame(true);
		Rifle->SetActorHiddenInGame(false);

		CurrentWeapon = Rifle;
	}
}

void ASci_Fi_ShooterCharacter::CollectDiamond()
{
	if (!IsAlive)
	{
		return;
	}

	DiamondsCollected++;

	if (DiamondsCollected >= TotalDiamonds)
	{
		ShowEndScreen(WinWidgetClass);
	}
}

void ASci_Fi_ShooterCharacter::ShowEndScreen(TSubclassOf<UUserWidget> WidgetClass)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC || !WidgetClass)
	{
		return;
	}

	UUserWidget* Widget = CreateWidget<UUserWidget>(PC, WidgetClass);
	if (Widget)
	{
		Widget->AddToViewport();
		PC->SetShowMouseCursor(true);

		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(Widget->TakeWidget());
		PC->SetInputMode(InputMode);
	}
}

void ASci_Fi_ShooterCharacter::AddKill()
{
	Kills++;
}