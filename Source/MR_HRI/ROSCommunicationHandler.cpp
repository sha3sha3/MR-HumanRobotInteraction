// Fill out your copyright notice in the Description page of Project Settings.
#include "ROSCommunicationHandler.h"

// Sets default values
AROSCommunicationHandler::AROSCommunicationHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AROSCommunicationHandler::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to robot model...
	const UWorld* World = GetWorld();
	ARModel* robotModel = NULL;
	for (TObjectIterator<ARModel> ObjectItr; ObjectItr; ++ObjectItr)
	{
		// skip if this object is not associated with our current game world
		if (ObjectItr->GetWorld() != World)
		{
			continue;
		}
		robotModel = *ObjectItr;
	}

	// Set up ROS Connection
	Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(*ROSBridgeServerIPAddr, ROSBridgeServerPort));
	Handler->Connect();	
	UE_LOG(LogTemp, Log, TEXT("[AROSCommunicationHandler::BeginPlay()] Websocket server connected."));

	// Add subscriber
	JointTrajectorySubscribers.Add(MakeShareable<FROSJointTrajectorySubscriber>(new FROSJointTrajectorySubscriber(*ROSSubscriberTopicName, robotModel)));
	Handler->AddSubscriber(JointTrajectorySubscribers[0]);
}

// Called every frame
void AROSCommunicationHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Process incoming ROS messages...
	Handler->Process();

	// Check if any subscriber has a pending trajectory to execute...
	for (auto subscriber : JointTrajectorySubscribers) {
		if (subscriber->hasPendingTrajectory_) {
			// Reset boolean flag
			subscriber->hasPendingTrajectory_ = false;
			// Add latent action to world, so trajectory can be properly executed
			int id = FMath::RandRange(1, 1000);
			GetWorld()->GetLatentActionManager().AddNewAction(this, id, new JointTrajectoryLatentAction(
				subscriber->jointTrajectoryMsg_->GetPoints(),
				subscriber->jointTrajectoryMsg_->GetJointNames(),
				subscriber->robot_,
				GetWorld()->DeltaTimeSeconds,
				ROSTrajectoryUpdateFrequency,
				ROSTrajectoryMaxSteps
			));
		}
	}
}

// Called when the game ends
void AROSCommunicationHandler::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Handler->Disconnect();
	UE_LOG(LogTemp, Log, TEXT("[AROSCommunicationHandler::EndPlay()] Websocket server disconnected."), *FString(__FUNCTION__));
	Super::EndPlay(EndPlayReason);
}

