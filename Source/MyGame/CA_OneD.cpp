// Fill out your copyright notice in the Description page of Project Settings.

#include "CA_OneD.h"

#define INDEX(x, y) ((int(Size.X)*y) + x)

// Sets default values
ACA_OneD::ACA_OneD()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

    HISMActorD = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISMActorD"));
    HISMActorD->SetupAttachment(RootComponent);

    HISMActor = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISMActor"));
    HISMActor->SetupAttachment(RootComponent);

    //Size = { 3, 3, 3 };

    //Base_StaticMesh = 

    Initial.Append({ 0, 0, 0, 1, 0, 0, 0, 0 });
    Cells.Append(Initial);
    Cells.AddZeroed(Size.X * Size.Y);

    //int arr[] = { 1, 1, 0, 1, 1, 1, 1, 0 };
    //Ruleset.Append(arr, ARRAY_COUNT(arr));
    Ruleset.Append({ 1, 1, 0, 1, 1, 1, 1, 0 });
}

// Called when the game starts or when spawned
void ACA_OneD::BeginPlay()
{
	Super::BeginPlay();
    GenerateMesh();
}

void ACA_OneD::PostActorCreated()
{
    Super::PostActorCreated();
    GenerateMesh();
}

void ACA_OneD::PostLoad()
{
    Super::PostLoad();
    GenerateMesh();
}

// Called every frame
void ACA_OneD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Counter++;
    if (Counter == AnimationDelay) 
    {
        Counter = 0;
        NextGeneration();
        GenerateMesh();

        GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, 
                FString::Printf(TEXT("Tick. %d"), Generation));
        //GEngine->AddOnScreenDebugMessage(2, 5, FColor::Red,
        //    FString::Printf(TEXT("Tick. %d"), Generation));
    }


}

void ACA_OneD::SetupMesh()
{

    HISMActorD->SetRelativeLocation(FVector(0, 0, 0));
    HISMActorD->SetStaticMesh(Base_StaticMesh);
    //HISMActor->SetMaterial(0, Base_Material);

    HISMActor->SetRelativeLocation(FVector(0, 0, 0));
    HISMActor->SetStaticMesh(Base_StaticMesh);
    HISMActor->SetMaterial(0, Base_Material);

}

void ACA_OneD::NextGeneration()
{
    //TArray<bool> nextGen({ 0 }, Size.X);

    int rows = Size.Y;
    int cols = Size.X;
    for (int i = 0; i < cols; i++)
    {
        int left   = Cells[INDEX(((i + cols - 1) % cols), (Generation%rows))];
        int middle = Cells[INDEX(i, (Generation%rows))];
        int right  = Cells[INDEX((i+1), (Generation%rows))];

        Cells[INDEX(i, ((Generation + 1) % rows))] = rules(left, middle, right);
    }

    Generation++;
}

void ACA_OneD::GenerateMesh()
{

    // Update the instances instead.??
    HISMActor->ClearInstances();
    HISMActorD->ClearInstances();
    FTransform Params;

    int rows = Size.Y;
    int cols = Size.X;
    int genOffset = Generation%rows;

    for(UTextRenderComponent* var : DebugText)
    {
        var->UnregisterComponent();
        var->DestroyComponent();
    }
    DebugText.Empty();

    for (int32 i = 0; i < rows; ++i)
    {
        int y = i - genOffset;
        if (y <= 0) y += rows;

        //UTextRenderComponent* Text = NewObject<UTextRenderComponent>(this);
        //Text->SetRelativeLocation(FVector(-100, y * Offset, 100.f));
        //Text->SetRelativeRotation(FRotator(0, 90, 0));
        //Text->SetTextRenderColor(FColor::Red);
        //Text->SetText(FString::Printf(TEXT("(%d , %d)"), i, y));
        //Text->SetXScale(1.f);
        //Text->SetYScale(1.f);
        //Text->SetWorldSize(75);

        //DebugText.Push(Text);

        //Text->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

        for (int32 j = 0; j < cols; ++j)
        {
            if (Generation < 3) {
                UTextRenderComponent* Text = NewObject<UTextRenderComponent>(this);
                Text->SetRelativeLocation(FVector(j * Offset - 100, y * Offset, 100.f));
                Text->SetRelativeRotation(FRotator(90, 90, 0));
                Text->SetTextRenderColor(FColor::Red);
                Text->SetText(FString::Printf(TEXT("(%d , %d, %d)"), j, i, y));
                Text->SetXScale(1.f);
                Text->SetYScale(1.f);
                Text->SetWorldSize(40);

                DebugText.Push(Text);

                Text->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
            }

            Params.SetTranslation(FVector(j * Offset, y * Offset, 0));
            //Params.SetTranslation(FVector(j * Offset, i * Offset, 0));
            HISMActorD->AddInstance(Params);

            //if (Cells[INDEX(i, j)])
            if (Cells[INDEX(j, i)])
            //if (i == Generation)
            {
                HISMActor->AddInstance(Params);
            }
        }
    }
}

int ACA_OneD::rules(int a, int b, int c)
{
    if      (a == 1 && b == 1 && c == 1) return Ruleset[0];
    else if (a == 1 && b == 1 && c == 0) return Ruleset[1];
    else if (a == 1 && b == 0 && c == 1) return Ruleset[2];
    else if (a == 1 && b == 0 && c == 0) return Ruleset[3];
    else if (a == 0 && b == 1 && c == 1) return Ruleset[4];
    else if (a == 0 && b == 1 && c == 0) return Ruleset[5];
    else if (a == 0 && b == 0 && c == 1) return Ruleset[6];
    else if (a == 0 && b == 0 && c == 0) return Ruleset[7];
    return true;
}
 


#if WITH_EDITOR
void ACA_OneD::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName MemberPropertyChanged = (PropertyChangedEvent.MemberProperty ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None);

    if ((MemberPropertyChanged == GET_MEMBER_NAME_CHECKED(ACA_OneD, Size)))
    {
        if (Size.X != Initial.Num())
        {
            Initial.Empty();
            for (int i = 0; i < Size.X; i++)
            {
                Initial.Add(FMath::Rand() % 2);
            }

        }
        Cells.Empty();
        Cells.Append(Initial);
        Cells.AddZeroed(Size.X * Size.Y);

        GenerateMesh();
    }
    else if ((MemberPropertyChanged == GET_MEMBER_NAME_CHECKED(ACA_OneD, Offset)))
    {
        GenerateMesh();
    }
    else if ((MemberPropertyChanged == GET_MEMBER_NAME_CHECKED(ACA_OneD, Base_StaticMesh)) ||
             (MemberPropertyChanged == GET_MEMBER_NAME_CHECKED(ACA_OneD, Base_Material)))
    {
        SetupMesh();
    }
    //else if ((MemberPropertyChanged == GET_MEMBER_NAME_CHECKED(AHeightFieldAnimatedActor, Material)))
    //{
    //    MeshComponent->SetMaterial(0, Material);
    //}
}
#endif // WITH_EDITOR

