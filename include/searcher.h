#ifndef SEARCHER_H
#define SEARCHER_H

#include "algirithm_interface.h"
#include "standalone-functions/search-algorithms.h"

class Searcher : public AlgorithmInterface {
 public:
  Searcher() {}
  ~Searcher() {}

  bool draw();
};

#endif