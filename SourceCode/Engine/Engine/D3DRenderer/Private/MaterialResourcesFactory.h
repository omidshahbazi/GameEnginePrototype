// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MATERIALFACTORY_H
#define MATERIALFACTORY_H

#include <Public\Renderer\IMaterialResourcesFactory.h>
#include <Private\JSONCPPInclude.h>
#include <Public\Enum.h>


#define SUPPORTED_EXTENSIONS "material"


BEGIN_NAMESPACE


class MaterialResourcesFactory : public IMaterialResourcesFactory
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
			LOG_ERROR("Parsing material failed for [" + Name + "], " + r.getFormatedErrorMessages().c_str())

				return NULL;
		}

		Material *mat = new Material;

		if (root == nullValue)
		{
			mat->CreatePass();
			return mat;
		}

		IPass *pass = NULL;
		for (uint32 i = 0; i < root.size(); i++)
		{
			const Value &current = root[i];

			pass = mat->CreatePass();

			pass->SetFillMode(Enum::Parse<FillModes>("FillModes", current.get("FillMode", "Solid").asCString()));
			pass->SetZCompareFunction(Enum::Parse<CompareFunctions>("CompareFunctions", current.get("ZCompareFunction", "Always").asCString()));
			pass->SetZWrite(current.get("ZWrite", true).asBool());
			pass->SetBlendOperation(Enum::Parse<BlendOperations>("BlendOperations", current.get("BlendOperation", "Add").asCString()));
			pass->SetSourceBlendFactor(Enum::Parse<BlendFactors>("BlendFactors", current.get("SourceBlendFactor", "Zero").asCString()));
			pass->SetDestinationBlendFactor(Enum::Parse<BlendFactors>("BlendFactors", current.get("DestinationBlendFactor", "One").asCString()));
			pass->SetAlphaTestFunction(Enum::Parse<CompareFunctions>("CompareFunctions", current.get("AlphaTestFunction", "Always").asCString()));
			pass->SetAlphaTestReference(current.get("AlphaTestReference", 255).asUInt());
			pass->SetCullType(Enum::Parse<CullTypes>("CullTypes", current.get("CullType", "ClockWise").asCString()));

			for (uint32 t = 0; t < maxSupportedTexturesCount; t++)
			{
				const Value value = current.get(("Texture" + StringConverter::ToString(t)).GetBuffer(), nullValue);
				if (value != nullValue)
					pass->SetTextureStage(t, texManager.GetTexture(value.asCString()));
			}

			IGPUProgram *prog = GPUProgramResourcesFactory::LoadGPUProgram(pass->GetVertexProgram(), current.get("VertexProgram", nullValue), true);
			if (prog)
				pass->SetVertexProgram(prog);

			prog = GPUProgramResourcesFactory::LoadGPUProgram(pass->GetFragmentProgram(), current.get("FragmentProgram", nullValue), false);
			if (prog)
				pass->SetFragmentProgram(prog);
		}

		return mat;
	}

	IMaterial *CreateMaterial(void) const
	{
		Material *mat = new Material;
		mat->CreatePass();
		return mat;
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
#endif // MATERIALFACTORY_H
