/**
 * @file toy_scope.h
 * @brief @@???@@
 *
 */

#ifndef TOY_SCOPE_H_
#define TOY_SCOPE_H_

#include <stdbool.h>

#include "toy_literal.h"
#include "toy_literal_array.h"
#include "toy_literal_dictionary.h"

/**
 * @typedef Toy_Scope
 * @brief @@???@@
 *
 */
typedef struct Toy_Scope {
    Toy_LiteralDictionary variables; /**< only allow identifiers as the keys */
    Toy_LiteralDictionary types;     /**< the types, indexed by identifiers */
    struct Toy_Scope *ancestor;      /**< @@???@@ */
    int references;                  /**< how many scopes point here */
} Toy_Scope;

/**
 * @fn Toy_Scope* Toy_pushScope(Toy_Scope *scope)
 * @brief Creates a new Toy_scope with scope as it's ancestor, and returns it.
 *
 * @param scope
 * @return
 */
TOY_API Toy_Scope* Toy_pushScope(Toy_Scope *scope);

/**
 * @fn Toy_Scope* Toy_popScope(Toy_Scope *scope)
 * @brief Frees the given scope, and returns it's ancestor.
 *
 * @param scope
 * @return
 */
TOY_API Toy_Scope* Toy_popScope(Toy_Scope *scope);

/**
 * @fn Toy_Scope* Toy_copyScope(Toy_Scope *original)
 * @brief Copies an existing scope, and returns the copy.
 *
 * @param original
 * @return
 */
TOY_API Toy_Scope* Toy_copyScope(Toy_Scope *original);

//returns false if error
/**
 * @fn bool Toy_declareScopeVariable(Toy_Scope *scope, Toy_Literal key, Toy_Literal type)
 * @brief Declares a new variable key within scope, giving it the type of type.
 *        This function returns true on success, otherwise it returns failure (such as if the given key already exists).
 *
 * @param scope
 * @param key
 * @param type
 * @return
 */
TOY_API bool Toy_declareScopeVariable(Toy_Scope *scope, Toy_Literal key, Toy_Literal type);

/**
 * @fn bool Toy_isDelcaredScopeVariable(Toy_Scope *scope, Toy_Literal key)
 * @brief Checks to see if a given variable with the name key has been previously declared.
 *
 * @param scope
 * @param key
 * @return
 */
TOY_API bool Toy_isDelcaredScopeVariable(Toy_Scope *scope, Toy_Literal key);

//return false if undefined
/**
 * @fn bool Toy_setScopeVariable(Toy_Scope *scope, Toy_Literal key, Toy_Literal value, bool constCheck)
 * @brief Sets an existing variable named key to the value of value. This function fails if constCheck is true and the given key's type has the constaant flag set. It also fails if the given key doesn't exist.
 *        Returns true on success, otherwise it returns false.
 *
 * @param scope
 * @param key
 * @param value
 * @param constCheck
 * @return
 */
TOY_API bool Toy_setScopeVariable(Toy_Scope *scope, Toy_Literal key, Toy_Literal value, bool constCheck);

/**
 * @fn bool Toy_getScopeVariable(Toy_Scope *scope, Toy_Literal key, Toy_Literal *value)
 * @brief Sets the literal pointed to by value to equal the variable named key.
 *        Returns true on success, otherwise it returns false.
 *
 * @param scope
 * @param key
 * @param value
 * @return
 */
TOY_API bool Toy_getScopeVariable(Toy_Scope *scope, Toy_Literal key, Toy_Literal *value);

/**
 * @fn Toy_Literal Toy_getScopeType(Toy_Scope *scope, Toy_Literal key)
 * @brief Returns a new Toy_Literal representing the type of the variable named key.
 *
 * @param scope
 * @param key
 * @return
 */
TOY_API Toy_Literal Toy_getScopeType(Toy_Scope *scope, Toy_Literal key);

#endif /* TOY_SCOPE_H_ */
