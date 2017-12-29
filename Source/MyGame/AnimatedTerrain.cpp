// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimatedTerrain.h"
#include "RuntimeMeshLibrary.h"
#include "ParallelFor.h"


// Sets default values
AAnimatedTerrain::AAnimatedTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RuntimeMesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Generated Mesh"));
    RootComponent = RuntimeMesh;

    // multithreaded physics cooking
    RuntimeMesh->bUseAsyncCooking = true;

}

// Called when the game starts or when spawned
void AAnimatedTerrain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnimatedTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!bGenerated) {
        Generate();
    }

    float AnimationStepX = 5;
    float AnimationStepY = 6;

    AnimationOffsetX += DeltaTime * AnimationStepX;
    AnimationOffsetY += DeltaTime * AnimationStepY;

    // Start position only update
    TArray<FVector>& Positions = *RuntimeMesh->BeginMeshSectionPositionUpdate(0);

    ParallelFor((HalfWidth * 2)*(HalfWidth * 2), [this, &Positions](int32 Index)
    {
        int32 PlaneWidth = HalfWidth * 2;
        int32 XIndex = Index % PlaneWidth;
        int32 YIndex = Index / PlaneWidth;

        float Scale = CellSize / 50.0f;

        float HeightScale = FMath::Cos((XIndex * Scale) + AnimationOffsetX) +
            FMath::Sin((YIndex * Scale) + AnimationOffsetY);

        Positions[Index].Z = HeightScale * Height;
    });

    // Commit position only update
    RuntimeMesh->EndMeshSectionPositionUpdate(0, BoundingBox);

}

void AAnimatedTerrain::OnConstruction(const FTransform & Transform)
{
    Generate();
}

void AAnimatedTerrain::Generate()
{
    TArray<FVector> Positions;
    TArray<FRuntimeMeshVertexNoPosition> VertexData;
    TArray<int32> Triangles;

    // Oversized bounding box so we don't have to update it
    BoundingBox = FBox(FVector(-HalfWidth * CellSize, -HalfWidth * CellSize, -100),
                       FVector(HalfWidth * CellSize, HalfWidth * CellSize, 100));

    float Scale = CellSize / 50.0f;
    // create the vertex array
    for (int32 YIndex = -HalfWidth; YIndex < HalfWidth; YIndex++) 
    {
        for (int32 XIndex = -HalfWidth; XIndex < HalfWidth; XIndex++) 
        {
            Positions.Add(FVector(XIndex * CellSize, YIndex * CellSize, 0));
            VertexData.Add(FRuntimeMeshVertexNoPosition(FVector(0, 0, 0),
                FRuntimeMeshTangent(-1, 0, 0), FVector2D(XIndex * Scale, YIndex * Scale)));
        }
    }

    // create the triangle array
    URuntimeMeshLibrary::CreateGridMeshTriangles(HalfWidth * 2, HalfWidth * 2, true, Triangles);

    RuntimeMesh->CreateMeshSectionDualBuffer(0, Positions, VertexData, Triangles, false, EUpdateFrequency::Frequent);

    bGenerated = true;
}

