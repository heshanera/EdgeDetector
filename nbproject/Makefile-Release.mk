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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1146eab9/Canny.o \
	${OBJECTDIR}/_ext/1146eab9/DetectLine.o \
	${OBJECTDIR}/_ext/1146eab9/Skeletonize.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/line_detection

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/line_detection: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/line_detection ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1146eab9/Canny.o: /home/heshan/NetBeansProjects/Line\ Detection/Canny.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/1146eab9
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1146eab9/Canny.o /home/heshan/NetBeansProjects/Line\ Detection/Canny.cpp

${OBJECTDIR}/_ext/1146eab9/DetectLine.o: /home/heshan/NetBeansProjects/Line\ Detection/DetectLine.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/1146eab9
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1146eab9/DetectLine.o /home/heshan/NetBeansProjects/Line\ Detection/DetectLine.cpp

${OBJECTDIR}/_ext/1146eab9/Skeletonize.o: /home/heshan/NetBeansProjects/Line\ Detection/Skeletonize.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/1146eab9
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1146eab9/Skeletonize.o /home/heshan/NetBeansProjects/Line\ Detection/Skeletonize.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
