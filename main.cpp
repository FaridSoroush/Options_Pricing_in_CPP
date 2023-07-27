#include <iostream>
#include <cmath>
#include <random>

// Parameters for the Geometric Brownian Motion
double S0 = 100.0;  // Initial price 
double K = 100.0;   // Strike price
double r = 0.05;    // Risk-free rate
double T = 1.0;     // One year until expiry
double sigma = 0.2; // Volatility
int M = 50;         // Number of time steps
int N = 10000;      // Number of simulations

// Function for the Geometric Brownian Motion
double GBM(double S0, double r, double sigma, double Z, double T) {
    return S0 * exp((r - 0.5 * sigma * sigma) * T + sigma * sqrt(T) * Z);
}

// Function for payoff of European Call Option
double payoff(double S, double K) {
    return std::max(S - K, 0.0);
}

int main() {
    // Random number generator
    std::mt19937 generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    double dt = T / M; // time step
    double sum_payoff = 0.0;

    // Monte Carlo Simulations
    for(int i=0; i<N; ++i){
        double S = S0;
        for(int j=0; j<M; ++j){
            double Z = distribution(generator);
            S = GBM(S, r, sigma, Z, dt);
        }
        sum_payoff += payoff(S, K);
    }

    // Calculate option price
    double option_price = exp(-r * T) * (sum_payoff / N);

    std::cout << "European Option Price: " << option_price << std::endl;

    return 0;
}
