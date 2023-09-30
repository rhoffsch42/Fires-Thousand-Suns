
#include "FuncLib.h"

bool	UFuncLib::CheckObject(UObject* obj, FString ErrorMsg) {
	if (!obj) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, ErrorMsg);
		return false;
	}
	return true;
}