#include <iostream>
#include <cmath>
#include <random>
#include <fstream> // for file operations

// Open file for writing
std::ofstream gbmFile("gbm_results.csv");
std::ofstream hestonFile("heston_results.csv");
std::ofstream gbmPathFile("gbm_path.csv");
std::ofstream hestonPathFile("heston_path.csv");

// Parameters for the Geometric Brownian Motion
double S0 = 100.0;  // Initial price 
double K = 100.0;   // Strike price
double r = 0.05;    // Risk-free rate
double T = 1.0;     // One year until expiry
double sigma = 0.2; // Volatility
int M = 50;         // Number of time steps
int N = 10000;      // Number of simulations

// Parameters for the Heston model
double v0 = 0.06; // initial variance
double kappa = 2.0; // rate of reversion
double theta = 0.02; // long-run variance
double xi = 0.1; // volatility of volatility
double rho = -0.7; // correlation coefficient

// Function for the Geometric Brownian Motion
double GBM(double S0, double r, double sigma, double Z, double T) {
    return S0 * exp((r - 0.5 * sigma * sigma) * T + sigma * sqrt(T) * Z);
}

// Function for the Heston model
double Heston(double S0, double v0, double r, double rho, double kappa, double theta, double xi, double W1, double W2, double T) {
    double v = std::max(0.0, v0 + kappa * (theta - v0) * T + xi * sqrt(v0) * sqrt(T) * W1);
    return S0 * exp((r - 0.5 * v) * T + sqrt(v) * sqrt(T) * W2);
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

    // Open file for writing
    std::ofstream file("simulation_results.csv");
    std::ofstream pathfile("path.csv");

    // Monte Carlo Simulations
    for(int i=0; i<N; ++i){
        double S_gbm = S0;
        double S_heston = S0;

        for(int j=0; j<M; ++j){
            double Z1 = distribution(generator);
            double Z2 = rho * Z1 + sqrt(1 - rho*rho) * distribution(generator); // generate two correlated standard normal random variables

            // use GBM model
            S_gbm = GBM(S_gbm, r, sigma, Z1, dt);

            // use Heston model
            S_heston = Heston(S_heston, v0, r, rho, kappa, theta, xi, Z1, Z2, dt);

            gbmPathFile << S_gbm; // write price at this time step for GBM
            hestonPathFile << S_heston; // write price at this time step for Heston

            if (j != M-1) {
                gbmPathFile << ","; // add a comma except for the last item
                hestonPathFile << ","; // add a comma except for the last item
            }
        }
        gbmPathFile << "\n"; // start a new line for each path
        hestonPathFile << "\n"; // start a new line for each path

        sum_payoff += payoff(S_gbm, K); // let's assume the payoff is based on GBM

        // Write final price for this simulation to file
        gbmFile << S_gbm << "\n";
        hestonFile << S_heston << "\n";
    }

    gbmFile.close();
    hestonFile.close();
    gbmPathFile.close();
    hestonPathFile.close();

    // Calculate option price
    double option_price = exp(-r * T) * (sum_payoff / N);

    std::cout << "European Option Price: " << option_price << std::endl;

    return 0;
}
