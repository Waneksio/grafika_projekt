#include "Loader.h"

Loader::Loader(vector<char*> paths)
{
	for (char* path : paths)
		models.push_back(Model(path));
}