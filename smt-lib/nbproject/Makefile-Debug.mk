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
	${OBJECTDIR}/clause.o \
	${OBJECTDIR}/interval.o \
	${OBJECTDIR}/la_theory.o \
	${OBJECTDIR}/lin.o \
	${OBJECTDIR}/lit.o \
	${OBJECTDIR}/sat_core.o \
	${OBJECTDIR}/set_theory.o \
	${OBJECTDIR}/theory.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/la_theory_test.o \
	${TESTDIR}/tests/sat_core_test.o

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsmt-lib.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsmt-lib.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsmt-lib.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared

${OBJECTDIR}/clause.o: clause.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clause.o clause.cpp

${OBJECTDIR}/interval.o: interval.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/interval.o interval.cpp

${OBJECTDIR}/la_theory.o: la_theory.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/la_theory.o la_theory.cpp

${OBJECTDIR}/lin.o: lin.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lin.o lin.cpp

${OBJECTDIR}/lit.o: lit.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lit.o lit.cpp

${OBJECTDIR}/sat_core.o: sat_core.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sat_core.o sat_core.cpp

${OBJECTDIR}/set_theory.o: set_theory.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/set_theory.o set_theory.cpp

${OBJECTDIR}/theory.o: theory.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/theory.o theory.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/la_theory_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/sat_core_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/la_theory_test.o: tests/la_theory_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/la_theory_test.o tests/la_theory_test.cpp


${TESTDIR}/tests/sat_core_test.o: tests/sat_core_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/sat_core_test.o tests/sat_core_test.cpp


${OBJECTDIR}/clause_nomain.o: ${OBJECTDIR}/clause.o clause.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/clause.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clause_nomain.o clause.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/clause.o ${OBJECTDIR}/clause_nomain.o;\
	fi

${OBJECTDIR}/interval_nomain.o: ${OBJECTDIR}/interval.o interval.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/interval.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/interval_nomain.o interval.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/interval.o ${OBJECTDIR}/interval_nomain.o;\
	fi

${OBJECTDIR}/la_theory_nomain.o: ${OBJECTDIR}/la_theory.o la_theory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/la_theory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/la_theory_nomain.o la_theory.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/la_theory.o ${OBJECTDIR}/la_theory_nomain.o;\
	fi

${OBJECTDIR}/lin_nomain.o: ${OBJECTDIR}/lin.o lin.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lin.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lin_nomain.o lin.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lin.o ${OBJECTDIR}/lin_nomain.o;\
	fi

${OBJECTDIR}/lit_nomain.o: ${OBJECTDIR}/lit.o lit.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lit.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lit_nomain.o lit.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lit.o ${OBJECTDIR}/lit_nomain.o;\
	fi

${OBJECTDIR}/sat_core_nomain.o: ${OBJECTDIR}/sat_core.o sat_core.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/sat_core.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sat_core_nomain.o sat_core.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/sat_core.o ${OBJECTDIR}/sat_core_nomain.o;\
	fi

${OBJECTDIR}/set_theory_nomain.o: ${OBJECTDIR}/set_theory.o set_theory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/set_theory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/set_theory_nomain.o set_theory.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/set_theory.o ${OBJECTDIR}/set_theory_nomain.o;\
	fi

${OBJECTDIR}/theory_nomain.o: ${OBJECTDIR}/theory.o theory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/theory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/theory_nomain.o theory.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/theory.o ${OBJECTDIR}/theory_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
