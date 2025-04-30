
#ifndef MYNAMESPACE_H
#define MYNAMESPACE_H
#include "flyManager.h"
#include <string>
#include <vector>
using namespace std;

namespace graphLoader {
vector<string> validNodeFormat(string line);
void loadGraph(flyManager &fly_manager);
void findPath(flyManager flies, string source, string destination);
void findShortPath(flyManager &flies, string source, string destination);
} // namespace graphLoader
#endif
