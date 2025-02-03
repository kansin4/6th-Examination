#include "Item.h"

AItem::AItem()
{
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComp->SetupAttachment(SceneRoot);

    /*AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
    AudioComp->SetupAttachment(StaticMeshComp);*/

    PrimaryActorTick.bCanEverTick = true; // Tick 함수 사용 사용 안하면 false 로 꺼두는게 낫다
    RotationSpeed = 90.0f;

}

// 현재 : 거리 -> 절대값 
void AItem::BeginPlay()
{
    Super::BeginPlay();

    OnItemPickedUP();
    // FVector NewLocation(300.0f, 200.0f, 100.0f);
    // FRotator NewRotation(0.0f, 90.0f, 0.0f);
    // FVector NewScale(2.0f);

    // FTransform NewTransform(NewRotation, NewLocation, NewScale);
    // SetActorTransform(NewTransform);
    // Ftransform 함수를 이용하면 한번에 세 가지를 관리할 수 있다
}

void AItem::Tick(float DeltaTime) // 델타타임을 이용한 계산은 프레임 독립적 계산이라고도 부른다.
{
    Super::Tick(DeltaTime);

    // float은 근사값만 반환하므로 FMath를 이용해 근사값 0 을 조건으로 걸어줄 수 있다.
    if (!FMath::IsNearlyZero(RotationSpeed))
    {
        AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
    }
}

void AItem::ResetActorPosition()
{
    SetActorLocation(FVector::ZeroVector); // zerovector로 원점으로 돌릴 수 있다.
}

float AItem::GetRotationSpeed() const
{
    return RotationSpeed;
}
