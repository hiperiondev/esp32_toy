#ifndef TOY_LIB_RANDOM_H_
#define TOY_LIB_RANDOM_H_

#include "toy_interpreter.h"

int Toy_hookRandom(Toy_Interpreter *interpreter, Toy_Literal identifier, Toy_Literal alias);

#define TOY_OPAQUE_TAG_RANDOM 200

#endif /* TOY_LIB_RANDOM_H_ */
