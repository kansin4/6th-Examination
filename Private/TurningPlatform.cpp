// Fill out your copyright notice in the Description page of Project Settings.


#include "TurningPlatform.h"

// Sets default values
ATurningPlatform::ATurningPlatform()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_AssetPlatform.SM_AssetPlatform"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("Game/Resources/Props/Materials/M_StatueGlass.M_StatueGlass"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;
	MovingSpeed = 1000.0f;
	bMovingForward = true;


}

// 0.5~1 특정값까지 증가하는 가속도 * 델타타임 

void ATurningPlatform::BeginPlay()
{
    Super::BeginPlay();
    SetActorLocation(StartLocation); // 시작 지점으로 위치 설정
}

// Called every frame
void ATurningPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // if (!FMath::IsNearlyZero(RotationSpeed))
    // {
    //     AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
    // }

    FVector CurrentLocation = GetActorLocation();
    FVector Direction = bMovingForward ? (EndLocation - StartLocation).GetSafeNormal() : (StartLocation - EndLocation).GetSafeNormal();
    FVector DeltaLocation = Direction * MovingSpeed * DeltaTime;
    FVector NewLocation = CurrentLocation + DeltaLocation;

    if (bMovingForward && FVector::Dist(NewLocation, EndLocation) < 10.0f)
    {
        bMovingForward = false;
    }
    else if (!bMovingForward && FVector::Dist(NewLocation, StartLocation) < 10.0f)
    {
        bMovingForward = true;
    }

    SetActorLocation(NewLocation);

}