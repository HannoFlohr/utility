#ifndef STATISTICSSTUFF_H_
#define STATISTICSSTUFF_H_

#include <algorithm>
#include <cmath>
#include <cassert>
#include <map>
#include <vector>

//euler number 
# define M_PI 3.141592653589793238462643383279502884L /* pi */
const double EulerConstant = exp(1.0);

//returns the mean of the values in the input vector v
double mean(const std::vector<double> &v) {
	double m = 0.0;
	for (int i = 0; i < v.size(); i++)
		m += v[i];
	return m/(double)(v.size());
}

//returns the standard deviation for the values in the input vector v
double standardDeviation(const std::vector<double> &v, const double &mean) {
	double stdDev = 0;
	for (int i = 0; i < v.size(); i++)
		stdDev += (double)pow(v[i] - mean, 2);
	stdDev /= (double)(v.size());
	stdDev = sqrt(stdDev);
	return stdDev;
}

//returns the faculty of the input n
unsigned long long int faculty(const unsigned long long int &n) {
	if (n == 1 || n == 0) return n;
	else return n * faculty(n - 1);
}

//a precise estimate for the faculty of n (useful for high n)
double facultyEstimate(unsigned int n) {
	return sqrt(2 * M_PI * n) * pow(n / EulerConstant, n) * (1 + (1 / (12 * n)) + (1 / (n*n)));
}

//returns the binomial coefficient for n over k
unsigned long long int binomialCoefficientRec(const unsigned long long int &n, const unsigned long long int &k) {
	if (k == 0) return 1;
	else if (k > n) return 0;
	else
		return binomialCoefficientRec(n - 1, k - 1) + binomialCoefficientRec(n - 1, k);
}

//returns the binomial coefficient for n over k 
unsigned long long int binomialCoefficient(const unsigned long long int &n, const unsigned long long int &k) {
	assert(n >= k && k >= 0);
	unsigned long long int binom = 1LL;
	if (k > n / 2) k = n - k;
	for (int i = 0; i < k; i++) binom = binom * (n - i) / (i + 1LL);
	return binom;
}

//computes a lower and upper estimate for the order of the binomialcoefficient n over k, useful for higher n,k
void estimateBinom(const unsigned long long int &n, const unsigned long long int &k, double &lower, double &upper) {
	lower = pow(((double)(n / k)), k);
	upper = pow((EulerConstant*((double)(n / k))), k);
}

//returns the dinomial distribution for n over k with probability p
double binomialDistribution(const unsigned long long int &n, const unsigned long long int &k, const double &p) {
	return (double)(binomialCoefficient(n, k)) * pow(p, k) * pow(1 - p, n - k);
}

//returns the geometric distribution g(n,p) =  q^(n-1) * p (first success after n-1 failures)
double geometricDistribution(const unsigned long long int &n, double &p) {
	return pow(1 - p, n - 1) * p;
}

//returns the poisson distribution p(k,lambda) = lambda^k * e^-lambda / k! 
//(the probability of getting exactly k successes when the average number of successes is lamba)
double poissonDistribution(const double &lambda, const unsigned long long int &k) {
	return pow(lambda, k) * pow(EulerConstant, (-1 * lambda)) / (double)faculty(k);
}

//returns the poisson distribution for E[X^2] (E[X]=lambda is expectation of X)
double poissonDistributionEofX2(const double& lambda) {
	return lambda + pow(lambda, 2);
}

//returns the normal distribution for mean mu and standard deviation sigma for x 
double normalDistribution(const double &mu, const double &sigma, const double &x) {
	double result = 1.0 / (sigma * sqrt(2.0 * M_PI));
	double exp = -1.0 * pow(x - mu, 2) / (2.0 * sigma *sigma);
	return pow(result, exp);
}

//returns the cumulative normal distribution for [0,x]
double cumulativeNormalDistribution(const double &mu, const double &sigma, const double &x) {
	return 0.5 * (1.0 + erf((x - mu) / (sigma * sqrt(2))));
}

//returns the pearson correlation coefficient for the two input vectors
double pearsonCorrelationCoefficient(const std::vector<double> &x, const std::vector<double> &y) {
	assert(x.size() == y.size());
	int n = x.size();
	double meanX = mean(x);
	double meanY = mean(y);

	double sum = 0;
	for (int i = 0; i < n; i++)
		sum += (x[i] - meanX) * (y[i] - meanY);

	return sum / (n * standardDeviation(x, meanX) * standardDeviation(y, meanY));
}

//returns the spearman rank correlation coefficient for the two input vectors x and y
//setRanks as helper function
std::vector<int> setRanks(const std::vector<double> &v) {
	std::vector<double> sorted = v;
	sort(sorted.begin(), sorted.end());

	std::map<double, int> m;
	for (int i = 0; i < v.size(); i++)
		m[sorted[i]] = i + 1;

	std::vector<int> ranks(v.size());
	for (int i = 0; i < v.size(); i++)
		ranks[i] = m[v[i]];
	return ranks;
}
double spearmanRankCorrelationCoefficient(const std::vector<double> &x, const std::vector<double> &y) {
	assert(x.size() == y.size());
	int n = x.size();
	std::vector<int> ranksX = setRanks(x);
	std::vector<int> ranksY = setRanks(y);

	std::vector<int> d(n);
	for (int i = 0; i < n; i++) {
		d[i] = ranksX[i] - ranksY[i];
		d[i] *= d[i];
	}

	double result = 0;
	for (int i = 0; i < n; i++)
		result += d[i];
	result = 6.0 * result / (n * ((n*n) - 1));
	return 1.0 - result;
}

#endif