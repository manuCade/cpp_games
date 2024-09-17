#include <iostream>
#include <vector>

const unsigned kNumberOfDisks{3};

std::vector<unsigned> A{3, 2, 1}, B{}, C{};

void move(const unsigned number_of_disks, std::vector<unsigned>& source, 
          std::vector<unsigned>& auxiliary, std::vector<unsigned>& target) {
  if (number_of_disks <= 0) return;
  move(number_of_disks - 1, source, target, auxiliary);
  target.push_back(source[source.size() - 1]);
  source.pop_back();
  std::cout << "A: [";
  for (const unsigned disk : source)
    std::cout << disk << (disk == source[source.size() - 1] ? "" : ", ");
  std::cout << "]   B: [";
  for (const unsigned disk : auxiliary)
    std::cout << disk << (disk == auxiliary[auxiliary.size() - 1] ? "" : ", ");
  std::cout << "]   C: [";
  for (const unsigned disk : target)
    std::cout << disk << (disk == target[target.size() - 1] ? "" : ", ");
  std::cout << "]\n\n";
  move(number_of_disks - 1, auxiliary, source, target);
}

int main() {
  move(kNumberOfDisks, A, B, C);
}