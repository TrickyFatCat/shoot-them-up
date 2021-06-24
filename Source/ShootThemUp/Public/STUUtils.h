#pragma once

class STUUtils
{
public:
    template <typename T>
    static T* GetSTUPlayerComponent(AActor* PlayerPawn)
    {
        if (!PlayerPawn) return nullptr;

        return Cast<T>(PlayerPawn->GetComponentByClass(T::StaticClass()));
    }
};
