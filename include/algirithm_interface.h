#ifndef ALGORITHM_INTERFACE_H
#define ALGORITHM_INTERFACE_H

class AlgorithmInterface {
 public:
  /**
   * @brief Will update the variables and draw everything on the screen
   *
   * @returns true if we want to exit the interface
   */
  virtual bool draw() { return true; }
};

#endif