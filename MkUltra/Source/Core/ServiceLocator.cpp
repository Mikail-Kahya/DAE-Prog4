#include "ServiceLocator.h"
#include "NullSoundSystem.h"
using namespace mk;

std::unique_ptr<SoundSystem> ServiceLocator::s_SoundSystem{ std::make_unique<NullSoundSystem>() };

SoundSystem& ServiceLocator::GetSoundSystem()
{
	return *s_SoundSystem;
}

void ServiceLocator::SetDefaultDataPath(const std::string& dataPath)
{
	GetSoundSystem().SetDefaultDataPath(dataPath);
	m_DataPath = dataPath;
}
