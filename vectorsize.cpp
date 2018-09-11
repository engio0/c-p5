// comparing size, capacity and max_size
#include <iostream>
#include <vector>
#include <string>

int main ()
{
  std::vector<int> myvector;

  // set some content in the vector:
  for (int i=0; i<100; i++) myvector.push_back(i);

  std::cout << "size: " << myvector.size() << "\n";
  std::cout << "capacity: " << myvector.capacity() << "\n";
  std::cout << "max_size: " << myvector.max_size() << "\n";

  std::string word;
  std::vector<std::string> text;

  while (std::cin >> word) {
      text.push_back(word);
  }

  for (auto w : text) {
      std::cout << w << ", ";
  }
  std::cout << std::endl;

  return 0;
}
