// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\TransformAPI.h>


BEGIN_NAMESPACE


ITransform *Transform_GetParent(ITransform *Transform)
{
	return Transform->GetParent();
}
void Transform_SetParent(ITransform *Transform, ITransform *Parent)
{
	Transform->SetParent(Parent);
}


Vector3 Transform_GetLocalPosition(ITransform *Transform)
{
	return Transform->GetLocalPosition();
}
void Transform_SetLocalPosition(ITransform *Transform, Vector3 Value)
{
	Transform->SetLocalPosition(Value);
}


Vector3 Transform_GetLocalRotation(ITransform *Transform)
{
	return Transform->GetLocalRotation();
}
void Transform_SetLocalRotation(ITransform *Transform, Vector3 Value)
{
	Transform->SetLocalRotation(Value);
}


Vector3 Transform_GetLocalScale(ITransform *Transform)
{
	return Transform->GetLocalScale();
}
void Transform_SetLocalScale(ITransform *Transform, Vector3 Value)
{
	Transform->SetLocalScale(Value);
}


Vector3 Transform_GetPosition(ITransform *Transform)
{
	return Transform->GetPosition();
}
void Transform_SetPosition(ITransform *Transform, Vector3 Value)
{
	Transform->SetPosition(Value);
}


Vector3 Transform_GetRotation(ITransform *Transform)
{
	return Transform->GetRotation();
}
void Transform_SetRotation(ITransform *Transform, Vector3 Value)
{
	Transform->SetRotation(Value);
}


Vector3 Transform_GetScale(ITransform *Transform)
{
	return Transform->GetScale();
}
void Transform_SetScale(ITransform *Transform, Vector3 Value)
{
	Transform->SetScale(Value);
}


void Transform_Translate(ITransform *Transform, Vector3 Value)
{
	Transform->Translate(Value);
}


void Transform_Rotate(ITransform *Transform, Vector3 Value)
{
	Transform->Rotate(Value);
}


void Transform_Scale(ITransform *Transform, Vector3 Value)
{
	Transform->Scale(Value);
}


END_NAMESPACE
