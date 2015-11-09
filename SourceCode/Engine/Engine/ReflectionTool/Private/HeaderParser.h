// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef HEADERPARSER_H
#define HEADERPARSER_H
#include <Private\CodePageParser.h>
#include <Private\MetaDataStructure.h>
#include <Private\MetaProperty.h>

BEGIN_NAMESPACE

class HeaderParser : public CodePageParser
{
public:
	HeaderParser(const String &Text) :
		CodePageParser(Text),
		m_CurrentDataStructure(NULL)
	{
	}

	void Parse(Type::TypesList &Types);

protected:
	virtual bool CompileDeclaration(Type::TypesList &Types, Token &Token);
	virtual void CompileTypeDeclaration(const Token &Declaration, Type::TypesList &Types);
	virtual void CompileEnumDeclaration(Type::TypesList &Types);
	virtual void CompileConstructorDeclaration(void);
	virtual void CompileFunctionDeclaration(void);
	virtual void CompileVariableDeclaration(void);

	virtual AccessSpecifiers GetAccessSpecifier(Token &Token);

	virtual void AddBlockLevel(void)
	{
		m_BlockLevel++;
	}

private:
	uint16 m_BlockLevel;
	MetaDataStructure *m_CurrentDataStructure;
};

END_NAMESPACE
#endif // HEADERPARSER_H
