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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/d4886e68/causal_graph_api.o \
	${OBJECTDIR}/_ext/d4886e68/causal_graph_java_listener.o \
	${OBJECTDIR}/solver_api.o


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
LDLIBSOPTIONS=-L/C/Program\ Files\ \(x86\)/LIBANTLR4/lib -L../../../smt-lib/dist/Release/MinGW-Windows -lsmt-lib -L../../../core-lib/dist/Release/MinGW-Windows -lcore-lib -L../../../cg-lib/dist/Release/MinGW-Windows -lcg-lib -lantlr4-runtime

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnative-api.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnative-api.${CND_DLIB_EXT}: ../../../smt-lib/dist/Release/MinGW-Windows/libsmt-lib.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnative-api.${CND_DLIB_EXT}: ../../../core-lib/dist/Release/MinGW-Windows/libcore-lib.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnative-api.${CND_DLIB_EXT}: ../../../cg-lib/dist/Release/MinGW-Windows/libcg-lib.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnative-api.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnative-api.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared

${OBJECTDIR}/_ext/d4886e68/causal_graph_api.o: /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/api/java/native-api/causal_graph_api.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d4886e68
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../smt-lib -I../../../core-lib -I../../../cg-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime -I/C/Program\ Files/Java/jdk1.8.0_121/include -I/C/Program\ Files/Java/jdk1.8.0_121/include/win32  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d4886e68/causal_graph_api.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/api/java/native-api/causal_graph_api.cpp

${OBJECTDIR}/_ext/d4886e68/causal_graph_java_listener.o: /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/api/java/native-api/causal_graph_java_listener.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d4886e68
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../smt-lib -I../../../core-lib -I../../../cg-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime -I/C/Program\ Files/Java/jdk1.8.0_121/include -I/C/Program\ Files/Java/jdk1.8.0_121/include/win32  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d4886e68/causal_graph_java_listener.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/api/java/native-api/causal_graph_java_listener.cpp

${OBJECTDIR}/solver_api.o: solver_api.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../../smt-lib -I../../../core-lib -I../../../cg-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime -I/C/Program\ Files/Java/jdk1.8.0_121/include -I/C/Program\ Files/Java/jdk1.8.0_121/include/win32  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/solver_api.o solver_api.cpp

# Subprojects
.build-subprojects:
	cd ../../../smt-lib && ${MAKE}  -f Makefile CONF=Release
	cd ../../../core-lib && ${MAKE}  -f Makefile CONF=Release
	cd ../../../cg-lib && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcg-lib.dll ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsmt-lib.dll ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcore-lib.dll
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnative-api.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../../../smt-lib && ${MAKE}  -f Makefile CONF=Release clean
	cd ../../../core-lib && ${MAKE}  -f Makefile CONF=Release clean
	cd ../../../cg-lib && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
