# GetDateTime.cmake - Sets a string with the current datetime.
# Written in 2011 by David Bishop <david@davidbishop.org>
#
# To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
# You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

# NOTE: This is the timestamp from the time cmake was run, not the compile time...

macro(DATETIME RESULT)
    if(WIN32)
        # NOTE: Windows has a differnt date format to everything else and will probably change the date/time format depending on the internationalization settings. Possible work around would be to use a vbs script via cscript.exe.
        execute_process(COMMAND "echo" "%DATE%" OUTPUT_VARIABLE RESULT_DATE)
        execute_process(COMMAND "echo" "%TIME%" OUTPUT_VARIABLE RESULT_TIME)
        string(STRIP ${RESULT_DATE} RESULT_DATE)
        string(STRIP ${RESULT_TIME} RESULT_TIME)
        set(${RESULT} "${RESULT_DATE} ${RESULT_TIME}")
    elseif(UNIX)
        execute_process(COMMAND "date" "+%Y-%m-%d\ %H:%M" OUTPUT_VARIABLE RESULT_RAW)
        string(STRIP ${RESULT_RAW} RESULT_RAW)
        set(${RESULT} ${RESULT_RAW})
    else(WIN32)
        message(SEND_ERROR "date not implemented")
        set(${RESULT} "UNKNOWN")
    endif(WIN32)
endmacro(DATETIME)
