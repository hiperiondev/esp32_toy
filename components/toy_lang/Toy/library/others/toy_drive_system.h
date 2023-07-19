#ifndef TOY_DRIVE_SYSTEM_H_
#define TOY_DRIVE_SYSTEM_H_

#include "toy_common.h"
#include "toy_literal.h"
#include "toy_interpreter.h"

//file system API - these need to be set by the host
/**
 * @fn void Toy_initDriveSystem(void)
 * @brief
 *
 */
TOY_API void Toy_initDriveSystem(void);

/**
 * @fn void Toy_freeDriveSystem(void)
 * @brief
 *
 */
TOY_API void Toy_freeDriveSystem(void);

//file system API - for use with libs
/**
 * @fn void Toy_setDrivePath(char *drive, char *path)
 * @brief
 *
 * @param drive
 * @param path
 */
TOY_API void Toy_setDrivePath(char *drive, char *path);

/**
 * @fn Toy_Literal Toy_getDrivePathLiteral(Toy_Interpreter *interpreter, Toy_Literal *drivePathLiteral)
 * @brief
 *
 * @param interpreter
 * @param drivePathLiteral
 * @return
 */
TOY_API Toy_Literal Toy_getDrivePathLiteral(Toy_Interpreter *interpreter, Toy_Literal *drivePathLiteral);

#endif /* TOY_DRIVE_SYSTEM_H_ */
