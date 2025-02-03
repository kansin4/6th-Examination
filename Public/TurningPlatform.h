// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurningPlatform.generated.h"

 // 명시적으로 기재 가능 NotBlueprintable, BlueprintType 로 BP 상속불가 설정 가능, BP Type은 변수로 선언가능하게 해줌
UCLASS()
class SPARTAPROJECT_API ATurningPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurningPlatform();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlatForm|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlatForm|Components")
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Speed|Properties")
	float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed|Properties")
	float MovingSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Speed|Properties")
	bool bMovingForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function|StartLocation")
	FVector StartLocation = FVector(430.0f, 4630.0f, 1960.0f); // 시작 지점 좌표 설정

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function|EndLocation")
	FVector EndLocation = FVector(12842.0f, 41802.0f, 22850.0f); // 끝 지점 좌표 설정

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
