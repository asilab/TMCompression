#pragma once

/** Enum for defining the strategy of traversal through possible
 * turing machines.
 */ 
enum struct TraversalStrategy {
  /// Sequential traversal, arg #1 indicates how many (all if 0), arg #2 the offset.
  SEQUENTIAL = 0,
  /// Randomly sampled, arg #1 indicates how many (0 is illegal).
  MONTE_CARLO = 1,
};
