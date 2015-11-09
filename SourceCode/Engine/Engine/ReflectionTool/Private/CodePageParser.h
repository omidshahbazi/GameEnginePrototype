// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CODEPAGEPARSER_H
#define CODEPAGEPARSER_H

#include <Public\Common.h>
#include <Private\Specifiers.h>
#include <Private\Token.h>
#include <Private\Constants.h>

BEGIN_NAMESPACE

enum class SymbolParseOptions
{
	Normal = 0,
	CloseTemplateBracket
};

class CodePageParser
{
public:
	CodePageParser(const String &Text);

	virtual void Parse(Type::TypesList &Types);

protected:
	virtual bool GetToken(Token &Token, bool NoConst = false, SymbolParseOptions ParseTemplateCloseBracket = SymbolParseOptions::Normal);
	virtual void UngetToken(Token &Token);

	virtual char GetChar(bool Literal = false);
	virtual void UngetChar(void)
	{
		m_CurrentIndex = m_PrevIndex;
		m_CurrentLineIndex = m_PrevLineIndex;
	}
	virtual char GetLeadingChar(void);
	virtual char PeekChar(void) const
	{
		return (m_CurrentIndex < m_Text.GetLength() ? m_Text[m_CurrentIndex] : NULL);
	}

	virtual bool RequireSymbol(const String &Match, const String &Tag, SymbolParseOptions ParseTemplateCloseBracket = SymbolParseOptions::Normal);
	virtual bool MatchSymbol(const String &Match, SymbolParseOptions ParseTemplateCloseBracket = SymbolParseOptions::Normal);

	virtual bool RequireIdentifier(const String &Match, const String &Tag);
	virtual bool MatchIdentifier(const String &Match);

	virtual bool MatchSemiColon(void);

	virtual void ReadSpecifiers(Specifiers *Specifiers, const String &TypeName);

	virtual bool GetDataType(DataType &DataType);

	INLINE bool IsDigit(char c) const
	{
		return (c >= CHAR_0 && c <= CHAR_9);
	}

	INLINE bool IsEOL(char c) const
	{
		return (c == RETURN || c == NEWLINE || c == NULL);
	}

	INLINE bool IsWhitespace(char c) const
	{
		return (c == SPACE || c == TAB || c == RETURN || c == NEWLINE);
	}

	INLINE bool IsAlphabetic(char c) const
	{
		return ((c >= UPPER_A && c <= UPPER_Z) || (c >= LOWER_A && c <= LOWER_Z) || c == UNDERLINE);
	}

	INLINE bool IsAlphanumeric(char c) const
	{
		return (IsAlphabetic(c) || IsDigit(c));
	}

	static ValueTypes ParseValueType(const String &Value);

protected:
	String m_Text;

	uint32 m_CurrentIndex;
	uint32 m_PrevIndex;

	uint32 m_CurrentLineIndex;
	uint32 m_PrevLineIndex;
};

END_NAMESPACE
#endif // CODEPAGEPARSER_H
