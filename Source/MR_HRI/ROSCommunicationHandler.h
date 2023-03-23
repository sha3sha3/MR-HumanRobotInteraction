// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROSBridgeHandler.h"
#include <Physics/RModel.h>
#include "ROSCommunicationHandler.generated.h"


UCLASS()
class MR_HRI_API AROSCommunicationHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AROSCommunicationHandler();

	// Pointer to ROSBridge handler for ROS-UE communication
	TSharedPtr<FROSBridgeHandler> Handler;
	// Pointer referencing robot model
	TSharedPtr<ARModel> RoboModelPtr;

	UPROPERTY(EditAnywhere, Category = "ROS Settings")
	FString ROSBridgeServerIPAddr;

	UPROPERTY(EditAnywhere, Category = "ROS Settings")
	uint32 ROSBridgeServerPort;

	UPROPERTY(EditAnywhere, Category = "ROS Settings")
	FString ROSSubscriberTopicName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
