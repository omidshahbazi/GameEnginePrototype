// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef COMPOSITEFACTORY_H
#define COMPOSITEFACTORY_H
#include <Public\Renderer\ICompositeResourcesFactory.h>
#include <Private\Composite.h>
#include <Private\JSONCPPInclude.h>


#define SUPPORTED_EXTENSIONS "composite"


BEGIN_NAMESPACE


class CompositeResourcesFactory : public ICompositeResourcesFactory
{
private:
	Resource *LoadResource(const String &Name) const
	{
		static uint32 maxSupportedTexturesCount = Core::GetReference().GetRenderer()->GetMaxSupportedTexturesCount();
		static const String &dataPath = Core::GetReference().GetDataPath();
		static TextureResourcesManager &texManager = TextureResourcesManager::GetReference();

		Value root;
		Reader r;

		String data = FileIO::GetReference().ReadText(dataPath + Name);

		if (!r.parse(data.GetBuffer(), root, false))
		{
			LOG_ERROR("Parsing composite failed for [" + Name + "], " + r.getFormatedErrorMessages().c_str())

				return NULL;
		}

		if (root == nullValue)
			return NULL;

		Composite *com = new Composite;

		//const String RenderTargetName = "RenderTarget";

		//CompositePass *pass = NULL;
		//for (uint32 i = 0; i < root.size(); i++)
		//{
		//	const Value &title = root[i++];
		//	const Value &value = root[i];

		//	const bool isRenderTarget = (title.asCString() == RenderTargetName);

		//	if (isRenderTarget)
		//	{
		//		texManager.CreateRenderTarget(
		//			value.get("Name", "").asCString(), 
		//			StringConverter::ParseVector2(value.get("Size", "Without, SizeforAutoSizetypes").asCString()), 
		//			ColourFormat[value.get("Format", "A8R8G8B8").asCString()]);
		//	}
		//	else
		//	{
		//		pass = (CompositePass*)com->CreatePass();

		//		for (uint32 t = 0; t < maxSupportedTexturesCount; t++)
		//		{
		//			const Value input = value.get(("Input" + StringConverter::ToString(t)).GetBuffer(), "None");

		//			ICompositePass::InputStage &stage = pass->GetInputStage(t);

		//			if (InputType.ContainsKey(input.asCString()))
		//				stage.InputType = InputType[input.asCString()];
		//			else
		//			{
		//				stage.InputType = ICompositePass::IT_RENDERTARGET;
		//				stage.Texture = texManager.GetTexture(input.asCString());
		//			}
		//		}

		//		const Value target = value.get("Target", nullValue);
		//		if (target != nullValue)
		//			pass->SetTarget((IRenderTarget*)texManager.GetTexture(target.asCString()));

		//		pass->SetClearColour(StringConverter::ParseColour(value.get("ClearColour", "0, 0, 0").asCString()));

		//		pass->SetProgram(GPUProgramFactory::LoadGPUProgram(pass->GetProgram(), value.get("Program", nullValue), false));
		//	}
		//}

		return com;
	}

	IComposite *CreateCompoiste(void) const
	{
		return NULL;
	}

	const String &GetSupportedExtensions(void) const
	{
		static const String Supported_Extensions(SUPPORTED_EXTENSIONS);

		return Supported_Extensions;
	}

	bool IsExtensionSupported(const String &Extension) const
	{
		static const String Supported_Extensions(SUPPORTED_EXTENSIONS);

		return Supported_Extensions == Extension.ToLowerCase();
	}
};

END_NAMESPACE
#endif // COMPOSITEFACTORY_H
