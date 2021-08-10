// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Pickups/STUBasePickup.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);


ASTUBasePickup::ASTUBasePickup()
{
    PrimaryActorTick.bCanEverTick = true;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(50.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ASTUBasePickup::BeginPlay()
{
    Super::BeginPlay();
    check(CollisionComponent);
    GenerateRotationYaw();
}

void ASTUBasePickup::Tick(float DeltaTime)
{ 
    Super::Tick(DeltaTime);

    AddActorWorldRotation(FRotator(0.f, RotationYaw, 0.f));
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    APawn* Pawn = Cast<APawn>(OtherActor);

    if (ActivateEffect(Pawn))
    {
        Hide();
    }
}

bool ASTUBasePickup::ActivateEffect(APawn* PlayerPawn)
{
    return false;
}

void ASTUBasePickup::Hide()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    if (!GetRootComponent()) return;

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
    GetRootComponent()->SetVisibility(false, true);
    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);
    bIsActive = false;
}

void ASTUBasePickup::Respawn()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    if (!GetRootComponent()) return;

    GetRootComponent()->SetVisibility(true, true);
    GenerateRotationYaw();
    bIsActive = true;
}

void ASTUBasePickup::GenerateRotationYaw()
{
    const float Direction = FMath::RandBool() ? 1.f : -1.f;
    RotationYaw *= Direction;
}