// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a camera boom (pulls in towards the character if there is a collison)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f; // The Camera Followe at this distance dehind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller


	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach camera to end fo boom
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm 
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	/**
	* 
	* Info logTemp
	* бшбнд дюммшу вепег йнмянкэ( ноепюрнпш )напюгеж
	* 
	* UE_LOG(LogTemp, Warning, TEXT("BeginPlay() Called!"));
	* 
	* int myInt{ (int)42.54 };
	* int myInt{ 42 };
	* UE_LOG(LogTemp, Warning, TEXT("int myInt: %d"), myInt);
	* 
	* float myFloat{ 3.14159f };
	* UE_LOG(LogTemp, Warning, TEXT("float myFloat: %f"), myFloat);
	* 
	* double myDouble{ 0.000756 };
	* UE_LOG(LogTemp, Warning, TEXT("double myDouble: %lf"), myDouble);
	* 
	* char MyChar{ 'A' };
	* UE_LOG(LogTemp, Warning, TEXT("char MyChar: %c"), MyChar);
	* 
	* wchar_t wideChar{L'A'};
	* UE_LOG(LogTemp, Warning, TEXT("wchar_t wideChar: %lc"), wideChar);
	* 
	* bool myBool{true};
	* UE_LOG(LogTemp, Warning, TEXT("bool myBool: %d"), myBool);
	* info 1 // UE_LOG(LogTemp, Warning, TEXT("int: %d, float: %f bool: %d"), myInt, myFloat, myBool);
	* info 0 // UE_LOG(LogTemp, Warning, TEXT("int: %d, float: %f bool: %d"), myInt, myFloat, false);
	* 
	* FString myString{ TEXT("My String!!!!") };
	* UE_LOG(LogTemp, Warning, TEXT("FString myString: %s"), *myString);
	* UE_LOG(LogTemp, Warning, TEXT("Name of instance: %s"), *GetName());
	* 
	*/


}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

