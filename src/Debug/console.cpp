/* console.c - David C. Bishop - 17 Nov 2008
 *
 * Thie file handles the pretty colourful text output, logging and the smiley
 * faces and such.
 *
 * [TODO]: It should probably be truly unicode aware. I had a look at using
 * w_char, but its really designed to be a drop in replacment for printf and it
 * was looking to complicated doing that.
 * [TODO]: I tried to compress all the function into one main function with a 
 * wrapper put passing va_lists was stripping the unicode (see above todo note).
 * [TODO]: Selecting unicode/colour should be dooable runtime, not #defined.
 */

#include "../Debug/console.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


void logit(const char* format, ...) {
   char prefix[] = "LOG";
   const char* colour = COLOUR_LIGHT_GREEN;

   int newsize = strlen(COLOUR_WHITE)*2 + strlen(colour) + 
      strlen(prefix) + strlen(COLOUR_NONE) + strlen(format) + 6;

   va_list ap;

   char* newformat = (char*)malloc(newsize);

   snprintf(newformat, newsize, "%s[%s%s%s]: %s%s\n", 
      COLOUR_WHITE, colour, prefix, COLOUR_WHITE, COLOUR_NONE, format);

   va_start(ap, format);
   vprintf(newformat, ap);
   va_end(ap);
   free(newformat);
}

void errorit(const char* format, ...) {
   char prefix[] = "ERROR";
   const char* colour = COLOUR_LIGHT_RED;

   int newsize = strlen(COLOUR_WHITE)*2 + strlen(colour) + 
      strlen(prefix) + strlen(COLOUR_NONE) + strlen(format) + 6;

   va_list ap;

   char* newformat = (char*)malloc(newsize);

   snprintf(newformat, newsize, "%s[%s%s%s]: %s%s\n", 
      COLOUR_WHITE, colour, prefix, COLOUR_WHITE, COLOUR_NONE, format);

   va_start(ap, format);
   vfprintf(stderr, newformat, ap);
   va_end(ap);
   free(newformat);
}

void debugit(int level, const char* format, ...) {
   if(DEBUG_LEVEL < level) {
      return;
   }

   char prefix[] = "DEBUG";
   const char* colour = COLOUR_YELLOW;

   int newsize = strlen(COLOUR_WHITE)*2 + strlen(colour) + 
      strlen(prefix) + strlen(COLOUR_NONE) + strlen(format) + 6;

   va_list ap;

   char* newformat = (char*)malloc(newsize);

   snprintf(newformat, newsize, "%s[%s%s%s]: %s%s\n", 
      COLOUR_WHITE, colour, prefix, COLOUR_WHITE, COLOUR_NONE, format);

   va_start(ap, format);
   vprintf(newformat, ap);
   va_end(ap);
   free(newformat);
}

void warnit(const char* format, ...) {
   char prefix[] = "WARNING";
   const char* colour = COLOUR_LIGHT_MAGENTA;

   int newsize = strlen(COLOUR_WHITE)*2 + strlen(colour) + 
      strlen(prefix) + strlen(COLOUR_NONE) + strlen(format) + 6;

   va_list ap;

   char* newformat = (char*)malloc(newsize);

   snprintf(newformat, newsize, "%s[%s%s%s]: %s%s\n", 
      COLOUR_WHITE, colour, prefix, COLOUR_WHITE, COLOUR_NONE, format);

   va_start(ap, format);
   vprintf(newformat, ap);
   va_end(ap);
   free(newformat);
}
