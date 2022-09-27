#include "standalone-functions/sorting-algorithms.h"

std::vector<std::vector<Pillar>> draw_result_animation(
    std::vector<Pillar> array) {
  std::vector<std::vector<Pillar>> x;

  for (int i = 0; i < 3; i++) {
    x.push_back(array);
    for (Pillar &pill : x.at(x.size() - 1)) pill.change_state(NORMAL);

    x.push_back(array);
    for (Pillar &pill : x.at(x.size() - 1)) pill.change_state(MOVED);
  }

  return x;
}

std::vector<std::vector<Pillar>> insertion_sort_algorithm(
    std::vector<Pillar> array) {
  std::vector<std::vector<Pillar>> animation;
  animation.push_back(array);

  int temp, j;
  for (int i = 1ul; i < array.size(); i++) {
    temp = array.at(i)._value;
    j = i - 1;

    // Move elements of arr[0..i-1], that are greater than key, to one
    // position ahead of their current position
    while (j >= 0 && array.at(j)._value > temp) {
      array.at(j + 1)._value = array.at(j)._value;

      // Add the frame to the animation
      animation.push_back(array);
      // Change the colors
      animation.at(animation.size() - 1).at(i).change_state(SELECTED);
      animation.at(animation.size() - 1).at(j).change_state(MOVED);

      j--;
    }
    array.at(j + 1)._value = temp;

    // Add the frame to the animation
    animation.push_back(array);
    // Change the colors
    animation.at(animation.size() - 1).at(j + 1).change_state(MOVED);
  }

  std::vector<std::vector<Pillar>> temp_vec = draw_result_animation(array);
  animation.insert(animation.end(), temp_vec.begin(), temp_vec.end());

  animation.push_back(array);

  return animation;
}

void heapify(std::vector<Pillar> &array,
             std::vector<std::vector<Pillar>> &animation, int size, int root) {
  int largest = root;
  int left = 2 * root + 1;
  int right = 2 * root + 2;

  if (left < size && array.at(left)._value > array.at(largest)._value) {
    largest = left;
  }

  if (right < size && array.at(right)._value > array.at(largest)._value) {
    largest = right;
  }

  if (largest != root) {
    std::swap(array.at(root)._value, array.at(largest)._value);

    // Add the frame to the animation
    animation.push_back(array);
    // Change the colors
    animation.at(animation.size() - 1).at(root).change_state(MOVED);
    animation.at(animation.size() - 1).at(largest).change_state(MOVED);

    heapify(array, animation, size, largest);
  }
}

std::vector<std::vector<Pillar>> heap_sort_algorithm(
    std::vector<Pillar> array) {
  std::vector<std::vector<Pillar>> animation;
  animation.push_back(array);

  for (int i = array.size() / 2 - 1; i >= 0; i--) {
    heapify(array, animation, array.size(), i);
  }

  for (int i = array.size() - 1; i >= 0; i--) {
    std::swap(array.at(0)._value, array.at(i)._value);

    // Add the frame to the animation
    animation.push_back(array);
    // Change the colors
    animation.at(animation.size() - 1).at(i).change_state(MOVED);
    animation.at(animation.size() - 1).at(0).change_state(MOVED);

    heapify(array, animation, i, 0);

    // Add the frame to the animation
    animation.push_back(array);
    // Change the colors
    animation.at(animation.size() - 1).at(i).change_state(SELECTED);
  }

  std::vector<std::vector<Pillar>> temp_vec = draw_result_animation(array);
  animation.insert(animation.end(), temp_vec.begin(), temp_vec.end());

  animation.push_back(array);

  return animation;
}

std::vector<std::vector<Pillar>> selection_sort_algorithm(
    std::vector<Pillar> array) {
  std::vector<std::vector<Pillar>> animation;
  animation.push_back(array);

  int min_index;

  for (int i = 0; i < array.size() - 1; i++) {
    min_index = i;
    for (int j = i + 1; j < array.size(); j++) {
      if (array.at(j)._value < array.at(min_index)._value) {
        min_index = j;

        // Add the frame to the animation
        animation.push_back(array);
        // Change the colors
        animation.at(animation.size() - 1).at(i).change_state(SELECTED);
        animation.at(animation.size() - 1).at(j).change_state(MOVED);
      } else {
        // Add the frame to the animation
        animation.push_back(array);
        // Change the colors
        animation.at(animation.size() - 1).at(i).change_state(SELECTED);
        animation.at(animation.size() - 1).at(j).change_state(SELECTED);
      }
    }

    std::swap(array.at(i)._value, array.at(min_index)._value);

    // Add the frame to the animation
    animation.push_back(array);
    // Change the colors
    animation.at(animation.size() - 1).at(i).change_state(MOVED);
    animation.at(animation.size() - 1).at(min_index).change_state(MOVED);
  }

  std::vector<std::vector<Pillar>> temp_vec = draw_result_animation(array);
  animation.insert(animation.end(), temp_vec.begin(), temp_vec.end());

  animation.push_back(array);

  return animation;
}

void merge_vectors(std::vector<Pillar> &array,
                   std::vector<std::vector<Pillar>> &animation, int const left,
                   int const mid, int const right) {
  int const subArrayOne = mid - left + 1;
  int const subArrayTwo = right - mid;

  // Create temp arrays of Pillar pointers
  int leftArray[subArrayOne];
  int rightArray[subArrayTwo];

  // Copy data to the temp arrays leftArray[] and rightArray[]
  for (int i = 0ul; i < subArrayOne; i++) {
    leftArray[i] = array[left + i]._value;

    // Add the frame to the animation
    animation.push_back(array);
    // Change the colors
    animation.at(animation.size() - 1).at(left + i).change_state(SELECTED);
  }
  for (int i = 0ul; i < subArrayTwo; i++) {
    rightArray[i] = array[mid + 1 + i]._value;

    // Add the frame to the animation
    animation.push_back(array);
    // Change the colors
    animation.at(animation.size() - 1).at(mid + 1 + i).change_state(SELECTED);
  }

  int indexOfSubArrayOne = 0,     // Initial index of first sub-array
      indexOfSubArrayTwo = 0,     // Initial index of second sub-array
      indexOfMergedArray = left;  // Initial index of merged array

  // Merge the temp arrays back into array[left..right]
  while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
    if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
      array[indexOfMergedArray]._value = leftArray[indexOfSubArrayOne];

      // Add the frame to the animation
      animation.push_back(array);
      // Change the colors
      animation.at(animation.size() - 1)
          .at(indexOfMergedArray)
          .change_state(MOVED);
      animation.at(animation.size() - 1)
          .at(indexOfSubArrayOne + left)
          .change_state(MOVED);

      indexOfSubArrayOne++;
    } else {
      array[indexOfMergedArray]._value = rightArray[indexOfSubArrayTwo];

      // Add the frame to the animation
      animation.push_back(array);
      // Change the colors
      animation.at(animation.size() - 1)
          .at(indexOfMergedArray)
          .change_state(MOVED);
      animation.at(animation.size() - 1)
          .at(indexOfSubArrayTwo + mid + 1)
          .change_state(MOVED);

      indexOfSubArrayTwo++;
    }
    indexOfMergedArray++;
  }
  // Copy the remaining elements of
  // left[], if there are any
  while (indexOfSubArrayOne < subArrayOne) {
    array[indexOfMergedArray]._value = leftArray[indexOfSubArrayOne];

    // Add the frame to the animation
    animation.push_back(array);
    // Change the colors
    animation.at(animation.size() - 1)
        .at(indexOfMergedArray)
        .change_state(MOVED);

    indexOfSubArrayOne++;
    indexOfMergedArray++;
  }
  // Copy the remaining elements of
  // right[], if there are any
  while (indexOfSubArrayTwo < subArrayTwo) {
    array[indexOfMergedArray]._value = rightArray[indexOfSubArrayTwo];

    // Add the frame to the animation
    animation.push_back(array);
    // Change the colors
    animation.at(animation.size() - 1)
        .at(indexOfMergedArray)
        .change_state(MOVED);

    indexOfSubArrayTwo++;
    indexOfMergedArray++;
  }
}

void merge_recursive(std::vector<Pillar> &array,
                     std::vector<std::vector<Pillar>> &animation,
                     int const begin, int const end) {
  if (begin >= end) return;  // Returns recursively

  int mid = begin + (end - begin) / 2;
  merge_recursive(array, animation, begin, mid);
  merge_recursive(array, animation, mid + 1, end);
  merge_vectors(array, animation, begin, mid, end);
}

std::vector<std::vector<Pillar>> merge_sort_algorithm(
    std::vector<Pillar> array) {
  std::vector<std::vector<Pillar>> animation;
  animation.push_back(array);

  merge_recursive(array, animation, 0ul, array.size() - 1);

  std::vector<std::vector<Pillar>> temp_vec = draw_result_animation(array);
  animation.insert(animation.end(), temp_vec.begin(), temp_vec.end());

  animation.push_back(array);

  return animation;
}

int partition(std::vector<Pillar> &array,
              std::vector<std::vector<Pillar>> &animation, int low, int high) {
  int pivot = array[high]._value;  // pivot
  int i = low - 1;  // Index of smaller element and indicates the right position
                    // of pivot found so far

  for (int j = low; j <= high - 1; j++) {
    // If current element is smaller than the pivot
    if (array[j]._value < pivot) {
      i++;  // increment index of smaller element
      std::swap(array[i]._value, array[j]._value);

      // Add the frame to the animation
      animation.push_back(array);
      // Change the colors
      animation.at(animation.size() - 1).at(i).change_state(MOVED);
      animation.at(animation.size() - 1).at(j).change_state(MOVED);
      animation.at(animation.size() - 1).at(high).change_state(SELECTED);
    }
  }

  std::swap(array[i + 1]._value, array[high]._value);

  // Add the frame to the animation
  animation.push_back(array);
  // Change the colors
  animation.at(animation.size() - 1).at(i + 1).change_state(MOVED);
  animation.at(animation.size() - 1).at(high).change_state(MOVED);

  return i + 1;
}

void quick_recursive(std::vector<Pillar> &array,
                     std::vector<std::vector<Pillar>> &animation, int low,
                     int high) {
  if (low < high) {
    int pivot = partition(array, animation, low, high);

    quick_recursive(array, animation, low, pivot - 1);
    quick_recursive(array, animation, pivot + 1, high);
  }
}

std::vector<std::vector<Pillar>> quick_sort_algorithm(
    std::vector<Pillar> array) {
  std::vector<std::vector<Pillar>> animation;
  animation.push_back(array);

  quick_recursive(array, animation, 0, array.size() - 1);

  std::vector<std::vector<Pillar>> temp_vec = draw_result_animation(array);
  animation.insert(animation.end(), temp_vec.begin(), temp_vec.end());

  animation.push_back(array);

  return animation;
}

std::vector<std::vector<Pillar>> bubble_sort_algorithm(
    std::vector<Pillar> array) {
  std::vector<std::vector<Pillar>> animation;
  animation.push_back(array);

  for (int i = 0; i < array.size() - 1; i++) {
    for (int j = 0; j < array.size() - 1 - i; j++) {
      if (array.at(j)._value > array.at(j + 1)._value) {
        std::swap(array.at(j)._value, array.at(j + 1)._value);

        // Add the frame to the animation
        animation.push_back(array);
        // Change the colors
        animation.at(animation.size() - 1)
            .at(array.size() - 1 - i)
            .change_state(SELECTED);
        animation.at(animation.size() - 1).at(j).change_state(MOVED);
        animation.at(animation.size() - 1).at(j + 1).change_state(MOVED);
      } else {
        // Add the frame to the animation
        animation.push_back(array);
        // Change the colors
        animation.at(animation.size() - 1)
            .at(array.size() - 1 - i)
            .change_state(SELECTED);
        animation.at(animation.size() - 1).at(j).change_state(SELECTED);
        animation.at(animation.size() - 1).at(j + 1).change_state(SELECTED);
      }
    }
  }

  std::vector<std::vector<Pillar>> temp_vec = draw_result_animation(array);
  animation.insert(animation.end(), temp_vec.begin(), temp_vec.end());

  animation.push_back(array);

  return animation;
}
