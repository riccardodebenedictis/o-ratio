
// Generated from ratio.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"


namespace ratio {

    class ratioLexer : public antlr4::Lexer {
    public:

        enum {
            TYPE_DEF = 1, REAL = 2, BOOL = 3, STRING = 4, ENUM = 5, CLASS = 6, GOAL = 7,
            FACT = 8, PREDICATE = 9, NEW = 10, OR = 11, THIS = 12, VOID = 13, TRUE = 14,
            FALSE = 15, RETURN = 16, DOT = 17, COMMA = 18, COLON = 19, SEMICOLON = 20,
            LPAREN = 21, RPAREN = 22, LBRACKET = 23, RBRACKET = 24, LBRACE = 25,
            RBRACE = 26, PLUS = 27, MINUS = 28, STAR = 29, SLASH = 30, AMP = 31,
            BAR = 32, EQUAL = 33, GT = 34, LT = 35, BANG = 36, EQEQ = 37, LTEQ = 38,
            GTEQ = 39, BANGEQ = 40, IMPLICATION = 41, CARET = 42, ID = 43, NumericLiteral = 44,
            StringLiteral = 45, LINE_COMMENT = 46, COMMENT = 47, WS = 48
        };

        ratioLexer(antlr4::CharStream *input);
        ~ratioLexer();

        virtual std::string getGrammarFileName() const override;
        virtual const std::vector<std::string>& getRuleNames() const override;

        virtual const std::vector<std::string>& getChannelNames() const override;
        virtual const std::vector<std::string>& getModeNames() const override;
        virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
        virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

        virtual const std::vector<uint16_t> getSerializedATN() const override;
        virtual const antlr4::atn::ATN& getATN() const override;

    private:
        static std::vector<antlr4::dfa::DFA> _decisionToDFA;
        static antlr4::atn::PredictionContextCache _sharedContextCache;
        static std::vector<std::string> _ruleNames;
        static std::vector<std::string> _tokenNames;
        static std::vector<std::string> _channelNames;
        static std::vector<std::string> _modeNames;

        static std::vector<std::string> _literalNames;
        static std::vector<std::string> _symbolicNames;
        static antlr4::dfa::Vocabulary _vocabulary;
        static antlr4::atn::ATN _atn;
        static std::vector<uint16_t> _serializedATN;


        // Individual action functions triggered by action() above.

        // Individual semantic predicate functions triggered by sempred() above.

        struct Initializer {
            Initializer();
        };
        static Initializer _init;
    };

} // namespace ratio
