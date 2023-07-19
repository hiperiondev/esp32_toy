/**
 * @file toy_builtin.h
 * @brief @@???@@
 *
 */

#ifndef TOY_BUILTIN_H_
#define TOY_BUILTIN_H_

#include "toy_interpreter.h"

/**
 * @fn int Toy_private_index(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments)
 * @brief The _index function is a historical oddity - it's used whenever a compound is indexed
 *
 * @param interpreter
 * @param arguments
 * @return
 */
int Toy_private_index(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);

//globally available native functions
/**
 * @fn int Toy_private_set(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments)
 * @brief @@???@@
 *
 * @param interpreter
 * @param arguments
 * @return
 */
int Toy_private_set(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);

/**
 * @fn int Toy_private_get(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments)
 * @brief @@???@@
 *
 * @param interpreter
 * @param arguments
 * @return
 */
int Toy_private_get(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);

/**
 * @fn int Toy_private_push(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments)
 * @brief @@???@@
 *
 * @param interpreter
 * @param arguments
 * @return
 */
int Toy_private_push(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);

/**
 * @fn int Toy_private_pop(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments)
 * @brief @@???@@
 *
 * @param interpreter
 * @param arguments
 * @return
 */
int Toy_private_pop(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);

/**
 * @fn int Toy_private_length(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments)
 * @brief @@???@@
 *
 * @param interpreter
 * @param arguments
 * @return
 */
int Toy_private_length(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);

/**
 * @fn int Toy_private_clear(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments)
 * @brief @@???@@
 *
 * @param interpreter
 * @param arguments
 * @return
 */
int Toy_private_clear(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);

#endif /* TOY_BUILTIN_H_ */
