#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROSBridgeHandler.h"
#include <Physics/RModel.h>
#include "FROSJointTrajectorySubscriber.h"

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
	// Array of pointers to joint trajectory subscribers
	TArray<TSharedPtr<FROSJointTrajectorySubscriber>> JointTrajectorySubscribers;
	// Array of pointers to robot models
	TArray<ARModel> robotModels;


	UPROPERTY(EditAnywhere, Category = "ROS Settings")
	FString ROSBridgeServerIPAddr;

	UPROPERTY(EditAnywhere, Category = "ROS Settings")
	uint32 ROSBridgeServerPort;

	UPROPERTY(EditAnywhere, Category = "ROS Settings")
	FString ROSSubscriberTopicName;

	UPROPERTY(EditAnywhere, Category = "ROS Settings")
	float ROSTrajectoryUpdateFrequency;

	UPROPERTY(EditAnywhere, Category = "ROS Settings")
	int ROSTrajectoryMaxSteps;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
