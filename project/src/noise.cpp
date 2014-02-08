#include "noise.h"
#include <boost/random.hpp>

noise::noise()
{
}

double noise::GetRandomNoise(double mean, double sigma)
{
     typedef boost::normal_distribution<double> NormalDistribution;
     typedef boost::mt19937 RandomGenerator;
     typedef boost::variate_generator<RandomGenerator&, \
                             NormalDistribution> GaussianGenerator;

      /** Initiate Random Number generator with current time */
      static RandomGenerator rng(static_cast<unsigned> (time(0)));

      /* Choose Normal Distribution */
      NormalDistribution gaussian_dist(mean, sigma);

      /* Create a Gaussian Random Number generator
       *  by binding with previously defined
       *  normal distribution object
       */
      GaussianGenerator generator(rng, gaussian_dist);

      // sample from the distribution
      return generator();
}
