#include "standalone-functions/search-algorithms.h"

std::vector<std::vector<Pillar>> draw_error_animation(
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

std::vector<std::vector<Pillar>> draw_success_animation(
    std::vector<Pillar> array, int target) {
  std::vector<std::vector<Pillar>> x;

  for (int i = 0; i < 3; i++) {
    x.push_back(array);
    x.at(x.size() - 1).at(target).change_state(NORMAL);

    x.push_back(array);
    x.at(x.size() - 1).at(target).change_state(MOVED);
  }

  return x;
}

std::vector<std::vector<Pillar>> search_linear_algo(std::vector<Pillar> array,
                                                    int target) {
  std::vector<std::vector<Pillar>> animation;

  animation.push_back(array);
  bool was_found = false;

  for (int i = 0; i < array.size(); i++) {
    animation.push_back(array);
    animation.at(animation.size() - 1).at(i).change_state(MOVED);

    if (array.at(i)._value == target) {
      was_found = true;
      std::vector<std::vector<Pillar>> temp = draw_success_animation(array, i);
      animation.insert(animation.end(), temp.begin(), temp.end());
      break;
    }
  }

  if (!was_found) {
    std::vector<std::vector<Pillar>> temp = draw_error_animation(array);
    animation.insert(animation.end(), temp.begin(), temp.end());
  }

  animation.push_back(array);

  return animation;
}

std::vector<std::vector<Pillar>> search_binary_algo(std::vector<Pillar> array,
                                                    int target) {
  std::vector<std::vector<Pillar>> animation;

  animation.push_back(array);
  bool was_found = false;
  int mid;
  int low = 0;
  int high = array.size() - 1;

  while (low <= high) {
    mid = (low + high) / 2;

    // Draw the high, mid and low positions
    for (int j = 0; j < 3; j++) {
      animation.push_back(array);
      animation.at(animation.size() - 1).at(high).change_state(SELECTED);
      animation.at(animation.size() - 1).at(mid).change_state(SELECTED);
      animation.at(animation.size() - 1).at(low).change_state(SELECTED);
    }

    if (target == array.at(mid)._value) {
      was_found = true;
      std::vector<std::vector<Pillar>> temp =
          draw_success_animation(array, mid);
      animation.insert(animation.end(), temp.begin(), temp.end());
      break;
    }

    if (target > array.at(mid)._value)
      low = mid + 1;
    else
      high = mid - 1;
  }

  if (!was_found) {
    std::vector<std::vector<Pillar>> temp = draw_error_animation(array);
    animation.insert(animation.end(), temp.begin(), temp.end());
  }

  animation.push_back(array);

  return animation;
}

std::vector<std::vector<Pillar>> search_jump_algo(std::vector<Pillar> array,
                                                  int target) {
  std::vector<std::vector<Pillar>> animation;

  animation.push_back(array);
  bool was_found = false;

  int step = sqrt(array.size());

  int prev = 0;
  while (array.at(MIN(array.size(), step) - 1)._value < target) {
    // Draw the current position
    animation.push_back(array);
    animation.at(animation.size() - 1).at(prev).change_state(MOVED);

    prev = step;
    step += sqrt(array.size());
  }

  while (array.at(prev)._value < target && prev != MIN(step, array.size())) {
    prev++;

    // Draw the current position
    animation.push_back(array);
    animation.at(animation.size() - 1).at(prev).change_state(MOVED);
  }

  if (array.at(prev)._value == target) {
    std::vector<std::vector<Pillar>> temp = draw_success_animation(array, prev);
    animation.insert(animation.end(), temp.begin(), temp.end());
    was_found = true;
  }

  if (!was_found) {
    std::vector<std::vector<Pillar>> temp = draw_error_animation(array);
    animation.insert(animation.end(), temp.begin(), temp.end());
  }

  animation.push_back(array);

  return animation;
}

std::vector<std::vector<Pillar>> search_interpolation_algo(
    std::vector<Pillar> array, int target) {
  std::vector<std::vector<Pillar>> animation;

  animation.push_back(array);
  bool was_found = false;

  int low = 0;
  int high = array.size() - 1;
  int mid;
  int index = -1;

  while (low <= high) {
    mid = low + (((double)(high - low) /
                  (array.at(high)._value - array.at(low)._value)) *
                 (target - array.at(low)._value));

    animation.push_back(array);
    animation.at(animation.size() - 1).at(mid).change_state(MOVED);

    if (array.at(mid)._value == target) {
      index = mid;

      std::vector<std::vector<Pillar>> temp =
          draw_success_animation(array, mid);
      animation.insert(animation.end(), temp.begin(), temp.end());
      was_found = true;
      break;
    } else {
      if (array.at(mid)._value < target)
        low = mid + 1;
      else
        high = mid - 1;
    }
  }

  if (!was_found) {
    std::vector<std::vector<Pillar>> temp = draw_error_animation(array);
    animation.insert(animation.end(), temp.begin(), temp.end());
  }

  animation.push_back(array);

  return animation;
}