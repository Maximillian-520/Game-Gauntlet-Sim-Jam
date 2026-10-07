#include "BaseBuilding.h"

ABaseBuilding::ABaseBuilding() {}

// ==================================================
//           Upgrade
// ==================================================

void ABaseBuilding::Upgrade()
{
	Level = FMath::Clamp(Level + 1, 1, MaxLevel);
}

// ==================================================
//           Upgrade
// ==================================================

int32 ABaseBuilding::GetDemolishValue() const
{
	int32 Value = BuildCost;
	
	for (int Index = 0; Index < Level - 1; Index++)
	{
		if (Index >= UpgradeCosts.Num()) break;
		Value += UpgradeCosts[Index];
	}

	return Value * DemolishValueMargin;
}