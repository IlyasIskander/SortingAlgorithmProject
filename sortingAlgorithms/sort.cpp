#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int randInt(int min, int max) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distr(min, max);
  int random_number = distr(gen);
  return random_number;
}

vector<int> genVector(int size) {
  vector<int> list = {};
  for (int i = 0; i < size; i += 1) {
    list.push_back(1 + i);
  }
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  shuffle(list.begin(), list.end(), mt19937(seed));
  return list;
}

int partition(vector<int> &vec, int low, int high) {

  int pivot = vec[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j += 1) {
    if (vec[j] <= pivot) {
      i += 1;
      swap(vec[i], vec[j]);
    }
  }

  swap(vec[i + 1], vec[high]);
  return (i + 1);
}

void merge(vector<int> &list, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  vector<int> leftV(n1);
  vector<int> rightV(n2);

  for (int i = 0; i < n1; ++i)
    leftV[i] = list[left + i];
  for (int i = 0; i < n2; ++i)
    rightV[i] = list[mid + 1 + i];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (leftV[i] <= rightV[j]) {
      list[k] = leftV[i];
      ++i;
    } else {
      list[k] = rightV[j];
      ++j;
    }
    ++k;
  }

  while (i < n1) {
    list[k] = leftV[i];
    ++i;
    ++k;
  }

  while (j < n2) {
    list[k] = rightV[j];
    ++j;
    ++k;
  }
}

vector<int> mergeSort(vector<int> &list, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    mergeSort(list, left, mid);
    mergeSort(list, mid + 1, right);

    merge(list, left, mid, right);
  }
  return list;
}

vector<int> quickSort(vector<int> &sort, int low, int high) {

  if (low < high) {

    int pi = partition(sort, low, high);

    quickSort(sort, low, pi - 1);
    quickSort(sort, pi + 1, high);
  }
  return sort;
}

vector<int> sortList(vector<int> list, int size, int algNum) {

  vector<int> sort = {};
  sort = list;

  if (algNum == 1) {

    // Bubble Sort

    for (int i = 1; i < size; i += 1) {
      for (int j = 0; j < (size - 1); j += 1) {
        if (sort[j] >
            sort[j + 1]) { // change this to a "<" for descending order
          swap(sort[j], sort[j + 1]);
        }
      }
    }
  } else if (algNum == 2) {

    // Selection Sort

    for (int j = 0; j < (size - 1); j += 1) {
      int min = j;
      for (int i = j + 1; i < size; i += 1) {
        if (sort[i] < sort[min]) { // change this to a ">" for descending order
          min = i;
        }
      }
      if (min != j) {
        swap(sort[j], sort[min]);
      }
    }
  } else if (algNum == 3) {

    // Insertion Sort

    for (int i = 0; i < size; i += 1) {
      int j = i;
      while (j > 0 && sort[j - 1] > sort[j]) {
        swap(sort[j], sort[j - 1]);
        j = j - 1;
      }
    }
  } else if (algNum == 4) {
    sort = mergeSort(sort, 0, size - 1); // Merge Sort
  } else {
     sort = quickSort(sort, 0, size - 1); // Quick Sort
  }

  return sort;
}

void printList(vector<int> list) {
  for (int i : list) {
    cout << i << " ";
  }
}

int main() {

  const int listSize = 50000;
  const int rep = 1;
  
  for (int i = 0; i < rep; i += 1) {
    cout << "TRIAL " << i+1 << endl << endl << endl;
    
    vector<int> list = genVector(listSize);
    
    auto bubbleStart = chrono::high_resolution_clock::now();
    vector<int> bubbleSort = sortList(list, listSize, 1);
    auto bubbleEnd = chrono::high_resolution_clock::now();
    auto bubbleDuration =
        chrono::duration_cast<chrono::milliseconds>(bubbleEnd - bubbleStart);
    cout << "Bubble Sort Time: " << bubbleDuration.count() << " milliseconds" << endl << endl;
  
    auto selectionStart = chrono::high_resolution_clock::now();
    vector<int> selectionSort = sortList(list, listSize, 2);
    auto selectionEnd = chrono::high_resolution_clock::now();
    auto selectionDuration = chrono::duration_cast<chrono::milliseconds>(
        selectionEnd - selectionStart);
    cout << "Selection Sort Time: " << selectionDuration.count() << " milliseconds" << endl << endl;
  
    auto insertionStart = chrono::high_resolution_clock::now();
    vector<int> insertionSort = sortList(list, listSize, 3);
    auto insertionEnd = chrono::high_resolution_clock::now();
    auto insertionDuration = chrono::duration_cast<chrono::milliseconds>(
        insertionEnd - insertionStart);
    cout << "Insertion Sort Time: " << insertionDuration.count() << " milliseconds" << endl << endl;
  
    auto mergeStart = chrono::high_resolution_clock::now();
    vector<int> mergeSort = sortList(list, listSize, 4);
    auto mergeEnd = chrono::high_resolution_clock::now();
    auto mergeDuration =
        chrono::duration_cast<chrono::milliseconds>(mergeEnd - mergeStart);
    cout << "Merge Sort Time: " << mergeDuration.count() << " milliseconds" << endl << endl;
  
    auto quickStart = chrono::high_resolution_clock::now();
    vector<int> quickSort = sortList(list, listSize, 5);
    auto quickEnd = chrono::high_resolution_clock::now();
    auto quickDuration =
        chrono::duration_cast<chrono::milliseconds>(quickEnd - quickStart);
    cout << "Quick Sort Time: " << quickDuration.count() << " milliseconds" << endl << endl << endl;
  }
  
  return 0;
}