// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Public\Common.h>
#include <Public\Object.h>
#include <Public\ReflectionDefinitions.h>

BEGIN_NAMESPACE

const char NEWLINE('\n');
const char RETURN('\r');
const char TAB('\t');
const char SPACE(' ');
const char SLASH('/');
const char BACK_SLASH('\\');
const char STAR('*');
const char AND('&');
const char UNDERLINE('_');
const char LOWER_A('a');
const char LOWER_X('x');
const char LOWER_Z('z');
const char UPPER_A('A');
const char UPPER_F('F');
const char UPPER_X('X');
const char UPPER_Z('Z');
const char DOUBLE_QUOTATION('"');
const char CHAR_0('0');
const char CHAR_9('9');
const char PLUS('+');
const char MINES('-');
const char EQUAL('=');
const char DOT('.');
const char COMMA(',');
const char COLON(':');
const char SEMI_COLON(';');
const char SHARP('#');
const char OPEN_BRACE('(');
const char CLOSE_BRACE(')');
const char OPEN_BRACKET('{');
const char CLOSE_BRACKET('}');

const String CONST(STRINGIZE(const));

const String CLASS(STRINGIZE(class));
const String STRUCT(STRINGIZE(struct));
const String REFLECTION_OBJECT_TEXT(STRINGIZE(REFLECTION_OBJECT));
const String REFLECTION_ENUM_TEXT(STRINGIZE(REFLECTION_ENUM));
const String REFLECTION_FUNCTION_TEXT(STRINGIZE(REFLECTION_FUNCTION));
const String REFLECTION_PROPERTY_TEXT(STRINGIZE(REFLECTION_PROPERTY));

END_NAMESPACE
#endif // CONSTANTS_H
