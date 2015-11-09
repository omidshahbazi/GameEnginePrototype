// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\CodePageParser.h>
#include <Public\CharacterUtilities.h>
#include <Public\StringConverter.h>
#include <Private\Console.h>


BEGIN_NAMESPACE


CodePageParser::CodePageParser(const String &Text) :
m_Text(Text)
{
}


void CodePageParser::Parse(Type::TypesList &Types)
{
	m_CurrentIndex = 0;
	m_PrevIndex = 0;
	m_CurrentLineIndex = 0;
	m_PrevLineIndex = 0;
}


bool CodePageParser::GetToken(Token &Token, bool NoConst, SymbolParseOptions ParseTemplateCloseBracket)
{
	//BaseParser.cpp Ln 307
	char c = GetLeadingChar();
	char p = PeekChar();

	if (c == NULL)
	{
		UngetChar();
		return false;
	}

	Token.SetStartIndex(m_PrevIndex);
	Token.SetLineIndex(m_PrevLineIndex);

	if (IsAlphabetic(c))
	{
		do
		{
			Token.GetIdentifier() += c;
			c = GetChar();
		} while (IsAlphanumeric(c));

		UngetChar();

		Token.SetType(Token::Types::Identifier);
		Token.SetName(Token.GetName());

		if (!NoConst)
		{
			if (Token.Matches("true"))
			{
				Token.SetConstantBool(true);
				return true;
			}
			else if (Token.Matches("false"))
			{
				Token.SetConstantBool(false);
				return true;
			}
		}

		return true;
	}
	else if (!NoConst && (IsDigit(c) || ((c == PLUS || c == MINES) && IsDigit(p))))
	{
		bool isFloat = false;
		bool isHex = false;

		do
		{
			if (c == DOT)
				isFloat = true;

			if (c == UPPER_X || c == LOWER_X)
				isHex = true;

			Token.GetIdentifier() += c;

			c = CharacterUtilities::ToUpperCase(GetChar());

		} while (IsDigit(c) || (!isFloat && c == DOT) || (!isHex && c == UPPER_X) || (isHex && c >= UPPER_A && c <= UPPER_F));

		if (isFloat || c != UPPER_F)
			UngetChar();

		if (isFloat)
			Token.SetConstantFloat32(StringConverter::ParseFloat32(Token.GetIdentifier()));
		else if (isHex)
			Token.SetConstantInt32(StringConverter::ParseInt32(Token.GetIdentifier()));
		else
			Token.SetConstantInt32(StringConverter::ParseInt32(Token.GetIdentifier()));

		return true;
	}
	else if (c == DOUBLE_QUOTATION)
	{
		String temp;
		c = GetChar(true);
		while (c != DOUBLE_QUOTATION && !IsEOL(c))
		{
			if (c == BACK_SLASH)
			{
				c = GetChar(true);

				if (IsEOL(c))
					break;
				else if (c == 'n')
					c = '\n';
			}

			temp += c;

			c = GetChar(true);
		}

		Token.SetConstantString(temp);

		return true;
	}
	else
	{
		Token.GetIdentifier() += c;

#define PAIR(cc, dd) (c == cc && d == dd)

		char d = GetChar();

		if (PAIR('<', '<') ||
			(PAIR('>', '>') && ParseTemplateCloseBracket != SymbolParseOptions::CloseTemplateBracket) ||
			PAIR('=', '=') ||
			PAIR('!', '=') ||
			PAIR('<', '=') ||
			PAIR('>', '=') ||
			PAIR('+', '+') ||
			PAIR('-', '-') ||
			PAIR('|', '|') ||
			PAIR('^', '^') ||
			PAIR('&', '&') ||
			PAIR('+', '=') ||
			PAIR('-', '=') ||
			PAIR('*', '=') ||
			PAIR('/', '=') ||
			PAIR('~', '=') ||
			PAIR(':', ':') ||
			PAIR('*', '*'))
		{
			Token.GetIdentifier() += d;

			if (c == '>' && d == '>')
			{
				if (GetChar() == '>')
					Token.GetIdentifier() += '>';
				else
					UngetChar();
			}
		}
		else
			UngetChar();

#undef PAIR

		Token.SetType(Token::Types::Symbol);

		Token.SetName(Token.GetIdentifier());

		return true;
	}
}


void CodePageParser::UngetToken(Token &Token)
{
	m_CurrentIndex = Token.GetStartIndex();
	m_CurrentLineIndex = Token.GetLineIndex();
}


char CodePageParser::GetChar(bool Literal)
{
	m_PrevIndex = m_CurrentIndex;
	m_PrevLineIndex = m_CurrentLineIndex;

	char c;
	do
	{
		c = m_Text[m_CurrentIndex++];

		if (c == NEWLINE)
			m_CurrentLineIndex++;
		else if (!Literal)
		{
			const char nextChar = PeekChar();
			if (c == SLASH && nextChar == STAR)
			{
				m_CurrentIndex++;
				continue;
			}
			else if (c == STAR && nextChar == SLASH)
			{
				m_CurrentIndex++;
				continue;
			}
		}

		return c;

	} while (true);
}


char CodePageParser::GetLeadingChar(void)
{
	char trailingCommentNewline = NULL;

	while (true)
	{
		bool multipleNewline = false;
		char c;

		do
		{
			c = GetChar();

			if (c == trailingCommentNewline)
				multipleNewline = true;

		} while (IsWhitespace(c));

		if (c != SLASH && PeekChar() != SLASH)
			return c;

		if (multipleNewline)
		{

		}

		do
		{
			c = GetChar(true);

			if (c == NULL)
				return c;

		} while (!IsEOL(c));

		trailingCommentNewline = c;

		do
		{
			c = GetChar();

			if (c == NULL)
				return c;

			if (c == trailingCommentNewline || !IsEOL(c))
			{
				UngetChar();
				break;
			}
		} while (true);
	}

	return NULL;
}


bool CodePageParser::RequireSymbol(const String &Match, const String &Tag, SymbolParseOptions ParseTemplateCloseBracket)
{
	if (MatchSymbol(Match, ParseTemplateCloseBracket))
		return true;

	Console::LogError("Missing '" + Match + "' in " + Tag);

	return false;
}


bool CodePageParser::MatchSymbol(const String &Match, SymbolParseOptions ParseTemplateCloseBracket)
{
	Token token;

	if (GetToken(token, true, ParseTemplateCloseBracket))
		if (token.GetTokenType() == Token::Types::Symbol && token.Matches(Match, Token::SearchCases::CaseSensitive))
			return true;
		else
			UngetToken(token);

	return false;
}


bool CodePageParser::RequireIdentifier(const String &Match, const String &Tag)
{
	if (MatchIdentifier(Match))
		return true;

	Console::LogError("Missing '" + Match + "' in " + Tag);

	return false;
}


bool CodePageParser::MatchIdentifier(const String &Match)
{
	Token token;

	if (GetToken(token, true))
		if (token.GetTokenType() == Token::Types::Identifier && token.Matches(Match, Token::SearchCases::IgnoreCase))
			return true;
		else
			UngetToken(token);

	return false;
}


bool CodePageParser::MatchSemiColon(void)
{
	if (MatchSymbol(SEMI_COLON))
		return true;

	Token token;
	if (GetToken(token))
		Console::LogError("Missing ';' before '" + token.GetIdentifier() + "'");
	else
		Console::LogError("Missing ';'");

	return false;
}


void CodePageParser::ReadSpecifiers(Specifiers *Specifiers, const String &TypeName)
{
	uint16 specifiersCount = 0;
	String error = TypeName + " declaration specifier";

	RequireSymbol(OPEN_BRACE, error);

	while (!MatchSymbol(CLOSE_BRACE))
	{
		if (specifiersCount > 0)
			RequireSymbol(COMMA, error);

		specifiersCount++;

		Token specifier;
		if (!GetToken(specifier))
			Console::LogError("Expected " + error);

		Specifiers->AddSpecifier(specifier.GetIdentifier());
	}
}


bool CodePageParser::GetDataType(DataType &DataType)
{
	while (true)
	{
		Token token;
		GetToken(token);

		ValueTypes valueType = ParseValueType(token.GetIdentifier());
		if (token.Matches(CLOSE_BRACE, Token::SearchCases::CaseSensitive))
			return false;
		if (valueType != ValueTypes::None)
			DataType.SetValueType(valueType);
		else if (token.Matches(STAR, Token::SearchCases::CaseSensitive))
		{
			DataType.SetPassType(DataType::PassesTypes::Pointer);
			break;
		}
		else if (token.Matches(AND, Token::SearchCases::CaseSensitive))
		{
			DataType.SetPassType(DataType::PassesTypes::Reference);
			break;
		}
		else if (token.Matches(CONST, Token::SearchCases::CaseSensitive))
		{
			if (DataType.GetValueType() == ValueTypes::None)
				DataType.SetIsConst(true);
			else
				DataType.SetIsConstValue(true);
		}
		else
			if (MatchSymbol(OPEN_BRACE) || MatchSymbol(CLOSE_BRACE) || MatchSymbol(SEMI_COLON) || MatchSymbol(COMMA))
			{
				UngetToken(token);
				break;
			}
			else
				DataType.SetExtraValueType(token.GetIdentifier());
	}

	return true;
}


ValueTypes CodePageParser::ParseValueType(const String &Value)
{
	ValueTypes type = ValueTypes::None;

	if (Value == "void")
		type = ValueTypes::Void;

	if (Value == "bool")
		type = ValueTypes::Bool;

	else if (Value == "uint8")
		type = ValueTypes::UInt8;
	else if (Value == "uint16")
		type = ValueTypes::UInt16;
	else if (Value == "uint32")
		type = ValueTypes::UInt32;
	else if (Value == "uint64")
		type = ValueTypes::UInt64;

	else if (Value == "int8")
		type = ValueTypes::Int8;
	else if (Value == "int16")
		type = ValueTypes::Int16;
	else if (Value == "int32")
		type = ValueTypes::Int32;
	else if (Value == "int64")
		type = ValueTypes::Int64;

	else if (Value == "float32")
		type = ValueTypes::Float32;
	else if (Value == "float64")
		type = ValueTypes::Float64;

	else if (Value == "double32")
		type = ValueTypes::Double32;
	else if (Value == "double64")
		type = ValueTypes::Double64;

	else if (Value == "String")
		type = ValueTypes::String;
	else if (Value == "Vector2")
		type = ValueTypes::Vector2;
	else if (Value == "Vector3")
		type = ValueTypes::Vector3;
	else if (Value == "Matrix4")
		type = ValueTypes::Matrix4;

	return type;
}


END_NAMESPACE
