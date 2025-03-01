#include <cmath>
#include <unordered_map>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  std::unordered_map<int, ListNode *> nodeIndexes;
  void transverseNodes(ListNode *head) {
    ListNode *current = head;
    int index = 0;
    while (current != NULL) {
      nodeIndexes[index] = current;
      current = current->next;
      index++;
    }
  }
  ListNode *middleElement() {
    int size = nodeIndexes.size();
    if (size == 1) {
      return nodeIndexes[0];
    }
    int middle_index = std::round((float)size / 2) - 1;
    bool is_even = (size % 2 == 0);
    if (is_even) {
      middle_index += 1;
    }

    return nodeIndexes[middle_index];
  }

  ListNode *middleNode(ListNode *head) {
    transverseNodes(head);
    ListNode *middle = middleElement();
    return middle;
  }
};

int main() {

  Solution temp;
  // temp.nodeIndexes
  // temp.middleElement();
  return 0;
};
