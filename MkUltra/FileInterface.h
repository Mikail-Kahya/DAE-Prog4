#pragma once
#include <string>

class FileInterface
{
public:
	FileInterface(const std::string& name);
	virtual ~FileInterface() = default;

	static int GetHash(const std::string& name);

	void Rename(const std::string& name);
	bool IsFile(const std::string& name);

private:
	int m_Hash{};
};