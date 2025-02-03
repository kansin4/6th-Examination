#include "SpawnFloor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

ASpawnFloor::ASpawnFloor()
{
    // 이 액터가 프레임마다 Tick()을 호출하도록 설정합니다.  이 설정이 필요 없는 경우 비활성화하면 퍼포먼스가 향상됩니다.
    PrimaryActorTick.bCanEverTick = true;

    //자체 디폴트 컴포넌트 생성
    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Floor"));
    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));

     SphereComp->SetupAttachment(RootComponent);

    StaticMeshComp->AttachToComponent(SphereComp, FAttachmentTransformRules::KeepRelativeTransform);
    ParticleComp->AttachToComponent(StaticMeshComp, FAttachmentTransformRules::KeepRelativeTransform);

    //스태틱 메시에 맞추어 스피어 반경을 더 작은 크기로 설정
    SphereComp->SetSphereRadius(16.0f);

    //스피어 반경에 맞추어 스태틱 메시 스케일 및 위치 설정
    StaticMeshComp->SetRelativeLocation(FVector(0.0, 0.0, -12.0f));
    StaticMeshComp->SetRelativeScale3D(FVector(0.25, 0.25, 0.25));

    //생성자 헬퍼를 사용하여 자체 스태틱 메시 컴포넌트를 스피어 셰이프로 설정
    static ConstructorHelpers::FObjectFinder<UStaticMesh>FloorMeshAsset(TEXT("/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400"));
    if (FloorMeshAsset.Succeeded())
    {
        StaticMeshComp->SetStaticMesh(FloorMeshAsset.Object);
    }

    //생성자 헬퍼를 사용하여 자체 파티클 컴포넌트를 자체 불 파티클 컴포넌트로 설정
    static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleCompAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
    ParticleComp->SetTemplate(ParticleCompAsset.Object);
}

// Called when the game starts or when spawned
void ASpawnFloor::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawnFloor::ToggleVisibility, timer, true);

}

// Called every frame
void ASpawnFloor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ASpawnFloor::ToggleVisibility()
{
    // 액터의 가시성을 토글
    bool bIsVisible = StaticMeshComp->IsVisible();
    StaticMeshComp->SetVisibility(!bIsVisible, true);
    ParticleComp->SetVisibility(!bIsVisible, true);
}
