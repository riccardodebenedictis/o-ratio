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
	${OBJECTDIR}/default_constructor.o \
	${OBJECTDIR}/defined_conjunction.o \
	${OBJECTDIR}/defined_constructor.o \
	${OBJECTDIR}/defined_method.o \
	${OBJECTDIR}/defined_predicate.o \
	${OBJECTDIR}/disjunction.o \
	${OBJECTDIR}/enum_type.o \
	${OBJECTDIR}/env.o \
	${OBJECTDIR}/expression_visitor.o \
	${OBJECTDIR}/field.o \
	${OBJECTDIR}/instantiated_field.o \
	${OBJECTDIR}/item.o \
	${OBJECTDIR}/method.o \
	${OBJECTDIR}/parser/ratioBaseListener.o \
	${OBJECTDIR}/parser/ratioBaseVisitor.o \
	${OBJECTDIR}/parser/ratioLexer.o \
	${OBJECTDIR}/parser/ratioListener.o \
	${OBJECTDIR}/parser/ratioParser.o \
	${OBJECTDIR}/parser/ratioVisitor.o \
	${OBJECTDIR}/predicate.o \
	${OBJECTDIR}/scope.o \
	${OBJECTDIR}/solver.o \
	${OBJECTDIR}/statement_visitor.o \
	${OBJECTDIR}/type.o \
	${OBJECTDIR}/type_declaration_listener.o \
	${OBJECTDIR}/type_refinement_listener.o \
	${OBJECTDIR}/type_visitor.o \
	${OBJECTDIR}/typedef_type.o

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
LDLIBSOPTIONS=-L/C/Program\ Files\ \(x86\)/LIBANTLR4/lib -L../smt-lib/dist/Release/MinGW-Windows -lsmt-lib -lantlr4-runtime

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
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/atom.o atom.cpp

${OBJECTDIR}/constructor.o: constructor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/constructor.o constructor.cpp

${OBJECTDIR}/core.o: core.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/core.o core.cpp

${OBJECTDIR}/default_constructor.o: default_constructor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/default_constructor.o default_constructor.cpp

${OBJECTDIR}/defined_conjunction.o: defined_conjunction.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/defined_conjunction.o defined_conjunction.cpp

${OBJECTDIR}/defined_constructor.o: defined_constructor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/defined_constructor.o defined_constructor.cpp

${OBJECTDIR}/defined_method.o: defined_method.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/defined_method.o defined_method.cpp

${OBJECTDIR}/defined_predicate.o: defined_predicate.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/defined_predicate.o defined_predicate.cpp

${OBJECTDIR}/disjunction.o: disjunction.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/disjunction.o disjunction.cpp

${OBJECTDIR}/enum_type.o: enum_type.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/enum_type.o enum_type.cpp

${OBJECTDIR}/env.o: env.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/env.o env.cpp

${OBJECTDIR}/expression_visitor.o: expression_visitor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/expression_visitor.o expression_visitor.cpp

${OBJECTDIR}/field.o: field.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/field.o field.cpp

${OBJECTDIR}/instantiated_field.o: instantiated_field.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instantiated_field.o instantiated_field.cpp

${OBJECTDIR}/item.o: item.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/item.o item.cpp

${OBJECTDIR}/method.o: method.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/method.o method.cpp

${OBJECTDIR}/parser/ratioBaseListener.o: parser/ratioBaseListener.cpp
	${MKDIR} -p ${OBJECTDIR}/parser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/ratioBaseListener.o parser/ratioBaseListener.cpp

${OBJECTDIR}/parser/ratioBaseVisitor.o: parser/ratioBaseVisitor.cpp
	${MKDIR} -p ${OBJECTDIR}/parser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/ratioBaseVisitor.o parser/ratioBaseVisitor.cpp

${OBJECTDIR}/parser/ratioLexer.o: parser/ratioLexer.cpp
	${MKDIR} -p ${OBJECTDIR}/parser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/ratioLexer.o parser/ratioLexer.cpp

${OBJECTDIR}/parser/ratioListener.o: parser/ratioListener.cpp
	${MKDIR} -p ${OBJECTDIR}/parser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/ratioListener.o parser/ratioListener.cpp

${OBJECTDIR}/parser/ratioParser.o: parser/ratioParser.cpp
	${MKDIR} -p ${OBJECTDIR}/parser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/ratioParser.o parser/ratioParser.cpp

${OBJECTDIR}/parser/ratioVisitor.o: parser/ratioVisitor.cpp
	${MKDIR} -p ${OBJECTDIR}/parser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/ratioVisitor.o parser/ratioVisitor.cpp

${OBJECTDIR}/predicate.o: predicate.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/predicate.o predicate.cpp

${OBJECTDIR}/scope.o: scope.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scope.o scope.cpp

${OBJECTDIR}/solver.o: solver.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/solver.o solver.cpp

${OBJECTDIR}/statement_visitor.o: statement_visitor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/statement_visitor.o statement_visitor.cpp

${OBJECTDIR}/type.o: type.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/type.o type.cpp

${OBJECTDIR}/type_declaration_listener.o: type_declaration_listener.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/type_declaration_listener.o type_declaration_listener.cpp

${OBJECTDIR}/type_refinement_listener.o: type_refinement_listener.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/type_refinement_listener.o type_refinement_listener.cpp

${OBJECTDIR}/type_visitor.o: type_visitor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/type_visitor.o type_visitor.cpp

${OBJECTDIR}/typedef_type.o: typedef_type.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/typedef_type.o typedef_type.cpp

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
	$(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/core_test.o tests/core_test.cpp


${OBJECTDIR}/atom_nomain.o: ${OBJECTDIR}/atom.o atom.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/atom.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/atom_nomain.o atom.cpp;\
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
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/constructor_nomain.o constructor.cpp;\
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
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/core_nomain.o core.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/core.o ${OBJECTDIR}/core_nomain.o;\
	fi

${OBJECTDIR}/default_constructor_nomain.o: ${OBJECTDIR}/default_constructor.o default_constructor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/default_constructor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/default_constructor_nomain.o default_constructor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/default_constructor.o ${OBJECTDIR}/default_constructor_nomain.o;\
	fi

${OBJECTDIR}/defined_conjunction_nomain.o: ${OBJECTDIR}/defined_conjunction.o defined_conjunction.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/defined_conjunction.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/defined_conjunction_nomain.o defined_conjunction.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/defined_conjunction.o ${OBJECTDIR}/defined_conjunction_nomain.o;\
	fi

${OBJECTDIR}/defined_constructor_nomain.o: ${OBJECTDIR}/defined_constructor.o defined_constructor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/defined_constructor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/defined_constructor_nomain.o defined_constructor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/defined_constructor.o ${OBJECTDIR}/defined_constructor_nomain.o;\
	fi

${OBJECTDIR}/defined_method_nomain.o: ${OBJECTDIR}/defined_method.o defined_method.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/defined_method.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/defined_method_nomain.o defined_method.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/defined_method.o ${OBJECTDIR}/defined_method_nomain.o;\
	fi

${OBJECTDIR}/defined_predicate_nomain.o: ${OBJECTDIR}/defined_predicate.o defined_predicate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/defined_predicate.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/defined_predicate_nomain.o defined_predicate.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/defined_predicate.o ${OBJECTDIR}/defined_predicate_nomain.o;\
	fi

${OBJECTDIR}/disjunction_nomain.o: ${OBJECTDIR}/disjunction.o disjunction.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/disjunction.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/disjunction_nomain.o disjunction.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/disjunction.o ${OBJECTDIR}/disjunction_nomain.o;\
	fi

${OBJECTDIR}/enum_type_nomain.o: ${OBJECTDIR}/enum_type.o enum_type.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/enum_type.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/enum_type_nomain.o enum_type.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/enum_type.o ${OBJECTDIR}/enum_type_nomain.o;\
	fi

${OBJECTDIR}/env_nomain.o: ${OBJECTDIR}/env.o env.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/env.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/env_nomain.o env.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/env.o ${OBJECTDIR}/env_nomain.o;\
	fi

${OBJECTDIR}/expression_visitor_nomain.o: ${OBJECTDIR}/expression_visitor.o expression_visitor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/expression_visitor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/expression_visitor_nomain.o expression_visitor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/expression_visitor.o ${OBJECTDIR}/expression_visitor_nomain.o;\
	fi

${OBJECTDIR}/field_nomain.o: ${OBJECTDIR}/field.o field.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/field.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/field_nomain.o field.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/field.o ${OBJECTDIR}/field_nomain.o;\
	fi

${OBJECTDIR}/instantiated_field_nomain.o: ${OBJECTDIR}/instantiated_field.o instantiated_field.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/instantiated_field.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instantiated_field_nomain.o instantiated_field.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/instantiated_field.o ${OBJECTDIR}/instantiated_field_nomain.o;\
	fi

${OBJECTDIR}/item_nomain.o: ${OBJECTDIR}/item.o item.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/item.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/item_nomain.o item.cpp;\
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
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/method_nomain.o method.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/method.o ${OBJECTDIR}/method_nomain.o;\
	fi

${OBJECTDIR}/parser/ratioBaseListener_nomain.o: ${OBJECTDIR}/parser/ratioBaseListener.o parser/ratioBaseListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/parser
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parser/ratioBaseListener.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/ratioBaseListener_nomain.o parser/ratioBaseListener.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/parser/ratioBaseListener.o ${OBJECTDIR}/parser/ratioBaseListener_nomain.o;\
	fi

${OBJECTDIR}/parser/ratioBaseVisitor_nomain.o: ${OBJECTDIR}/parser/ratioBaseVisitor.o parser/ratioBaseVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/parser
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parser/ratioBaseVisitor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/ratioBaseVisitor_nomain.o parser/ratioBaseVisitor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/parser/ratioBaseVisitor.o ${OBJECTDIR}/parser/ratioBaseVisitor_nomain.o;\
	fi

${OBJECTDIR}/parser/ratioLexer_nomain.o: ${OBJECTDIR}/parser/ratioLexer.o parser/ratioLexer.cpp 
	${MKDIR} -p ${OBJECTDIR}/parser
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parser/ratioLexer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/ratioLexer_nomain.o parser/ratioLexer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/parser/ratioLexer.o ${OBJECTDIR}/parser/ratioLexer_nomain.o;\
	fi

${OBJECTDIR}/parser/ratioListener_nomain.o: ${OBJECTDIR}/parser/ratioListener.o parser/ratioListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/parser
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parser/ratioListener.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/ratioListener_nomain.o parser/ratioListener.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/parser/ratioListener.o ${OBJECTDIR}/parser/ratioListener_nomain.o;\
	fi

${OBJECTDIR}/parser/ratioParser_nomain.o: ${OBJECTDIR}/parser/ratioParser.o parser/ratioParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/parser
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parser/ratioParser.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/ratioParser_nomain.o parser/ratioParser.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/parser/ratioParser.o ${OBJECTDIR}/parser/ratioParser_nomain.o;\
	fi

${OBJECTDIR}/parser/ratioVisitor_nomain.o: ${OBJECTDIR}/parser/ratioVisitor.o parser/ratioVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/parser
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parser/ratioVisitor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/ratioVisitor_nomain.o parser/ratioVisitor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/parser/ratioVisitor.o ${OBJECTDIR}/parser/ratioVisitor_nomain.o;\
	fi

${OBJECTDIR}/predicate_nomain.o: ${OBJECTDIR}/predicate.o predicate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/predicate.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/predicate_nomain.o predicate.cpp;\
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
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scope_nomain.o scope.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/scope.o ${OBJECTDIR}/scope_nomain.o;\
	fi

${OBJECTDIR}/solver_nomain.o: ${OBJECTDIR}/solver.o solver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/solver.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/solver_nomain.o solver.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/solver.o ${OBJECTDIR}/solver_nomain.o;\
	fi

${OBJECTDIR}/statement_visitor_nomain.o: ${OBJECTDIR}/statement_visitor.o statement_visitor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/statement_visitor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/statement_visitor_nomain.o statement_visitor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/statement_visitor.o ${OBJECTDIR}/statement_visitor_nomain.o;\
	fi

${OBJECTDIR}/type_nomain.o: ${OBJECTDIR}/type.o type.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/type.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/type_nomain.o type.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/type.o ${OBJECTDIR}/type_nomain.o;\
	fi

${OBJECTDIR}/type_declaration_listener_nomain.o: ${OBJECTDIR}/type_declaration_listener.o type_declaration_listener.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/type_declaration_listener.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/type_declaration_listener_nomain.o type_declaration_listener.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/type_declaration_listener.o ${OBJECTDIR}/type_declaration_listener_nomain.o;\
	fi

${OBJECTDIR}/type_refinement_listener_nomain.o: ${OBJECTDIR}/type_refinement_listener.o type_refinement_listener.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/type_refinement_listener.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/type_refinement_listener_nomain.o type_refinement_listener.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/type_refinement_listener.o ${OBJECTDIR}/type_refinement_listener_nomain.o;\
	fi

${OBJECTDIR}/type_visitor_nomain.o: ${OBJECTDIR}/type_visitor.o type_visitor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/type_visitor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/type_visitor_nomain.o type_visitor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/type_visitor.o ${OBJECTDIR}/type_visitor_nomain.o;\
	fi

${OBJECTDIR}/typedef_type_nomain.o: ${OBJECTDIR}/typedef_type.o typedef_type.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/typedef_type.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I../smt-lib -I/C/Program\ Files\ \(x86\)/LIBANTLR4/include/antlr4-runtime  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/typedef_type_nomain.o typedef_type.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/typedef_type.o ${OBJECTDIR}/typedef_type_nomain.o;\
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
