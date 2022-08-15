#ifndef TREES_H
#define TREES_H

#include "algirithm_interface.h"
#include "standalone-functions/trees-algorithms.h"

class Trees : public AlgorithmInterface {
 public:
  Trees() { inter_regular = LoadFontEx("assets/inter-regular.ttf", 20, 0, 0); }
  ~Trees() { }

  bool draw();

private:
  void draw_header();
};

#endif