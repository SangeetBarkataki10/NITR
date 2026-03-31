#include <iostream>

#include "session_manager.h"

int main() {
  nitr::case009::SessionManager manager(30);

  const bool created = manager.CreateSession("alpha");
  const bool valid = manager.IsValid("alpha");

  std::cout << "created=" << created << " valid=" << valid
            << " count=" << manager.SessionCount() << "\n";
  return 0;
}
