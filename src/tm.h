#include <vector>


struct CompressionResultsData
{
  std::vector <unsigned int> amplitudeResults;
  std::vector <double> normalizedCompressionResults;
  std::vector <double> selfCompressionResults;
};

/** Evaluate all relative turing machine programs with the given architecture.
 *
 * @param states
 * @param alphabet_size
 * @param num_iterations
 * @param k
 * @param verbose
 * @return a vector of normalized compression values, one per turing machine
 */
CompressionResultsData tm(
    size_t states,
    size_t alphabet_size,
    unsigned int num_iterations,
    unsigned int k,
    bool verbose);
