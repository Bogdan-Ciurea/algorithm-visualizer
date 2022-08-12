#ifndef TREES_H
#define TREES_H

#include "algirithm_interface.h"
#include "standalone-functions/trees-algorithms.h"

class Trees : public AlgorithmInterface {
 public:
  Trees() {}
  ~Trees() {}

  bool draw();
};

#endif