#include <iostream>
#include <boost/filesystem.hpp>
#include <stdlib.h>
#include <fstream>
#include <future>
#include <string>
#include <map>

using namespace std;

namespace bf = boost::filesystem;

extern vector<pair<future<bool>, thread>> threads;

bool WriteInfo(string filename, string current_path);
void MakeOutputInfoThreads(int argc, char *argv[], string  current_pth);
void StartKerr();