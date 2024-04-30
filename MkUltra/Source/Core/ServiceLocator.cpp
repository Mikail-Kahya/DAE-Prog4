#include "ServiceLocator.h"
#include "NullSoundSystem.h"
using namespace mk;

SoundSystem& ServiceLocator::GetSoundSystem()
{
	if (!s_SoundSystem)
		s_SoundSystem = std::make_unique<NullSoundSystem>();
	return *s_SoundSystem;
}

void ServiceLocator::SetDefaultDataPath(const std::string& dataPath)
{
	GetSoundSystem().SetDefaultDataPath(dataPath);
	m_DataPath = dataPath;
}
