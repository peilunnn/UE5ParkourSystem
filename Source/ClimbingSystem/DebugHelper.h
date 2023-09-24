#pragma once

namespace Debug
{
    static void Print(const FString& Msg, const FColor& color = FColor::MakeRandomColor(), int32 InKey = -1)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(InKey, 6.f, color, Msg);
        }

        UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
    }
}