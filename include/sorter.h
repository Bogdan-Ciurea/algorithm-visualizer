#ifndef SORTER_H
#define SORTER_H

#include "algorithm.h"

class Sorter{
public:
  Sorter();
  ~Sorter();

  /**
   * @brief Will draw everything to the screen
   * 
   * @param start_height represents the starting height on which we can draw
   */
  void draw(int start_height);

  /**
   * @brief Will add one pillar to the list
   * 
   */
  void add_pillar();

  /**
   * @brief Will remove the last pillar of the list
   * 
   */
  void remove_pillar();

  /**
   * @brief Will randomize the array
   * 
   * @param size represents the size of the desired array
   */
  void randomize(int size);

  /**
   * @brief Will get the number of pillars in the list
   * 
   * @return int the number of pillars in the list
   */
  int get_number_pillars() {
    return pillars.size();
  }

private:
  std::vector<Pillar> pillars;
  int pillar_width;

};

#endif