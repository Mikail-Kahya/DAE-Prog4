#include "FileInterface.h"

FileInterface::FileInterface(const std::string& name)
{
    m_Hash = GetHash(name);
}

int FileInterface::GetHash(const std::string& name)
{
    int hash{};
    for (size_t idx{}; idx < name.size(); ++idx)
        hash += static_cast<int>(roundf(name[idx] / static_cast<float>(idx)));

    return hash;
}

void FileInterface::Rename(const std::string& name)
{
    m_Hash = GetHash(name);
}

bool FileInterface::IsFile(const std::string& name)
{
    return GetHash(name) == m_Hash;
}
