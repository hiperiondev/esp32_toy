#ifndef TOY_SCOPE_H_
#define TOY_SCOPE_H_

#include <stdbool.h>

#include "toy_literal.h"
#include "toy_literal_array.h"
#include "toy_literal_dictionary.h"

/**
 * @typedef Toy_Scope
 * @brief
 *
 */
typedef struct Toy_Scope {
    Toy_LiteralDictionary variables; /**< */ //only allow identifiers as the keys
    Toy_LiteralDictionary types;     /**< */ //the types, indexed by identifiers
    struct Toy_Scope *ancestor;      /**< */
    int references;                  /**< */ //how many scopes point here
} Toy_Scope;

/**
 * @fn Toy_Scope* Toy_pushScope(Toy_Scope *scope)
 * @brief
 *
 * @param scope
 * @return
 */
TOY_API Toy_Scope* Toy_pushScope(Toy_Scope *scope);

/**
 * @fn Toy_Scope* Toy_popScope(Toy_Scope *scope)
 * @brief
 *
 * @param scope
 * @return
 */
TOY_API Toy_Scope* Toy_popScope(Toy_Scope *scope);

/**
 * @fn Toy_Scope* Toy_copyScope(Toy_Scope *original)
 * @brief
 *
 * @param original
 * @return
 */
TOY_API Toy_Scope* Toy_copyScope(Toy_Scope *original);

//returns false if error
/**
 * @fn bool Toy_declareScopeVariable(Toy_Scope *scope, Toy_Literal key, Toy_Literal type)
 * @brief
 *
 * @param scope
 * @param key
 * @param type
 * @return
 */
TOY_API bool Toy_declareScopeVariable(Toy_Scope *scope, Toy_Literal key, Toy_Literal type);

/**
 * @fn bool Toy_isDelcaredScopeVariable(Toy_Scope *scope, Toy_Literal key)
 * @brief
 *
 * @param scope
 * @param key
 * @return
 */
TOY_API bool Toy_isDelcaredScopeVariable(Toy_Scope *scope, Toy_Literal key);

//return false if undefined
/**
 * @fn bool Toy_setScopeVariable(Toy_Scope *scope, Toy_Literal key, Toy_Literal value, bool constCheck)
 * @brief
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
 * @brief
 *
 * @param scope
 * @param key
 * @param value
 * @return
 */
TOY_API bool Toy_getScopeVariable(Toy_Scope *scope, Toy_Literal key, Toy_Literal *value);

/**
 * @fn Toy_Literal Toy_getScopeType(Toy_Scope *scope, Toy_Literal key)
 * @brief
 *
 * @param scope
 * @param key
 * @return
 */
TOY_API Toy_Literal Toy_getScopeType(Toy_Scope *scope, Toy_Literal key);

#endif /* TOY_SCOPE_H_ */
