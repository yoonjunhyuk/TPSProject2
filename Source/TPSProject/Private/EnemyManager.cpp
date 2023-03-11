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
	
	// ���� ���� �ð� ���ϱ�
	float createTime = FMath::RandRange(minTime, maxTime);
	// Timer Manager���� �˶� ���
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);

	FindSpawnPoints();
}

void AEnemyManager::CreateEnemy()
{
	// ���� ��ġ ���ϱ�
	int index = FMath::RandRange(0, spawnPoints.Num() - 1);
	// �� ���� �� ��ġ�ϱ�
	GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnPoints[index]->GetActorLocation(), FRotator(0));
	// �ٽ� ���� �ð��� CreateEnemy�Լ��� ȣ��ǵ��� Ÿ�̸� ����
	float createTime = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
}

// TActorIterator�� �̿��� ���� ã��(#include <EngineUtils.h>�� �߰�)
/*
void AEnemyManager::FindSpawnPoints()
{
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* spawn = *It;
		// ã�� ������ �̸��� �ش� ���ڿ��� �����ϰ� �ִٸ�
		if (spawn->GetName().Contains(TEXT("BP_EnemySpawnPoint")))
		{
			// ���� ��Ͽ� �߰�
			spawnPoints.Add(spawn);
		}
	}
}
*/

// GetAllActorsOfClass�� �̿��� ���� ã��(#include <Kismet/GameplayStatics.h>�� �߰�)
void AEnemyManager::FindSpawnPoints()
{
	// �˻����� ã�� ����� ������ �迭
	TArray<AActor*> allActors;
	// ���ϴ� Ÿ���� ���� ��� ã�ƿ���
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
	// ã�� ����� ���� ��� �ݺ�������
	for (auto spawn : allActors)
	{
		// ã�� ������ �̸��� �ش� ���ڿ��� �����ϰ� �ִٸ�
		if (spawn->GetName().Contains(TEXT("BP_EnemySpawnPoint")))
		{
			// ���� ��Ͽ� �߰�
			spawnPoints.Add(spawn);
		}
	}
}