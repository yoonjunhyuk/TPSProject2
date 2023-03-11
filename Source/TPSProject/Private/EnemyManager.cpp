#include "EnemyManager.h"
#include "Enemy.h"
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
	// 랜덤 생성 시간 구하기
	float createTime = FMath::RandRange(minTime, maxTime);
	// Timer Manager한테 알람 등록
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);

	FindSpawnPoints();
}

void AEnemyManager::CreateEnemy()
{
	// 랜덤 위치 구하기
	int index = FMath::RandRange(0, spawnPoints.Num() - 1);
	// 적 생성 및 배치하기
	GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnPoints[index]->GetActorLocation(), FRotator(0));
	// 다시 랜덤 시간에 CreateEnemy함수가 호출되도록 타이머 설정
	float createTime = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
}

// TActorIterator를 이용한 액터 찾기(#include <EngineUtils.h>를 추가)
/*
void AEnemyManager::FindSpawnPoints()
{
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* spawn = *It;
		// 찾은 액터의 이름에 해당 문자열을 포함하고 있다면
		if (spawn->GetName().Contains(TEXT("BP_EnemySpawnPoint")))
		{
			// 스폰 목록에 추가
			spawnPoints.Add(spawn);
		}
	}
}
*/

// GetAllActorsOfClass를 이용한 액터 찾기(#include <Kismet/GameplayStatics.h>를 추가)
void AEnemyManager::FindSpawnPoints()
{
	// 검색으로 찾은 결과를 저장할 배열
	TArray<AActor*> allActors;
	// 원하는 타입의 액터 모두 찾아오기
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
	// 찾은 결과가 있을 경우 반복적으로
	for (auto spawn : allActors)
	{
		// 찾은 액터의 이름에 해당 문자열을 포함하고 있다면
		if (spawn->GetName().Contains(TEXT("BP_EnemySpawnPoint")))
		{
			// 스폰 목록에 추가
			spawnPoints.Add(spawn);
		}
	}
}