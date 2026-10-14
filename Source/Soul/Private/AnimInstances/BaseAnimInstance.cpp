// All Rights Reserved.


#include "AnimInstances/BaseAnimInstance.h"
#include "SoulFunctionLibrary.h"

bool UBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
    if (APawn* OwningPawn = TryGetPawnOwner())
    {
        return USoulFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
    }

    return false;
}
