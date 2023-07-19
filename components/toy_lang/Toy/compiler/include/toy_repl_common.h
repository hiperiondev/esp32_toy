/**
 * @file toy_repl_common.h
 * @brief @@???@@
 *
 */

#ifndef TOY_REPL_COMMON_H_
#define TOY_REPL_COMMON_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @def TOY_VERSION_BUILD
 * @brief @@???@@
 *
 */
#define TOY_VERSION_BUILD Toy_private_version_build()

/**
 * @fn const char* Toy_private_version_build(void)
 * @brief @@???@@
 *
 * @return
 */
TOY_API const char* Toy_private_version_build(void);

/**
 * @typedef Toy_CommandLine
 * @brief @@???@@ Structure for processing the command line arguments in the repl
 *
 */
typedef struct {
    bool error;               /**< @@???@@ */
    bool help;                /**< @@???@@ */
    bool version;             /**< @@???@@ */
    char *binaryfile;         /**< @@???@@ */
    char *sourcefile;         /**< @@???@@ */
    char *compilefile;        /**< @@???@@ */
    char *outfile;            /**< defaults to out.tb */
    char *source;             /**< @@???@@ */
    char *initialfile;        /**< @@???@@ */
    bool enablePrintNewline;  /**< @@???@@ */
    bool parseBytecodeHeader; /**< @@???@@ */
    bool verbose;             /**< @@???@@ */
} Toy_CommandLine; /**< Toy_commandLine */

//these are intended for the repl only, despite using the api prefix
TOY_API Toy_CommandLine Toy_commandLine; /**< Toy_commandLine */

/**
 * @fn void Toy_initCommandLine(int argc, const char *argv[])
 * @brief @@???@@
 *
 * @param argc
 * @param argv
 */
TOY_API void Toy_initCommandLine(int argc, const char *argv[]);

/**
 * @fn void Toy_usageCommandLine(int argc, const char *argv[])
 * @brief @@???@@
 *
 * @param argc
 * @param argv
 */
TOY_API void Toy_usageCommandLine(int argc, const char *argv[]);

/**
 * @fn void Toy_helpCommandLine(int argc, const char *argv[])
 * @brief @@???@@
 *
 * @param argc
 * @param argv
 */
TOY_API void Toy_helpCommandLine(int argc, const char *argv[]);

/**
 * @fn void Toy_copyrightCommandLine(int argc, const char *argv[])
 * @brief @@???@@
 *
 * @param argc
 * @param argv
 */
TOY_API void Toy_copyrightCommandLine(int argc, const char *argv[]);

#endif /* TOY_REPL_COMMON_H_ */

