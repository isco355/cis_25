
#ifndef MYNAMESPACE_H
#define MYNAMESPACE_H
#include "flyManager.h"
#include <string>
#include <vector>

#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
using namespace std;

namespace graphLoader {
void loadGraph(flyManager &fly_manager);
void traceRoute(string source_file, vector<string> path);
void render(string source_name_file);

void reWritedot(string file_name, vector<vector<string>> connections);
} // namespace graphLoader
#endif
