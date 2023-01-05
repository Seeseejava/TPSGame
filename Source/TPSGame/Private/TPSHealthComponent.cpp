// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSHealthComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UTPSHealthComponent::UTPSHealthComponent()
{
	DefaultHealth = 100;

	SetIsReplicatedByDefault(true);    // SetIsReplicated会报错
}


// Called when the game starts
void UTPSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (GetOwnerRole() == ROLE_Authority)
	{
		AActor* MyOwner = GetOwner();
		if (MyOwner)
		{
			MyOwner->OnTakeAnyDamage.AddDynamic(this, &UTPSHealthComponent::HandleTakeAnyDamage);
		}
	}

	Health = DefaultHealth;
}

void UTPSHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f)
	{
		return;
	}

	// 更新生命值上限
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	UE_LOG(LogTemp, Log, TEXT("Health Changed: %s"), *FString::SanitizeFloat(Health));

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
}

void UTPSHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTPSHealthComponent, Health);
}