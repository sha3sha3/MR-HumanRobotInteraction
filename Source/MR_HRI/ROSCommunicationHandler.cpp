// Fill out your copyright notice in the Description page of Project Settings.
#include "ROSCommunicationHandler.h"
#include "FROSFloatSubscriber.h"

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

	// Set up ROS Connection
	Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(*ROSBridgeServerIPAddr, ROSBridgeServerPort));
	Handler->Connect();	
	UE_LOG(LogTemp, Log, TEXT("[AROSCommunicationHandler::BeginPlay()] Websocket server connected."));

	// Add subscriber
	TSharedPtr<FROSFloatSubscriber> Subscriber = MakeShareable<FROSFloatSubscriber>(new FROSFloatSubscriber(*ROSSubscriberTopicName));
	Handler->AddSubscriber(Subscriber);
}

// Called every frame
void AROSCommunicationHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Process incoming ROS messages...
	Handler->Process();
}

// Called when the game ends
void AROSCommunicationHandler::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Handler->Disconnect();
	UE_LOG(LogTemp, Log, TEXT("[AROSCommunicationHandler::EndPlay()] Websocket server disconnected."), *FString(__FUNCTION__));
	Super::EndPlay(EndPlayReason);
	

}

