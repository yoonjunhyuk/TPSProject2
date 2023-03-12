// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPSPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "PlayerBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UPlayerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerBaseComponent()
	{
		// Tick �Լ��� ȣ����� �ʵ��� ó��
		PrimaryComponentTick.bCanEverTick = false;
		bWantsInitializeComponent = true;
	};

	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;

	// ����� �Է� ���� ó�� �Լ�
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) {};

public:
	UPROPERTY()
	ATPSPlayer* me;
		
	UPROPERTY()
	UCharacterMovementComponent* moveComp;
};