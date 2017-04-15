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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/2a0b8f30/causal_graph.o \
	${OBJECTDIR}/_ext/2a0b8f30/flaw.o \
	${OBJECTDIR}/_ext/2a0b8f30/resolver.o \
	${OBJECTDIR}/atom_flaw.o \
	${OBJECTDIR}/disjunction_flaw.o \
	${OBJECTDIR}/enum_flaw.o


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
LDLIBSOPTIONS=-L/C/Program\ Files\ \(x86\)/LIBANTLR4/lib -L../smt-lib/dist/Debug/MinGW-Windows -lsmt-lib -L../core-lib/dist/Debug/MinGW-Windows -lcore-lib -lantlr4-runtime

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcg-lib.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcg-lib.${CND_DLIB_EXT}: ../smt-lib/dist/Debug/MinGW-Windows/libsmt-lib.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcg-lib.${CND_DLIB_EXT}: ../core-lib/dist/Debug/MinGW-Windows/libcore-lib.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcg-lib.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcg-lib.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared

${OBJECTDIR}/_ext/2a0b8f30/causal_graph.o: /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/causal_graph.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2a0b8f30
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a0b8f30/causal_graph.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/causal_graph.cpp

${OBJECTDIR}/_ext/2a0b8f30/flaw.o: /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/flaw.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2a0b8f30
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a0b8f30/flaw.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/flaw.cpp

${OBJECTDIR}/_ext/2a0b8f30/resolver.o: /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/resolver.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2a0b8f30
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a0b8f30/resolver.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/resolver.cpp

${OBJECTDIR}/atom_flaw.o: atom_flaw.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/atom_flaw.o atom_flaw.cpp

${OBJECTDIR}/disjunction_flaw.o: disjunction_flaw.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/disjunction_flaw.o disjunction_flaw.cpp

${OBJECTDIR}/enum_flaw.o: enum_flaw.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/enum_flaw.o enum_flaw.cpp

# Subprojects
.build-subprojects:
	cd ../smt-lib && ${MAKE}  -f Makefile CONF=Debug
	cd ../core-lib && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsmt-lib.dll ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcore-lib.dll
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcg-lib.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../smt-lib && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../core-lib && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc