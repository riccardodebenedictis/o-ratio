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
	${OBJECTDIR}/atom_flaw.o \
	${OBJECTDIR}/causal_graph.o \
	${OBJECTDIR}/causal_graph_listener.o \
	${OBJECTDIR}/disjunction_flaw.o \
	${OBJECTDIR}/enum_flaw.o \
	${OBJECTDIR}/flaw.o \
	${OBJECTDIR}/resolver.o \
	${OBJECTDIR}/reusable_resource.o \
	${OBJECTDIR}/state_variable.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/cg_test.o \
	${TESTDIR}/tests/heuristic_test.o

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

${OBJECTDIR}/atom_flaw.o: atom_flaw.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/atom_flaw.o atom_flaw.cpp

${OBJECTDIR}/causal_graph.o: causal_graph.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/causal_graph.o causal_graph.cpp

${OBJECTDIR}/causal_graph_listener.o: causal_graph_listener.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/causal_graph_listener.o causal_graph_listener.cpp

${OBJECTDIR}/disjunction_flaw.o: disjunction_flaw.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/disjunction_flaw.o disjunction_flaw.cpp

${OBJECTDIR}/enum_flaw.o: enum_flaw.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/enum_flaw.o enum_flaw.cpp

${OBJECTDIR}/flaw.o: flaw.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/flaw.o flaw.cpp

${OBJECTDIR}/resolver.o: resolver.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/resolver.o resolver.cpp

${OBJECTDIR}/reusable_resource.o: reusable_resource.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/reusable_resource.o reusable_resource.cpp

${OBJECTDIR}/state_variable.o: state_variable.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/state_variable.o state_variable.cpp

# Subprojects
.build-subprojects:
	cd ../smt-lib && ${MAKE}  -f Makefile CONF=Debug
	cd ../core-lib && ${MAKE}  -f Makefile CONF=Debug

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/cg_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/heuristic_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/cg_test.o: tests/cg_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/cg_test.o tests/cg_test.cpp


${TESTDIR}/tests/heuristic_test.o: tests/heuristic_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/heuristic_test.o tests/heuristic_test.cpp


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

${OBJECTDIR}/causal_graph_nomain.o: ${OBJECTDIR}/causal_graph.o causal_graph.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/causal_graph.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/causal_graph_nomain.o causal_graph.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/causal_graph.o ${OBJECTDIR}/causal_graph_nomain.o;\
	fi

${OBJECTDIR}/causal_graph_listener_nomain.o: ${OBJECTDIR}/causal_graph_listener.o causal_graph_listener.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/causal_graph_listener.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/causal_graph_listener_nomain.o causal_graph_listener.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/causal_graph_listener.o ${OBJECTDIR}/causal_graph_listener_nomain.o;\
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

${OBJECTDIR}/flaw_nomain.o: ${OBJECTDIR}/flaw.o flaw.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/flaw.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/flaw_nomain.o flaw.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/flaw.o ${OBJECTDIR}/flaw_nomain.o;\
	fi

${OBJECTDIR}/resolver_nomain.o: ${OBJECTDIR}/resolver.o resolver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/resolver.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/resolver_nomain.o resolver.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/resolver.o ${OBJECTDIR}/resolver_nomain.o;\
	fi

${OBJECTDIR}/reusable_resource_nomain.o: ${OBJECTDIR}/reusable_resource.o reusable_resource.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/reusable_resource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/reusable_resource_nomain.o reusable_resource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/reusable_resource.o ${OBJECTDIR}/reusable_resource_nomain.o;\
	fi

${OBJECTDIR}/state_variable_nomain.o: ${OBJECTDIR}/state_variable.o state_variable.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/state_variable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -I../smt-lib -I../core-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/state_variable_nomain.o state_variable.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/state_variable.o ${OBJECTDIR}/state_variable_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
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
