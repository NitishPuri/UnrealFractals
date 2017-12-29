// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"
#include "FractalActor.generated.h"

UCLASS()
class MYGAME_API AFractalActor : public AActor
{
    GENERATED_BODY()
    
public:    
    // Sets default values for this actor's properties
    AFractalActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void OnConstruction(const FTransform& Transform) override;

    virtual void PostActorCreated() override;

    virtual void PostLoad() override;

public:    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    URuntimeMeshComponent* _mesh;

    void CreateTriangle();

    
};
