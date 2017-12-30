// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuntimeMeshActorBase.h"
#include "SimpleCubeActor.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API ASimpleCubeActor : public ARuntimeMeshActorBase
{
	GENERATED_BODY()

public:
    ASimpleCubeActor();
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Parameters")
    FVector Size = FVector(100.0f, 100.0f, 100.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Parameters")
    UMaterialInterface* Material;

    virtual void PostLoad() override;
    virtual void PostActorCreated() override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR

private:
    void GenerateMesh();

    void GenerateCube(TArray<FRuntimeMeshVertexSimple>& InVertices, 
                    TArray<int32>& InTriangles, FVector InSize);

    void BuildQuad(TArray<FRuntimeMeshVertexSimple>& InVertices, TArray<int32>& InTriangles, 
                   FVector BottomLeft, FVector BottomRight, FVector TopRight, FVector TopLeft,
                   int32& VertexOffset, int32& TriangleOffset, FPackedNormal Normal, FPackedNormal Tangent);

    // Mesh buffers
    void SetupMeshBuffers();
    bool bHaveBuffersBeenInitialized = false;
    TArray<FRuntimeMeshVertexSimple> Vertices;
    TArray<int32> Triangles;
};
