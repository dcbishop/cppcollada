/* This is a simple file for dumping text to a console, including pretty
 * colours and some things like unicode smiley faces. */
#ifndef CONSOLE_H
#define CONSOLE_H

#define DEBUG_VERY_HIGH 40
#define DEBUG_HIGH 30
#define DEBUG_MEDIUM 20
#define DEBUG_LOW 10
#define DEBUG_ALWAYS -10

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL DEBUG_MEDIUM
#endif

#define USE_COLOUR
#define USE_UNICODE

#ifdef _WIN32
#undef USE_COLOUR
#undef USE_UNICODE
#endif

#ifdef USE_COLOUR
#define COLOUR_LIGHT_RED "\033[1;31m"
#define COLOUR_LIGHT_GREEN "\033[1;32m"
#define COLOUR_YELLOW "\033[1;33m"
#define COLOUR_LIGHT_BLUE "\033[1;34m"
#define COLOUR_LIGHT_MAGENTA "\033[1;35m"
#define COLOUR_LIGHT_CYAN "\033[1;36m"
#define COLOUR_WHITE "\033[1;37m"
#define COLOUR_NONE "\033[0m"
#else
#define COLOUR_LIGHT_RED ""
#define COLOUR_LIGHT_GREEN ""
#define COLOUR_YELLOW ""
#define COLOUR_LIGHT_BLUE ""
#define COLOUR_LIGHT_MAGENTA ""
#define COLOUR_LIGHT_CYAN ""
#define COLOUR_WHITE ""
#define COLOUR_NONE ""
#endif

#ifdef USE_UNICODE
#define SYMBOL_SMILEY "☺"
#define SYMBOL_INVERTED_SMILEY "☻"
#define SYMBOL_SADLEY "☹"
#define SYMBOL_FATAL "☠"
#define SYMBOL_WARNING "☢"
#define SYMBOL_DEGREES "°"
#else
#define SYMBOL_SMILEY ":)"
#define SYMBOL_INVERTED_SMILEY "(:"
#define SYMBOL_SADLEY ":("
#define SYMBOL_FATAL ">_<"
#define SYMBOL_WARNING "(!)"
#define SYMBOL_DEGREES "deg"
#endif

#define DEBUG(level, fmt, ...) debugit(level, "%s[%s%s:%u%s]: [%s%s%s] %s" fmt, COLOUR_WHITE, COLOUR_LIGHT_CYAN, __FILE__, __LINE__, COLOUR_WHITE, COLOUR_LIGHT_BLUE, __FUNCTION__, COLOUR_WHITE, COLOUR_NONE, ## __VA_ARGS__)

#ifndef _DEBUG
#undef DEBUG
#define DEBUG(level, fmt, ...)
#endif

#define DEBUG_A(fmt, ...) DEBUG(DEBUG_ALWAYS, fmt, ## __VA_ARGS__)
#define DEBUG_L(fmt, ...) DEBUG(DEBUG_LOW, fmt, ## __VA_ARGS__)
#define DEBUG_M(fmt, ...) DEBUG(DEBUG_MEDIUM, fmt, ## __VA_ARGS__)
#define DEBUG_H(fmt, ...) DEBUG(DEBUG_HIGH, fmt, ## __VA_ARGS__)
#define DEBUG_V(fmt, ...) DEBUG(DEBUG_VERY_HIGH, fmt, ## __VA_ARGS__)

#define LOG(fmt, ...) logit("%s[%s%s%s:%s%s%s]:%s " fmt, COLOUR_WHITE, COLOUR_LIGHT_CYAN, __DATE__, COLOUR_WHITE, COLOUR_LIGHT_CYAN, __TIME__, COLOUR_WHITE, COLOUR_NONE, ## __VA_ARGS__)
#define WARNING(fmt, ...) warnit("%s[%s%s:%u%s]: [%s%s%s] %s" fmt, COLOUR_WHITE, COLOUR_LIGHT_CYAN, __FILE__, __LINE__, COLOUR_WHITE, COLOUR_LIGHT_BLUE, __FUNCTION__, COLOUR_WHITE, COLOUR_NONE, ## __VA_ARGS__)
#define ERROR(fmt, ...) errorit("%s[%s%s:%u%s]: [%s%s%s] %s" fmt, COLOUR_WHITE, COLOUR_LIGHT_CYAN, __FILE__, __LINE__, COLOUR_WHITE, COLOUR_LIGHT_BLUE, __FUNCTION__, COLOUR_WHITE, COLOUR_NONE, ## __VA_ARGS__)

#define BREAK() char buffer[255]; ERROR("Break point..."); fgets(buffer, 254, stdin)

void logit(const char* format, ...);
void errorit(const char* format, ...);
void debugit(int level, const char* format, ...);
void warnit(const char* format, ...);

#endif /* CONSOLE_H */
