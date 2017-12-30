// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshActorBase.h"
#include "AnimatedTerrain.generated.h"

UCLASS()
class MYGAME_API AAnimatedTerrain : public ARuntimeMeshActorBase
{
	GENERATED_BODY()
	
public:	

    bool bGenerated;
    FBox BoundingBox;


	// Sets default values for this actor's properties
	AAnimatedTerrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void OnConstruction(const FTransform& Transform) override;

    void Generate();

    float AnimationOffsetX = 0.0f;
    float AnimationOffsetY = 0.0f;

    int32 HalfWidth = 40;

    float CellSize = 5;
    float Height = 20;

};
