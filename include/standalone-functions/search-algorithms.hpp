#ifndef SEARCH_ALGORITHMS_HPP
#define SEARCH_ALGORITHMS_HPP

#include "../pillar-objects.hpp"

std::vector<std::vector<Pillar>> search_linear_algo(std::vector<Pillar> array,
                                                    int target);

std::vector<std::vector<Pillar>> search_binary_algo(std::vector<Pillar> array,
                                                    int target);

std::vector<std::vector<Pillar>> search_jump_algo(std::vector<Pillar> array,
                                                  int target);

std::vector<std::vector<Pillar>> search_interpolation_algo(
    std::vector<Pillar> array, int target);

#endif  // SEARCH_ALGORITHMS_HPP