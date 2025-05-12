#include "../definition//interface.h"
#include "../definition/dijkstra.h"
#include "../definition/flyManager.h"
#include "../definition/graphLoader.h"
void clearScreen() { system("clear"); }
void displayPlane() {
  std::filesystem::path filePath = "./render/airplane.txt";

  std::ifstream inputFile(filePath);

  if (!inputFile.is_open()) {
    std::cerr << "Error opening file: " << filePath << std::endl;
  }
  std::string line;
  while (std::getline(inputFile, line)) {
    std::cout << line << std::endl;
  }

  inputFile.close();
}
void commandExecution(flyManager fly_manager, int command) {
  clearScreen();
  switch (command) {
  case 1: {
    fly_manager.displayFlies();
    break;
  }
  case 2: {
    string source;
    string destination;
    std::cout << "INITIAL POINT(SOURCE): ";

    cin >> source;
    std::cout << std::endl;
    std::cout << "FINAL POINT(DESTINATION): ";
    cin >> destination;
    std::cout << std::endl;
    Dijkstra path_helper = Dijkstra(fly_manager, source, destination);

    path_helper.writeConnections("routes");
    path_helper.findShortPath();
    path_helper.summary("routes");
    break;
  }
  case 3: {
    fly_manager.setRandomPortDistance();
    std::cout << "RANDOM" << std::endl;
    string source;
    string destination;
    std::cout << "INITIAL POINT(SOURCE): ";
    cin >> source;

    std::cout << std::endl;

    std::cout << "FINAL POINT(DESTINATION): ";
    cin >> destination;
    std::cout << std::endl;
    Dijkstra path_helper = Dijkstra(fly_manager, source, destination);
    path_helper.writeConnections("random");
    path_helper.findShortPath();
    path_helper.summary("random");
    break;
  }
  case 4: {
    graphLoader::render("default");
    fly_manager.overview();
    break;
  }
  default:

    break;
  }

  std::cout << endl;
  string s;
  std::cout << "Press any character to proceed...\n";
  std::cin.ignore() >> s; // Waits for the user to press Enter
}

void options() {
  displayPlane();
  std::cout << "Menu: " << std::endl;
  std::cout << "q) exit program" << std::endl;
  std::cout << "1) display port routes" << std::endl;
  std::cout << "2) find short path" << std::endl;
  std::cout << "3) generate random routes" << std::endl;
  std::cout << "4) render routes" << std::endl;
}
void Interface::menu() {
  std::cout << "FIND short PATH" << std::endl;
  flyManager fly_manager = flyManager();
  graphLoader::loadGraph(fly_manager);
  while (true) {
    short int command;
    clearScreen();
    options();
    std::cout << "command: ";

    cin >> command;
    if (command <= 0) {
      break;
    }
    commandExecution(fly_manager, command);
  }
}
