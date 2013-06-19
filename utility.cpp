#include "utility.h"

ScreenDirection calculateDirection(ScreenDirection currDir, Direction elemDir)
{
	bool LE = (currDir == East && elemDir == Left);
	bool SN = (currDir == North && elemDir == Straight);
	bool RW = (currDir == West && elemDir == Right);

	bool SE = (currDir == East && elemDir == Straight);
	bool LS = (currDir == South && elemDir == Left);
	bool RN = (currDir == North && elemDir == Right);

	bool SS = (currDir == South && elemDir == Straight);
	bool LW = (currDir == West && elemDir == Left);
	bool RE = (currDir == East && elemDir == Right);

	bool SW = (currDir == West && elemDir == Straight);
	bool LN = (currDir == North && elemDir == Left);
	bool RS = (currDir == South && elemDir == Right);

	// North
	if (LE || SN || RW)
		return ScreenDirection::North;

	// South
	else if (SS || LW || RE)
		return ScreenDirection::South;

	// East
	else if (SE || LS || RN)
		return ScreenDirection::East;

	// West
	else if (SW || LN || RS)
		return ScreenDirection::West;
}