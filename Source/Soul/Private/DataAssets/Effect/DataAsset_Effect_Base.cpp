// All Rights Reserved.


#include "DataAssets/Effect/DataAsset_Effect_Base.h"

bool UDataAsset_Effect_Base::FindEffectByTag(FGameplayTag InTag, FHitEffectEntry& OutEffect) const
{
	if (!InTag.IsValid()) return false;

	for (const FHitEffectEntry& Entry : Effects)
	{
		if (InTag.MatchesTag(Entry.EffectTag))
		{
			OutEffect = Entry;
			return true;
		}
	}

	return false;
}
