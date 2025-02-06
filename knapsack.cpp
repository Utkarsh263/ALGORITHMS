#include <iostream>
#include <vector>
#include <algorithm>

struct Item {
    int value;
    int weight;
    Item(int v, int w) : value(v), weight(w) {}
};

// Function to compare items based on their value-to-weight ratio
bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

// Function to partition the array for QuickSort
int partition(std::vector<Item>& items, int low, int high) {
    Item pivot = items[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (compare(items[j], pivot)) {
            i++;
            std::swap(items[i], items[j]);
        }
    }
    std::swap(items[i + 1], items[high]);
    return (i + 1);
}

// QuickSort algorithm
void quickSort(std::vector<Item>& items, int low, int high) {
    if (low < high) {
        int pi = partition(items, low, high);
        quickSort(items, low, pi - 1);
        quickSort(items, pi + 1, high);
    }
}

// Function to calculate the maximum value we can get
double fractionalKnapsack(int W, std::vector<Item>& items) {
    quickSort(items, 0, items.size() - 1);

    int currentWeight = 0;
    double totalValue = 0.0;

    for (auto& item : items) {
        if (currentWeight + item.weight <= W) {
            currentWeight += item.weight;
            totalValue += item.value;
        } else {
            int remainingWeight = W - currentWeight;
            totalValue += item.value * ((double)remainingWeight / item.weight);
            break;
        }
    }

    return totalValue;
}

int main() {
    std::vector<Item> items = {{60, 10}, {100, 20}, {120, 30}};
    int capacity = 50;

    double maxValue = fractionalKnapsack(capacity, items);
    std::cout << "Maximum value in Knapsack = " << maxValue << std::endl;

    return 0;
}
