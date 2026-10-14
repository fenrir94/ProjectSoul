// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnTargetableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnTargetableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOUL_API IPawnTargetableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FVector GetTargetLocation() const = 0;
	virtual bool IsTargetable() const = 0;
};
