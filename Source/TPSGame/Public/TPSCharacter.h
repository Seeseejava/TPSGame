// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ATPSWeapon;
class UTPSHealthComponent;

UCLASS()
class TPSGAME_API ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void LookUp(float Value);

	void Turn(float Value);

	void BeginCrouch();

	void EndCrouch();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")  // 不加弹簧臂的话上下旋转有问题
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTPSHealthComponent* HealthComp;

	bool bWantsToZoom;
	
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float ZoomedFOV;
	
	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.1, ClampMax = 100))
	float ZoomInterpSpeed;

	float DefaultFOV;

	void BeginZoom();

	void EndZoom();


	UPROPERTY(Replicated)
	ATPSWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<ATPSWeapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName WeaponAttachScoketName;

	void StartFire();

	void StopFire();

	UFUNCTION()
	void OnHealthChanged(UTPSHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/* Pawn died previously*/
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
	bool bDied;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//重载pawn的视线位置，从眼睛改为摄像机
	virtual FVector GetPawnViewLocation() const;

};
