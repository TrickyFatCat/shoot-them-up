// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "AI/EQS/EnvQueryTest_PickupIsActive.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/STUBasePickup.h"

UEnvQueryTest_PickupIsActive::UEnvQueryTest_PickupIsActive(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickupIsActive::RunTest(FEnvQueryInstance& QueryInstance) const
{
    UObject* DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);
    bool WantsBeTaken = BoolValue.GetValue();

    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        ASTUBasePickup* PickupActor = Cast<ASTUBasePickup>(ItemActor);

        if (!PickupActor) continue;

        const bool bIsActive = PickupActor->GetIsActive();
        It.SetScore(TestPurpose, FilterType, bIsActive, WantsBeTaken);
    }
}
