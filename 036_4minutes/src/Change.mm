#include "Change.h"

template<>
const ofColor& Change<ofColor> :: Update(){
	current.r = current.r + (target.r - current.r) * resist;
	current.g = current.g + (target.g - current.g) * resist;
	current.b = current.b + (target.b - current.b) * resist;
	current.a = current.a + (target.a - current.a) * resist;

	return Current();
}
