#pragma once 

#include "CoreMinimal.h" 
#include "GameFramework/Actor.h" 
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Item.generated.h"


UCLASS() // 리플렉션 시스템 관련 매크로
class SPARTAPROJECT_API AItem : public AActor // API는 빌드와 관련이 있는 매크로
{
	GENERATED_BODY() // UCLASS랑 짝꿍 매크로
	
public:	
	AItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	float RotationSpeed;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Item|Actions") // BP 호출 가능
	void ResetActorPosition();

	UFUNCTION(BlueprintPure, Category = "Item|Properties") // BP에서 리턴값만 반환 받는 함수
	float GetRotationSpeed() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Item|Event") // 구현은 BP에서 호출은 C++로
	void OnItemPickedUP();
	
};

// 생성자 - 메모리에 생김. 단 한번 호출됨
// PostInitializeComponents() - 컴포넌트가 완성된 직후 호출, 컴포넌트끼리 데이터 주고받기, 상호작용
// BeginPlay() - 배치 (Spawn) 직후 
// Tick(float DeltaTime) - 매 프레임마다 호출됨
// Destroyed() - 삭제가 되기 직전에 호출된다
// EndPlay() - 게임 종료, 파괴 ((Destroyed()), 레벨 전환, 끝나는 모든것에 항상 불려오는 함수(심지어 디스트로이 내부에서도!)
