// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry,All,All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);

}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	InitialiLocation = GetActorLocation();
	
	
	  //PrintTransform();
	 //PrintTypes();
	//PrintStringTypes();

	SetColor(GeometryDate.Color);
	GetWorldTimerManager().SetTimer(TimerHandle,this, &ABaseGeometryActor::OnTimerFired, GeometryDate.TimerRate, true);
	
		
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HendleMovement();
	
}

void ABaseGeometryActor::HendleMovement() 
{
	switch (GeometryDate.MoveType)
	{
	case EMovementType::Sin: 
	{
		//[formula] z = z0 + amplitude * sin(freq * t); 
		FVector CurrentLocation = GetActorLocation();
		float Time = GetWorld()->GetTimeSeconds();
		CurrentLocation.Z = InitialiLocation.Z + GeometryDate.Amplitude * FMath::Sin(GeometryDate.Frequncy * Time);

		SetActorLocation(CurrentLocation);
	}
	break;

	case EMovementType::Static: break;
	default: break;
	}
}


void ABaseGeometryActor::PrintTypes()
{
	// UE_LOG	<--[F12]+[Corsor] MAKROS:
	// TEXT		<--[F12]+[Corsor] MAKROS:
	// UE_LOG(LogTemp, Display, TEXT("Hello World!"));
	// UE_LOG(LogTemp, Warning, TEXT("Hello World!"));
	// UE_LOG(LogTemp, Error, TEXT("Hello World!"));
	// UE_LOG(LogBaseGeometry, Display, TEXT("info"));

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"),*GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Weapons num:  %d, Kills num: %i"), WeaponsNum, KillsNum);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Health %f "), Health);
	// UE_LOG(LogTemp, Display, TEXT("Health %.2f "), Health);
	UE_LOG(LogBaseGeometry, Warning, TEXT("IsDead %d "), IsDead);
	UE_LOG(LogBaseGeometry, Warning, TEXT("HasWeapon %d "), static_cast<int>(HasWeapon));
}
void ABaseGeometryActor::PrintStringTypes()
{
	FString Name = "ANDREW.Y";
	UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name);

	//int WeaponsNum = 4;
	//float Health = 38.00000;
	//bool IsDead = false;

	FString WeaponsNumStr = "Weapons Num = " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is Dead = " + FString(IsDead ? "true" : "false");

	FString Start = FString::Printf(TEXT("\n == All Start == \n %s \n %s \n %s \n"), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Start);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Start, true, FVector2D(1.5f, 1.5f));
}
void ABaseGeometryActor::PrintTransform()
{
	FTransform Transform = GetActorTransform();
	FVector  Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector  Scale = Transform.GetScale3D();

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Transform %s"), *Transform.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Location %s"), *Location.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Rotation %s"), *Rotation.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Scale %s"), *Scale.ToString());

	UE_LOG(LogBaseGeometry, Error, TEXT("Human Transform %s"), *Transform.ToHumanReadableString());
}
void ABaseGeometryActor::SetColor(const FLinearColor& Color) 
{
	UMaterialInstanceDynamic* DnyMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DnyMaterial)
	{
		DnyMaterial->SetVectorParameterValue("Color",Color);
	}

}
void ABaseGeometryActor::OnTimerFired()
{
	if (++TimerConst <= MaxTimerConst)
	{
	const FLinearColor NewColor = FLinearColor::MakeRandomColor();
	UE_LOG(LogBaseGeometry, Display, TEXT("TimerConst : %i Color to Set up: %s"), TimerConst, *NewColor.ToString());
	SetColor(NewColor);

	}
	else
	{
		UE_LOG(LogBaseGeometry, Warning, TEXT("Timer has been stopped!"));
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}