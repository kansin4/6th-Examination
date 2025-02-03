// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnFloor.generated.h"

UCLASS()
class SPARTAPROJECT_API ASpawnFloor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnFloor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* ParticleComp;

	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Setting|Timer")
	float timer = 5.0f;
	FTimerHandle TimerHandle; // 타이머 핸들
	void ToggleVisibility();

};
