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
	${OBJECTDIR}/_ext/2a0b8f30/causal_graph_listener.o \
	${OBJECTDIR}/_ext/2a0b8f30/flaw.o \
	${OBJECTDIR}/_ext/2a0b8f30/resolver.o \
	${OBJECTDIR}/_ext/2a0b8f30/state_variable.o \
	${OBJECTDIR}/atom_flaw.o \
	${OBJECTDIR}/disjunction_flaw.o \
	${OBJECTDIR}/enum_flaw.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/_ext/12d57e82/cg_test.o

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

${OBJECTDIR}/_ext/2a0b8f30/causal_graph_listener.o: /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/causal_graph_listener.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2a0b8f30
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a0b8f30/causal_graph_listener.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/causal_graph_listener.cpp

${OBJECTDIR}/_ext/2a0b8f30/flaw.o: /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/flaw.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2a0b8f30
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a0b8f30/flaw.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/flaw.cpp

${OBJECTDIR}/_ext/2a0b8f30/resolver.o: /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/resolver.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2a0b8f30
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a0b8f30/resolver.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/resolver.cpp

${OBJECTDIR}/_ext/2a0b8f30/state_variable.o: /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/state_variable.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2a0b8f30
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a0b8f30/state_variable.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/state_variable.cpp

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

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/_ext/12d57e82/cg_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/_ext/12d57e82/cg_test.o: /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/tests/cg_test.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/12d57e82
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/12d57e82/cg_test.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/tests/cg_test.cpp


${OBJECTDIR}/_ext/2a0b8f30/causal_graph_nomain.o: ${OBJECTDIR}/_ext/2a0b8f30/causal_graph.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/causal_graph.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2a0b8f30
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/2a0b8f30/causal_graph.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a0b8f30/causal_graph_nomain.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/causal_graph.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/2a0b8f30/causal_graph.o ${OBJECTDIR}/_ext/2a0b8f30/causal_graph_nomain.o;\
	fi

${OBJECTDIR}/_ext/2a0b8f30/causal_graph_listener_nomain.o: ${OBJECTDIR}/_ext/2a0b8f30/causal_graph_listener.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/causal_graph_listener.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2a0b8f30
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/2a0b8f30/causal_graph_listener.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a0b8f30/causal_graph_listener_nomain.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/causal_graph_listener.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/2a0b8f30/causal_graph_listener.o ${OBJECTDIR}/_ext/2a0b8f30/causal_graph_listener_nomain.o;\
	fi

${OBJECTDIR}/_ext/2a0b8f30/flaw_nomain.o: ${OBJECTDIR}/_ext/2a0b8f30/flaw.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/flaw.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2a0b8f30
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/2a0b8f30/flaw.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a0b8f30/flaw_nomain.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/flaw.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/2a0b8f30/flaw.o ${OBJECTDIR}/_ext/2a0b8f30/flaw_nomain.o;\
	fi

${OBJECTDIR}/_ext/2a0b8f30/resolver_nomain.o: ${OBJECTDIR}/_ext/2a0b8f30/resolver.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/resolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2a0b8f30
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/2a0b8f30/resolver.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a0b8f30/resolver_nomain.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/resolver.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/2a0b8f30/resolver.o ${OBJECTDIR}/_ext/2a0b8f30/resolver_nomain.o;\
	fi

${OBJECTDIR}/_ext/2a0b8f30/state_variable_nomain.o: ${OBJECTDIR}/_ext/2a0b8f30/state_variable.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/state_variable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2a0b8f30
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/2a0b8f30/state_variable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2a0b8f30/state_variable_nomain.o /C/Users/sydde/OneDrive/Documenti/NetBeansProjects/o-ratio/cg-lib/state_variable.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/2a0b8f30/state_variable.o ${OBJECTDIR}/_ext/2a0b8f30/state_variable_nomain.o;\
	fi

${OBJECTDIR}/atom_flaw_nomain.o: ${OBJECTDIR}/atom_flaw.o atom_flaw.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/atom_flaw.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/atom_flaw_nomain.o atom_flaw.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/atom_flaw.o ${OBJECTDIR}/atom_flaw_nomain.o;\
	fi

${OBJECTDIR}/disjunction_flaw_nomain.o: ${OBJECTDIR}/disjunction_flaw.o disjunction_flaw.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/disjunction_flaw.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/disjunction_flaw_nomain.o disjunction_flaw.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/disjunction_flaw.o ${OBJECTDIR}/disjunction_flaw_nomain.o;\
	fi

${OBJECTDIR}/enum_flaw_nomain.o: ${OBJECTDIR}/enum_flaw.o enum_flaw.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/enum_flaw.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/enum_flaw_nomain.o enum_flaw.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/enum_flaw.o ${OBJECTDIR}/enum_flaw_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

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
