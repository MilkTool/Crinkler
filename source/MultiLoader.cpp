#include "MultiLoader.h"
#include "CoffLibraryLoader.h"
#include "CoffObjectLoader.h"
#include "LTCGLoader.h"

using namespace std;

MultiLoader::MultiLoader() {
	m_loaders.push_back(new CoffLibraryLoader);
	m_loaders.push_back(new CoffObjectLoader);
	m_loaders.push_back(new LTCGLoader);
}

MultiLoader::~MultiLoader() {
	//free loaders
	for(list<HunkLoader*>::iterator it = m_loaders.begin(); it != m_loaders.end(); it++)
		delete *it;
}

bool MultiLoader::clicks(const char* data, int size) {
	for(list<HunkLoader*>::iterator it = m_loaders.begin(); it != m_loaders.end(); it++) {
		HunkLoader* hl = *it;
		if(hl->clicks(data, size))
			return true;
	}
	return false;
}

HunkList* MultiLoader::load(const char* data, int size, const char* module) {
	for(list<HunkLoader*>::iterator it = m_loaders.begin(); it != m_loaders.end(); it++) {
		HunkLoader* hl = *it;
		if(hl->clicks(data, size))
			return hl->load(data, size, module);
	}
	
	return NULL;
}