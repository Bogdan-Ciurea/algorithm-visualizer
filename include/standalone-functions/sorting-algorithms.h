#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include "../pillar-objects.hpp"

std::vector<std::vector<Pillar>> insertion_sort_algorithm(
    std::vector<Pillar> array);

std::vector<std::vector<Pillar>> heap_sort_algorithm(std::vector<Pillar> array);

std::vector<std::vector<Pillar>> selection_sort_algorithm(
    std::vector<Pillar> array);

std::vector<std::vector<Pillar>> merge_sort_algorithm(
    std::vector<Pillar> array);

std::vector<std::vector<Pillar>> quick_sort_algorithm(
    std::vector<Pillar> array);

std::vector<std::vector<Pillar>> bubble_sort_algorithm(
    std::vector<Pillar> array);

#endif