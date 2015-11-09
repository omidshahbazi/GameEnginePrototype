// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef GPUPROGRAMRESOURCESMANAGER_H
#define GPUPROGRAMRESOURCESMANAGER_H

#include <Public\ResourcesManager.h>
#include <Public\Renderer\IGPUProgramResourcesFactory.h>
#include <Public\ReflectionDefinitions.h>

BEGIN_NAMESPACE

REFLECTION_ENUM()
enum class PackMatrixTypes
{
	ColumnMajor = 0,
	RowMajor
};

REFLECTION_ENUM()
enum class OptimizationTypes
{
	None = 0,
	Level0,
	Level1,
	Level2,
	Level3
};

class CORE_API GPUProgramResourcesManager : public ResourcesManager
{
public:
	INLINE IGPUProgram *GetProgram(const String &Name)
	{
		return (IGPUProgram*)GetOrLoadResource(Name);
	}

	INLINE void Initialize(IGPUProgramResourcesFactory *Factory)
	{
		m_Factory = Factory;

		Reimport();
	}

	static void SetPackMatrixType(PackMatrixTypes Value)
	{
		m_PackMatrixType = Value;
	}
	static PackMatrixTypes GetPackMatrixType(void)
	{
		return m_PackMatrixType;
	}

	static void SetOptimizationType(OptimizationTypes Value)
	{
		m_OptimizationType = Value;
	}
	static OptimizationTypes GetOptimizationType(void)
	{
		return m_OptimizationType;
	}

private:
	INLINE IResourcesFactory *GetFactory(void) const
	{
		return m_Factory;
	}

protected:
	IGPUProgramResourcesFactory *m_Factory;

private:
	static PackMatrixTypes m_PackMatrixType;
	static OptimizationTypes m_OptimizationType;
};

END_NAMESPACE
#endif // GPUPROGRAMRESOURCESMANAGER_H
