#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/camera.o \
	${OBJECTDIR}/entity.o \
	${OBJECTDIR}/functions.o \
	${OBJECTDIR}/game.o \
	${OBJECTDIR}/input.o \
	${OBJECTDIR}/level.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/player.o \
	${OBJECTDIR}/renderer.o \
	${OBJECTDIR}/sprite.o \
	${OBJECTDIR}/tile.o \
	${OBJECTDIR}/tileset.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -lSDL2 -lSDL2_image
CXXFLAGS=-m64 -lSDL2 -lSDL2_image

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/lib/x86_64-linux-gnu

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isogame

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isogame: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isogame ${OBJECTFILES} ${LDLIBSOPTIONS} -lSDL2 -lSDL2_image

${OBJECTDIR}/camera.o: camera.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I/usr/include/nlohmann -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/camera.o camera.cpp

${OBJECTDIR}/entity.o: entity.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I/usr/include/nlohmann -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/entity.o entity.cpp

${OBJECTDIR}/functions.o: functions.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I/usr/include/nlohmann -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/functions.o functions.cpp

${OBJECTDIR}/game.o: game.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I/usr/include/nlohmann -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/game.o game.cpp

${OBJECTDIR}/input.o: input.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I/usr/include/nlohmann -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/input.o input.cpp

${OBJECTDIR}/level.o: level.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I/usr/include/nlohmann -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/level.o level.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I/usr/include/nlohmann -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/player.o: player.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I/usr/include/nlohmann -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player.o player.cpp

${OBJECTDIR}/renderer.o: renderer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I/usr/include/nlohmann -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/renderer.o renderer.cpp

${OBJECTDIR}/sprite.o: sprite.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I/usr/include/nlohmann -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sprite.o sprite.cpp

${OBJECTDIR}/tile.o: tile.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I/usr/include/nlohmann -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tile.o tile.cpp

${OBJECTDIR}/tileset.o: tileset.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I/usr/include/nlohmann -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tileset.o tileset.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
