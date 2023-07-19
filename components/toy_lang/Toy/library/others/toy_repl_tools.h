#ifndef TOY_REPL_TOOLS_H_
#define TOY_REPL_TOOLS_H_

#include "toy_common.h"

/**
 * @fn const unsigned char* Toy_readFile(const char *path, size_t *fileSize)
 * @brief
 *
 * @param path
 * @param fileSize
 * @return
 */
const unsigned char* Toy_readFile(const char *path, size_t *fileSize);

/**
 * @fn int Toy_writeFile(const char *path, const unsigned char *bytes, size_t size)
 * @brief
 *
 * @param path
 * @param bytes
 * @param size
 * @return
 */
int Toy_writeFile(const char *path, const unsigned char *bytes, size_t size);

/**
 * @fn const unsigned char* Toy_compileString(const char *source, size_t *size)
 * @brief
 *
 * @param source
 * @param size
 * @return
 */
const unsigned char* Toy_compileString(const char *source, size_t *size);

/**
 * @fn void Toy_runBinary(const unsigned char *tb, size_t size)
 * @brief
 *
 * @param tb
 * @param size
 */
void Toy_runBinary(const unsigned char *tb, size_t size);

/**
 * @fn void Toy_runBinaryFile(const char *fname)
 * @brief
 *
 * @param fname
 */
void Toy_runBinaryFile(const char *fname);

/**
 * @fn void Toy_runSource(const char *source)
 * @brief
 *
 * @param source
 */
void Toy_runSource(const char *source);

/**
 * @fn void Toy_runSourceFile(const char *fname)
 * @brief
 *
 * @param fname
 */
void Toy_runSourceFile(const char *fname);

/**
 * @fn void Toy_parseBinaryFileHeader(const char *fname)
 * @brief
 *
 * @param fname
 */
void Toy_parseBinaryFileHeader(const char *fname);

#endif /* TOY_REPL_TOOLS_H_ */
