#ifndef TOY_AST_NODE_H_
#define TOY_AST_NODE_H_

#include "toy_common.h"
#include "toy_literal.h"
#include "toy_opcodes.h"
#include "toy_token_types.h"

//nodes are the intermediaries between parsers and compilers
/**
 * @typedef Toy_ASTNode
 * @brief
 *
 */
typedef union Toy_private_node Toy_ASTNode;

/**
 * @enum Toy_ASTNodeType
 * @brief
 *
 */
typedef enum Toy_ASTNodeType {
    TOY_AST_NODE_ERROR,             //
    TOY_AST_NODE_LITERAL,           //a simple value
    TOY_AST_NODE_UNARY,             //one child + opcode
    TOY_AST_NODE_BINARY,            //two children, left and right + opcode
    TOY_AST_NODE_TERNARY,           //three children, condition, then path & else path
    TOY_AST_NODE_GROUPING,          //one child
    TOY_AST_NODE_BLOCK,             //contains a sub-node array
    TOY_AST_NODE_COMPOUND,          //contains a sub-node array
    TOY_AST_NODE_PAIR,              //contains a left and right
    TOY_AST_NODE_INDEX,             //index a variable
    TOY_AST_NODE_VAR_DECL,          //contains identifier literal, typenode, expression definition
    TOY_AST_NODE_FN_DECL,           //contains identifier literal, arguments node, returns node, block node
    TOY_AST_NODE_FN_COLLECTION,     //parts of a function
    TOY_AST_NODE_FN_CALL,           //call a function
    TOY_AST_NODE_FN_RETURN,         //for control flow
    TOY_AST_NODE_IF,                //for control flow
    TOY_AST_NODE_WHILE,             //for control flow
    TOY_AST_NODE_FOR,               //for control flow
    TOY_AST_NODE_BREAK,             //for control flow
    TOY_AST_NODE_CONTINUE,          //for control flow
    TOY_AST_NODE_PREFIX_INCREMENT,  //increment a variable
    TOY_AST_NODE_POSTFIX_INCREMENT, //increment a variable
    TOY_AST_NODE_PREFIX_DECREMENT,  //decrement a variable
    TOY_AST_NODE_POSTFIX_DECREMENT, //decrement a variable
    TOY_AST_NODE_IMPORT,            //import a library
    TOY_AST_NODE_PASS,              //for doing nothing
} Toy_ASTNodeType;

//literals
/**
 * @fn void Toy_emitASTNodeLiteral(Toy_ASTNode **nodeHandle, Toy_Literal literal)
 * @brief
 *
 * @param nodeHandle
 * @param literal
 */
void Toy_emitASTNodeLiteral(Toy_ASTNode **nodeHandle, Toy_Literal literal);

/**
 * @struct Toy_NodeLiteral
 * @brief
 *
 */
typedef struct Toy_NodeLiteral {
    Toy_ASTNodeType type;
    Toy_Literal literal;
} Toy_NodeLiteral;

//unary operator
/**
 * @fn void Toy_emitASTNodeUnary(Toy_ASTNode **nodeHandle, Toy_Opcode opcode, Toy_ASTNode *child)
 * @brief
 *
 * @param nodeHandle
 * @param opcode
 * @param child
 */
void Toy_emitASTNodeUnary(Toy_ASTNode **nodeHandle, Toy_Opcode opcode, Toy_ASTNode *child);

typedef struct Toy_NodeUnary {
    Toy_ASTNodeType type;
    Toy_Opcode opcode;
    Toy_ASTNode *child;
} Toy_NodeUnary;

//binary operator
/**
 * @fn void Toy_emitASTNodeBinary(Toy_ASTNode **nodeHandle, Toy_ASTNode *rhs, Toy_Opcode opcode)
 * @brief
 *
 * @param nodeHandle
 * @param rhs
 * @param opcode
 */
void Toy_emitASTNodeBinary(Toy_ASTNode **nodeHandle, Toy_ASTNode *rhs, Toy_Opcode opcode); //handled node becomes lhs

/**
 * @struct Toy_NodeBinary
 * @brief
 *
 */
typedef struct Toy_NodeBinary {
    Toy_ASTNodeType type;
    Toy_Opcode opcode;
    Toy_ASTNode *left;
    Toy_ASTNode *right;
} Toy_NodeBinary;

//ternary operator
/**
 * @fn void Toy_emitASTNodeTernary(Toy_ASTNode **nodeHandle, Toy_ASTNode *condition, Toy_ASTNode *thenPath, Toy_ASTNode *elsePath)
 * @brief
 *
 * @param nodeHandle
 * @param condition
 * @param thenPath
 * @param elsePath
 */
void Toy_emitASTNodeTernary(Toy_ASTNode **nodeHandle, Toy_ASTNode *condition, Toy_ASTNode *thenPath, Toy_ASTNode *elsePath);

/**
 * @typedef Toy_NodeTernary
 * @brief
 *
 */
typedef struct Toy_NodeTernary {
    Toy_ASTNodeType type;
    Toy_ASTNode *condition;
    Toy_ASTNode *thenPath;
    Toy_ASTNode *elsePath;
} Toy_NodeTernary;

//grouping of other AST nodes
/**
 * @fn void Toy_emitASTNodeGrouping(Toy_ASTNode **nodeHandle)
 * @brief
 *
 * @param nodeHandle
 */
void Toy_emitASTNodeGrouping(Toy_ASTNode **nodeHandle);

/**
 * @typedef Toy_NodeGrouping
 * @brief
 *
 */
typedef struct Toy_NodeGrouping {
    Toy_ASTNodeType type;
    Toy_ASTNode *child;
} Toy_NodeGrouping;

//block of statement nodes
/**
 * @fn void Toy_emitASTNodeBlock(Toy_ASTNode **nodeHandle)
 * @brief
 *
 * @param nodeHandle
 */
void Toy_emitASTNodeBlock(Toy_ASTNode **nodeHandle);

typedef struct Toy_NodeBlock {
    Toy_ASTNodeType type;
    Toy_ASTNode *nodes;
    int capacity;
    int count;
} Toy_NodeBlock;

//compound literals (array, dictionary)
/**
 * @fn void Toy_emitASTNodeCompound(Toy_ASTNode **nodeHandle, Toy_LiteralType literalType)
 * @brief
 *
 * @param nodeHandle
 * @param literalType
 */
void Toy_emitASTNodeCompound(Toy_ASTNode **nodeHandle, Toy_LiteralType literalType);

/**
 * @typedef Toy_NodeCompound
 * @brief
 *
 */
typedef struct Toy_NodeCompound {
    Toy_ASTNodeType type;
    Toy_LiteralType literalType;
    Toy_ASTNode *nodes;
    int capacity;
    int count;
} Toy_NodeCompound;

/**
 * @fn void Toy_setASTNodePair(Toy_ASTNode *node, Toy_ASTNode *left, Toy_ASTNode *right)
 * @brief
 *
 * @param node
 * @param left
 * @param right
 */
void Toy_setASTNodePair(Toy_ASTNode *node, Toy_ASTNode *left, Toy_ASTNode *right); //NOTE: this is a set function, not an emit function

/**
 * @typedef Toy_NodePair
 * @brief
 *
 */
typedef struct Toy_NodePair {
    Toy_ASTNodeType type;
    Toy_ASTNode *left;
    Toy_ASTNode *right;
} Toy_NodePair;

/**
 * @fn void Toy_emitASTNodeIndex(Toy_ASTNode **nodeHandle, Toy_ASTNode *first, Toy_ASTNode *second, Toy_ASTNode *third)
 * @brief
 *
 * @param nodeHandle
 * @param first
 * @param second
 * @param third
 */
void Toy_emitASTNodeIndex(Toy_ASTNode **nodeHandle, Toy_ASTNode *first, Toy_ASTNode *second, Toy_ASTNode *third);

typedef struct Toy_NodeIndex {
    Toy_ASTNodeType type;
    Toy_ASTNode *first;
    Toy_ASTNode *second;
    Toy_ASTNode *third;
} Toy_NodeIndex;

//variable declaration
/**
 * @fn void Toy_emitASTNodeVarDecl(Toy_ASTNode **nodeHandle, Toy_Literal identifier, Toy_Literal type, Toy_ASTNode *expression)
 * @brief
 *
 * @param nodeHandle
 * @param identifier
 * @param type
 * @param expression
 */
void Toy_emitASTNodeVarDecl(Toy_ASTNode **nodeHandle, Toy_Literal identifier, Toy_Literal type, Toy_ASTNode *expression);

/**
 * @typedef Toy_NodeVarDecl
 * @brief
 *
 */
typedef struct Toy_NodeVarDecl {
    Toy_ASTNodeType type;
    Toy_Literal identifier;
    Toy_Literal typeLiteral;
    Toy_ASTNode *expression;
} Toy_NodeVarDecl;

//NOTE: fnCollection is used by fnDecl, fnCall and fnReturn
/**
 * @fn void Toy_emitASTNodeFnCollection(Toy_ASTNode **nodeHandle)
 * @brief
 *
 * @param nodeHandle
 */
void Toy_emitASTNodeFnCollection(Toy_ASTNode **nodeHandle);

/**
 * @struct Toy_NodeFnCollection
 * @brief
 *
 */
typedef struct Toy_NodeFnCollection {
    Toy_ASTNodeType type;
    Toy_ASTNode *nodes;
    int capacity;
    int count;
} Toy_NodeFnCollection;

//function declaration
/**
 * @fn void Toy_emitASTNodeFnDecl(Toy_ASTNode **nodeHandle, Toy_Literal identifier, Toy_ASTNode *arguments, Toy_ASTNode *returns, Toy_ASTNode *block)
 * @brief
 *
 * @param nodeHandle
 * @param identifier
 * @param arguments
 * @param returns
 * @param block
 */
void Toy_emitASTNodeFnDecl(Toy_ASTNode **nodeHandle, Toy_Literal identifier, Toy_ASTNode *arguments, Toy_ASTNode *returns, Toy_ASTNode *block);

/**
 * @typedef Toy_NodeFnDecl
 * @brief
 *
 */
typedef struct Toy_NodeFnDecl {
    Toy_ASTNodeType type;
    Toy_Literal identifier;
    Toy_ASTNode *arguments;
    Toy_ASTNode *returns;
    Toy_ASTNode *block;
} Toy_NodeFnDecl;

//function call
/**
 * @fn void Toy_emitASTNodeFnCall(Toy_ASTNode **nodeHandle, Toy_ASTNode *arguments)
 * @brief
 *
 * @param nodeHandle
 * @param arguments
 */
void Toy_emitASTNodeFnCall(Toy_ASTNode **nodeHandle, Toy_ASTNode *arguments);

/**
 * @typedef Toy_NodeFnCall
 * @brief
 *
 */
typedef struct Toy_NodeFnCall {
    Toy_ASTNodeType type;
    Toy_ASTNode *arguments;
    int argumentCount; //NOTE: leave this, so it can be hacked by dottify()
} Toy_NodeFnCall;

//function return
/**
 * @fn void Toy_emitASTNodeFnReturn(Toy_ASTNode **nodeHandle, Toy_ASTNode *returns)
 * @brief
 *
 * @param nodeHandle
 * @param returns
 */
void Toy_emitASTNodeFnReturn(Toy_ASTNode **nodeHandle, Toy_ASTNode *returns);

/**
 * @stypedef Toy_NodeFnReturn
 * @brief
 *
 */
typedef struct Toy_NodeFnReturn {
    Toy_ASTNodeType type;
    Toy_ASTNode *returns;
} Toy_NodeFnReturn;

//control flow path - if-else, while, for, break, continue, return
/**
 * @fn void Toy_emitASTNodeIf(Toy_ASTNode **nodeHandle, Toy_ASTNode *condition, Toy_ASTNode *thenPath, Toy_ASTNode *elsePath)
 * @brief
 *
 * @param nodeHandle
 * @param condition
 * @param thenPath
 * @param elsePath
 */
void Toy_emitASTNodeIf(Toy_ASTNode **nodeHandle, Toy_ASTNode *condition, Toy_ASTNode *thenPath, Toy_ASTNode *elsePath);

/**
 * @fn void Toy_emitASTNodeWhile(Toy_ASTNode **nodeHandle, Toy_ASTNode *condition, Toy_ASTNode *thenPath)
 * @brief
 *
 * @param nodeHandle
 * @param condition
 * @param thenPath
 */
void Toy_emitASTNodeWhile(Toy_ASTNode **nodeHandle, Toy_ASTNode *condition, Toy_ASTNode *thenPath);

/**
 * @fn void Toy_emitASTNodeFor(Toy_ASTNode **nodeHandle, Toy_ASTNode *preClause, Toy_ASTNode *condition, Toy_ASTNode *postClause, Toy_ASTNode *thenPath)
 * @brief
 *
 * @param nodeHandle
 * @param preClause
 * @param condition
 * @param postClause
 * @param thenPath
 */
void Toy_emitASTNodeFor(Toy_ASTNode **nodeHandle, Toy_ASTNode *preClause, Toy_ASTNode *condition, Toy_ASTNode *postClause, Toy_ASTNode *thenPath);

/**
 * @fn void Toy_emitASTNodeBreak(Toy_ASTNode **nodeHandle)
 * @brief
 *
 * @param nodeHandle
 */
void Toy_emitASTNodeBreak(Toy_ASTNode **nodeHandle);

/**
 * @fn void Toy_emitASTNodeContinue(Toy_ASTNode **nodeHandle)
 * @brief
 *
 * @param nodeHandle
 */
void Toy_emitASTNodeContinue(Toy_ASTNode **nodeHandle);

/**
 * @typedef Toy_NodeIf
 * @brief
 *
 */
typedef struct Toy_NodeIf {
    Toy_ASTNodeType type;
    Toy_ASTNode *condition;
    Toy_ASTNode *thenPath;
    Toy_ASTNode *elsePath;
} Toy_NodeIf;

/**
 * @typedef Toy_NodeWhile
 * @brief
 *
 */
typedef struct Toy_NodeWhile {
    Toy_ASTNodeType type;
    Toy_ASTNode *condition;
    Toy_ASTNode *thenPath;
} Toy_NodeWhile;

/**
 * @typedef Toy_NodeFor
 * @brief
 *
 */
typedef struct Toy_NodeFor {
    Toy_ASTNodeType type;
    Toy_ASTNode *preClause;
    Toy_ASTNode *condition;
    Toy_ASTNode *postClause;
    Toy_ASTNode *thenPath;
} Toy_NodeFor;

/**
 * @typedef Toy_NodeBreak
 * @brief
 *
 */
typedef struct Toy_NodeBreak {
    Toy_ASTNodeType type;
} Toy_NodeBreak;

/**
 * @typedef Toy_NodeContinue
 * @brief
 *
 */
typedef struct Toy_NodeContinue {
    Toy_ASTNodeType type;
} Toy_NodeContinue;

//pre-post increment/decrement
/**
 * @fn void Toy_emitASTNodePrefixIncrement(Toy_ASTNode **nodeHandle, Toy_Literal identifier)
 * @brief
 *
 * @param nodeHandle
 * @param identifier
 */
void Toy_emitASTNodePrefixIncrement(Toy_ASTNode **nodeHandle, Toy_Literal identifier);

/**
 * @fn void Toy_emitASTNodePrefixDecrement(Toy_ASTNode **nodeHandle, Toy_Literal identifier)
 * @brief
 *
 * @param nodeHandle
 * @param identifier
 */
void Toy_emitASTNodePrefixDecrement(Toy_ASTNode **nodeHandle, Toy_Literal identifier);

/**
 * @fn void Toy_emitASTNodePostfixIncrement(Toy_ASTNode **nodeHandle, Toy_Literal identifier)
 * @brief
 *
 * @param nodeHandle
 * @param identifier
 */
void Toy_emitASTNodePostfixIncrement(Toy_ASTNode **nodeHandle, Toy_Literal identifier);

/**
 * @fn void Toy_emitASTNodePostfixDecrement(Toy_ASTNode **nodeHandle, Toy_Literal identifier)
 * @brief
 *
 * @param nodeHandle
 * @param identifier
 */
void Toy_emitASTNodePostfixDecrement(Toy_ASTNode **nodeHandle, Toy_Literal identifier);

/**
 * @typedef Toy_NodePrefixIncrement
 * @brief
 *
 */
typedef struct Toy_NodePrefixIncrement {
    Toy_ASTNodeType type;
    Toy_Literal identifier;
} Toy_NodePrefixIncrement;

/**
 * @typedef Toy_NodePrefixDecrement
 * @brief
 *
 */
typedef struct Toy_NodePrefixDecrement {
    Toy_ASTNodeType type;
    Toy_Literal identifier;
} Toy_NodePrefixDecrement;

/**
 * @typedef Toy_NodePostfixIncrement
 * @brief
 *
 */
typedef struct Toy_NodePostfixIncrement {
    Toy_ASTNodeType type;
    Toy_Literal identifier;
} Toy_NodePostfixIncrement;

/**
 * @typedef Toy_NodePostfixDecrement
 * @brief
 *
 */
typedef struct Toy_NodePostfixDecrement {
    Toy_ASTNodeType type;
    Toy_Literal identifier;
} Toy_NodePostfixDecrement;

//import a library
/**
 * @fn void Toy_emitASTNodeImport(Toy_ASTNode **nodeHandle, Toy_Literal identifier, Toy_Literal alias)
 * @brief
 *
 * @param nodeHandle
 * @param identifier
 * @param alias
 */
void Toy_emitASTNodeImport(Toy_ASTNode **nodeHandle, Toy_Literal identifier, Toy_Literal alias);

/**
 * @typedef Toy_NodeImport
 * @brief
 *
 */
typedef struct Toy_NodeImport {
    Toy_ASTNodeType type;
    Toy_Literal identifier;
    Toy_Literal alias;
} Toy_NodeImport;

//for doing nothing
/**
 * @fn void Toy_emitASTNodePass(Toy_ASTNode **nodeHandle)
 * @brief
 *
 * @param nodeHandle
 */
void Toy_emitASTNodePass(Toy_ASTNode **nodeHandle);

/**
 * @union Toy_private_node
 * @brief
 *
 */
union Toy_private_node {
    Toy_ASTNodeType type;
    Toy_NodeLiteral atomic;
    Toy_NodeUnary unary;
    Toy_NodeBinary binary;
    Toy_NodeTernary ternary;
    Toy_NodeGrouping grouping;
    Toy_NodeBlock block;
    Toy_NodeCompound compound;
    Toy_NodePair pair;
    Toy_NodeIndex index;
    Toy_NodeVarDecl varDecl;
    Toy_NodeFnCollection fnCollection;
    Toy_NodeFnDecl fnDecl;
    Toy_NodeFnCall fnCall;
    Toy_NodeFnReturn returns;
    Toy_NodeIf pathIf;
    Toy_NodeWhile pathWhile;
    Toy_NodeFor pathFor;
    Toy_NodeBreak pathBreak;
    Toy_NodeContinue pathContinue;
    Toy_NodePrefixIncrement prefixIncrement;
    Toy_NodePrefixDecrement prefixDecrement;
    Toy_NodePostfixIncrement postfixIncrement;
    Toy_NodePostfixDecrement postfixDecrement;
    Toy_NodeImport import;
};

/**
 * @fn void Toy_freeASTNode(Toy_ASTNode *node)
 * @brief
 *
 * @param node
 */
TOY_API void Toy_freeASTNode(Toy_ASTNode *node);

#endif /* TOY_AST_NODE_H_ */
