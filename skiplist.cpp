#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

#define MAX_LEVEL 16

struct SkipNode {
    int value;
    SkipNode *forward[MAX_LEVEL];

    SkipNode() {
        value = 0;
        for (int i = 0; i < MAX_LEVEL; i++) {
            forward[i] = nullptr;
        }
    }
};

class Skiplist {
public:
    Skiplist() {
        srand(time(0));
        head = new SkipNode();
        level = 0;
    }

    bool search(int target) {
        SkipNode *current = head;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < target) {
                current = current->forward[i];
            }
            if (current->forward[i] != nullptr && current->forward[i]->value == target) {
                return true;
            }
        }
        return false;
    }

    void add(int num) {
        SkipNode *update[MAX_LEVEL];
        SkipNode *current = head;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < num) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        // get max level
        int max_level = 0;
        while ((rand() % 100) < 50 && max_level < MAX_LEVEL - 1) {
            max_level++;
        }

        if (max_level > level) {
            for (int i = max_level; i > level; i--) {
                update[i] = head;
            }
            level = max_level;
        }

        // insert
        SkipNode *n = new SkipNode();
        n->value = num;
        for (int i = max_level; i >= 0; i--) {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
    }

    bool erase(int num) {
        SkipNode *update[MAX_LEVEL];
        SkipNode *current = head;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < num) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        if (current->forward[0] != nullptr && current->forward[0]->value == num) {
            current = current->forward[0];
            for (int i = 0; i <= level; i++) {
                if (update[i]->forward[i] == current) {
                    update[i]->forward[i] = current->forward[i];
                } else {
                    break;
                }
            }
            while (level > 0 && head->forward[level] == nullptr) {
                level--;
            }
            delete current;
            return true;
        } else {
            return false;
        }
    }

private:
    SkipNode *head;
    int level;
};

int main() {
    Skiplist s;
    s.add(1);
    for (int i = 0; i < 50; i++) {
        s.add(i);
    }
    for (int i = 0; i < 40; i++) {
        s.erase(i);
    }
    s.erase(1);
    s.erase(1);
    s.search(1);
    s.add(1);
    s.erase(1);
    return 0;
}