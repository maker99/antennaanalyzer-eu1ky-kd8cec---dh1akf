#!/bin/bash

set -e
TIME_STAMP_FILE=${1:-"Src/Inc/build_timestamp.h"}

function write_timestamp {
    CurrYear=`date -u +%Y`
    CurrMonth=`date -u +%m`
    CurrDay=`date -u +%d`
    CurrHour=`date -u +%H`
    CurrMinute=`date -u +%M`

    echo \#define BUILD_TIMESTAMP \"${CurrYear}-${CurrMonth}-${CurrDay} ${CurrHour}:${CurrMinute} UT\" >> ${TIME_STAMP_FILE}
    echo \#define GITREVSTR\(s\) stringify_\(s\) >> ${TIME_STAMP_FILE}
    echo \#define stringify_\(s\) \#s >> ${TIME_STAMP_FILE}
    echo const char \* get_revision\(void\)\; >> ${TIME_STAMP_FILE}
    echo const char \* get_build_timestamp\(void\)\; >> ${TIME_STAMP_FILE}
    echo extern const char VERSION_STRING\[\]\; >> ${TIME_STAMP_FILE}
    echo \#endif >> ${TIME_STAMP_FILE}
    echo ${TIME_STAMP_FILE} file created at ${CurrYear}-${CurrMonth}-${CurrDay} ${CurrHour}:${CurrMinute} UT
}

function write_git_error {
    echo #warning GIT failed. Repository not found. Firmware revision will not be generated. >> ${TIME_STAMP_FILE}
    echo #define GITREV N/A >> ${TIME_STAMP_FILE}
}

function write_header {
    echo \#ifndef BUILD_TIMESTAMP > ${TIME_STAMP_FILE}
    git status &> /dev/null
    if [ $? -ne 0 ]; then
	echo Failed to execute git status
	return 1
    fi

    GITREV="$(git rev-parse --short=8 HEAD)"
    echo "#define GITREV \"${GITREV}\"" >> ${TIME_STAMP_FILE}
    return 0
}

write_header
if [ $? -eq 0 ]; then
    write_timestamp
else
    echo Failed to execute git status
    write_git_error
    write_timestamp
fi
