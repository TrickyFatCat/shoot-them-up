// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "AI/EQS/STUEnemyEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "VisualLogger/VisualLogger.h"

void USTUEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
    UBlackboardComponent* Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);

    if (!Blackboard) return;

    UObject* ContextActor = Blackboard->GetValueAsObject(EnemyActorKeyName);
    UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
}
