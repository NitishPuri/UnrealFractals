// Fill out your copyright notice in the Description page of Project Settings.

#include "RuntimeMeshActorBase.h"


// Sets default values
ARuntimeMeshActorBase::ARuntimeMeshActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootNode = CreateDefaultSubobject<USceneComponent>("Root");
    RootComponent = RootNode;

    RuntimeMesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Generated Mesh"));
    RuntimeMesh->SetupAttachment(RootNode);

}

// Called when the game starts or when spawned
void ARuntimeMeshActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARuntimeMeshActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

