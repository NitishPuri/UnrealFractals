// Fill out your copyright notice in the Description page of Project Settings.

#include "CA_OneD.h"

#define INDEX(x, y) ((Columns*y) + x)

// Sets default values
ACA_OneD::ACA_OneD()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

    HISMActor = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISMActor"));
    HISMActor->SetupAttachment(RootComponent);

    Initial.Append({ 0, 0, 0, 1, 0, 0, 0, 0 });
    Cells.Append(Initial);
    Cells.SetNumZeroed(Columns * Rows);

    Ruleset.Append({ 1, 1, 0, 1, 1, 1, 1, 0 });
}

// Called when the game starts or when spawned
void ACA_OneD::BeginPlay()
{
	Super::BeginPlay();
    InitializeArrays();
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
    //GenerateMesh();
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
    }


}

void ACA_OneD::SetupMesh()
{

    HISMActor->SetRelativeLocation(FVector(0, 0, 0));
    HISMActor->SetStaticMesh(Base_StaticMesh);
    HISMActor->SetMaterial(0, Base_Material);

}

void ACA_OneD::NextGeneration()
{
    for (int i = 0; i < Columns; i++)
    {
        int left   = Cells[INDEX(((i + Columns - 1) % Columns), (Generation%Rows))];
        int middle = Cells[INDEX(i, (Generation%Rows))];
        int right  = Cells[INDEX((i+1)%Columns, (Generation%Rows))];

        Cells[INDEX(i, ((Generation + 1) % Rows))] = rules(left, middle, right);
    }

    Generation++;
}

void ACA_OneD::GenerateMesh()
{

    // Update the instances instead.??
    HISMActor->ClearInstances();
    FTransform Params;

    int genOffset = Generation%Rows;

    //for(UTextRenderComponent* var : DebugText)
    //{
    //    var->UnregisterComponent();
    //    var->DestroyComponent();
    //}
    //DebugText.Empty();

    for (int32 i = 0; i < Rows; ++i)
    {
        int y = i - genOffset;
        if (y <= 0) y += Rows;

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

        for (int32 j = 0; j < Columns; ++j)
        {
            //if (Generation < 3) {
            //    UTextRenderComponent* Text = NewObject<UTextRenderComponent>(this);
            //    Text->SetRelativeLocation(FVector(j * Offset - 100, y * Offset, 100.f));
            //    Text->SetRelativeRotation(FRotator(90, 90, 0));
            //    Text->SetTextRenderColor(FColor::Red);
            //    Text->SetText(FString::Printf(TEXT("(%d , %d, %d)"), j, i, y));
            //    Text->SetXScale(1.f);
            //    Text->SetYScale(1.f);
            //    Text->SetWorldSize(40);

            //    DebugText.Push(Text);

            //    Text->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
            //}

            //if (Cells[INDEX(i, j)])
            if (Cells[INDEX(j, i)])
            {
                Params.SetTranslation(FVector(j * Offset, y * Offset, 0));
                HISMActor->AddInstance(Params);
            }
        }
    }
}

int ACA_OneD::rules(int a, int b, int c)
{
    return Ruleset[a * 4 + b * 2 + c];
    //return Ruleset[a<<2 | b<<1 | c];
}
 
void ACA_OneD::InitializeArrays()
{
    Cells.Empty();
    Cells.Append(Initial);
    Cells.SetNum(Rows * Columns);
}

#if WITH_EDITOR
void ACA_OneD::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName MemberPropertyChanged = (PropertyChangedEvent.MemberProperty ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None);

    if ((MemberPropertyChanged == GET_MEMBER_NAME_CHECKED(ACA_OneD, Rows)) || 
        (MemberPropertyChanged == GET_MEMBER_NAME_CHECKED(ACA_OneD, Columns)) ||
        (MemberPropertyChanged == GET_MEMBER_NAME_CHECKED(ACA_OneD, Initial)))
    {
        InitializeArrays();
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
}
#endif // WITH_EDITOR

