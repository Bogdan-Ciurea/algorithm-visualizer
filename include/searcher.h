#ifndef SEARCHER_H
#define SEARCHER_H

#include "algirithm_interface.h"
#include "standalone-functions/search-algorithms.h"

class Searcher : public AlgorithmInterface {
 public:
  Searcher() {
    inter_regular = LoadFontEx("assets/inter-regular.ttf", 20, 0, 0);
  }
  ~Searcher() {
    UnloadFont(inter_regular);
  }

  bool draw();
};

#endif