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
	${OBJECTDIR}/atom.o \
	${OBJECTDIR}/constructor.o \
	${OBJECTDIR}/core.o \
	${OBJECTDIR}/disjunction.o \
	${OBJECTDIR}/env.o \
	${OBJECTDIR}/field.o \
	${OBJECTDIR}/item.o \
	${OBJECTDIR}/method.o \
	${OBJECTDIR}/predicate.o \
	${OBJECTDIR}/scope.o \
	${OBJECTDIR}/type.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/core_test.o

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
LDLIBSOPTIONS=-L../smt-lib/dist/Release/MinGW-Windows -lsmt-lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcore-lib.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcore-lib.${CND_DLIB_EXT}: ../smt-lib/dist/Release/MinGW-Windows/libsmt-lib.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcore-lib.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcore-lib.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared

${OBJECTDIR}/atom.o: atom.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/atom.o atom.cpp

${OBJECTDIR}/constructor.o: constructor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/constructor.o constructor.cpp

${OBJECTDIR}/core.o: core.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/core.o core.cpp

${OBJECTDIR}/disjunction.o: disjunction.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/disjunction.o disjunction.cpp

${OBJECTDIR}/env.o: env.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/env.o env.cpp

${OBJECTDIR}/field.o: field.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/field.o field.cpp

${OBJECTDIR}/item.o: item.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/item.o item.cpp

${OBJECTDIR}/method.o: method.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/method.o method.cpp

${OBJECTDIR}/predicate.o: predicate.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/predicate.o predicate.cpp

${OBJECTDIR}/scope.o: scope.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scope.o scope.cpp

${OBJECTDIR}/type.o: type.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/type.o type.cpp

# Subprojects
.build-subprojects:
	cd ../smt-lib && ${MAKE}  -f Makefile CONF=Release

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/core_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/core_test.o: tests/core_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/core_test.o tests/core_test.cpp


${OBJECTDIR}/atom_nomain.o: ${OBJECTDIR}/atom.o atom.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/atom.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/atom_nomain.o atom.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/atom.o ${OBJECTDIR}/atom_nomain.o;\
	fi

${OBJECTDIR}/constructor_nomain.o: ${OBJECTDIR}/constructor.o constructor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/constructor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/constructor_nomain.o constructor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/constructor.o ${OBJECTDIR}/constructor_nomain.o;\
	fi

${OBJECTDIR}/core_nomain.o: ${OBJECTDIR}/core.o core.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/core.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/core_nomain.o core.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/core.o ${OBJECTDIR}/core_nomain.o;\
	fi

${OBJECTDIR}/disjunction_nomain.o: ${OBJECTDIR}/disjunction.o disjunction.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/disjunction.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/disjunction_nomain.o disjunction.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/disjunction.o ${OBJECTDIR}/disjunction_nomain.o;\
	fi

${OBJECTDIR}/env_nomain.o: ${OBJECTDIR}/env.o env.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/env.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/env_nomain.o env.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/env.o ${OBJECTDIR}/env_nomain.o;\
	fi

${OBJECTDIR}/field_nomain.o: ${OBJECTDIR}/field.o field.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/field.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/field_nomain.o field.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/field.o ${OBJECTDIR}/field_nomain.o;\
	fi

${OBJECTDIR}/item_nomain.o: ${OBJECTDIR}/item.o item.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/item.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/item_nomain.o item.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/item.o ${OBJECTDIR}/item_nomain.o;\
	fi

${OBJECTDIR}/method_nomain.o: ${OBJECTDIR}/method.o method.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/method.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/method_nomain.o method.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/method.o ${OBJECTDIR}/method_nomain.o;\
	fi

${OBJECTDIR}/predicate_nomain.o: ${OBJECTDIR}/predicate.o predicate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/predicate.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/predicate_nomain.o predicate.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/predicate.o ${OBJECTDIR}/predicate_nomain.o;\
	fi

${OBJECTDIR}/scope_nomain.o: ${OBJECTDIR}/scope.o scope.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/scope.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scope_nomain.o scope.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/scope.o ${OBJECTDIR}/scope_nomain.o;\
	fi

${OBJECTDIR}/type_nomain.o: ${OBJECTDIR}/type.o type.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/type.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/type_nomain.o type.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/type.o ${OBJECTDIR}/type_nomain.o;\
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
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsmt-lib.dll
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcore-lib.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../smt-lib && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
