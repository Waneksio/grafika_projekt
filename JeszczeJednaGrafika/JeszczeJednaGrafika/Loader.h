#ifndef LOADER_H
#define LOADER_H

#include "Model.h"

class Loader
{
public:
	vector<Model> models;
	Loader(vector<char*> paths);
};

#endif