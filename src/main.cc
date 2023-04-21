#include "./view/console.h"

int main() {
  Navigator navigator;
  Controller controller(&navigator);
  Console main_menu(&controller);
  main_menu.Run();
  return 0;
}
