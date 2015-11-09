// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Token.h>


BEGIN_NAMESPACE


//http://stackoverflow.com/questions/12251545/how-do-i-implement-a-lexer-given-that-i-have-already-implemented-a-basic-regular


Token::Token(void) :
PropertyType(NULL),
m_Type(Types::None)
{
}


bool Token::Matches(const String &Name) const
{
	return (m_Type == Types::Identifier && m_Name == Name);
}


bool Token::Matches(const String &Value, SearchCases SearchCase) const
{
	return ((m_Type == Types::Identifier || m_Type == Types::Symbol) && ((SearchCase == SearchCases::CaseSensitive) ? m_Identifier == Value : m_Identifier.ToLowerCase() == Value.ToLowerCase()));
}


void Token::SetConstantBool(bool Value)
{
	(PropertyType&)*this = PropertyType(NULL, ValueTypes::Bool);

	m_ConstantBool = Value;
	m_Type = Types::Constant;
}


void Token::SetConstantInt32(int32 Value)
{
	(PropertyType&)*this = PropertyType(NULL, ValueTypes::Int32);

	m_ConstantInt32 = Value;
	m_Type = Types::Constant;
}


void Token::SetConstantFloat32(float32 Value)
{
	(PropertyType&)*this = PropertyType(NULL, ValueTypes::Float32);

	m_ConstantFloat32 = Value;
	m_Type = Types::Constant;
}


void Token::SetConstantDouble32(double32 Value)
{
	(PropertyType&)*this = PropertyType(NULL, ValueTypes::Double32);

	m_ConstantDouble32 = Value;
	m_Type = Types::Constant;
}


void Token::SetConstantString(const String &Value)
{
	(PropertyType&)*this = PropertyType(NULL, ValueTypes::String);

	//m_ConstantDouble32 = Value;
	m_Type = Types::Constant;
}


END_NAMESPACE
