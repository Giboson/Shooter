// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"


AWeapon::AWeapon():
	ThrowWeaponTime(0.7f),
	bFalling(false),
	Ammo(0)
	//MagazineCapacity(30),
	//WeaponType(EWeaponType::EWT_SubmachineGun),
	//AmmoType(EAmmoType::EAT_9mm),
	//ReloadMontageSection(FName(TEXT("Reload SMG"))),
	//ClipBoneName(TEXT("smg_clip")),
	//SlideDisplacement(0.f),
	//SlideDisplacementTime(0.2f),
	//bMovingSlide(false),
	//MaxSlideDisplacement(4.f),
	//MaxRecoilRotation(20.f),
	//bAutomatic(true)
{
	PrimaryActorTick.bCanEverTick = true;
}
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Keep the Weapon upright
	if (GetItemState() == EItemState::EIS_Falling && bFalling)
	{
		const FRotator MeshRotation{ 0.f, GetItemMesh()->GetComponentRotation().Yaw, 0.f };
		GetItemMesh()->SetWorldRotation(MeshRotation, false, nullptr, ETeleportType::TeleportPhysics);
	}
	// Update slide on pistol
	//UpdateSlideDisplacement();

}

void AWeapon::ThrowWeapon()
{
	FRotator MeshRotation{ 0.f, GetItemMesh()->GetComponentRotation().Yaw, 0.f };
	GetItemMesh()->SetWorldRotation(MeshRotation, false, nullptr, ETeleportType::TeleportPhysics);

	const FVector MeshForward{ GetItemMesh()->GetForwardVector() };
	const FVector MeshRight{ GetItemMesh()->GetRightVector() };
	// Direction in which we throw the Weapon
	FVector ImpulseDirection = MeshRight.RotateAngleAxis(-20.f, MeshForward);

	float RandomRotation{ 30.f };
	ImpulseDirection = ImpulseDirection.RotateAngleAxis(RandomRotation, FVector(0.f, 0.f, 1.f));
	ImpulseDirection *= 20'000.f;
	GetItemMesh()->AddImpulse(ImpulseDirection);

	bFalling = true;
	GetWorldTimerManager().SetTimer(ThrowWeaponTimer, this, &AWeapon::StopFalling, ThrowWeaponTime);

	//EnableGlowMaterial();

}


void AWeapon::StopFalling()
{
	bFalling = false;
	SetItemState(EItemState::EIS_Pickup);
	//StartPulseTimer();
}


void  AWeapon::DecrementAmmo() 
{
	if (Ammo - 1 <= 0) 
	{
		Ammo = 0;
	}
	else
	{
		--Ammo;
	}
}