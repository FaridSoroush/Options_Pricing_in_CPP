import pandas as pd
import matplotlib.pyplot as plt

# Load simulation results
gbm_results = pd.read_csv('gbm_results.csv', header=None)
heston_results = pd.read_csv('heston_results.csv', header=None)

# Load path results
gbm_paths = pd.read_csv('gbm_path.csv', header=None)
heston_paths = pd.read_csv('heston_path.csv', header=None)

# Plot histograms of the simulation results
plt.figure(figsize=(10, 5))
plt.hist(gbm_results[0], bins=50, alpha=0.5, label='GBM')
plt.hist(heston_results[0], bins=50, alpha=0.5, label='Heston')
plt.title('Simulation Results')
plt.xlabel('Price')
plt.ylabel('Frequency')
plt.legend()
plt.show()

# Plot a few paths
plt.figure(figsize=(10, 5))
for i in range(100):
    plt.plot(gbm_paths.loc[i], alpha=0.7, label='GBM' if i == 0 else None)
    plt.plot(heston_paths.loc[i], alpha=0.7, label='Heston' if i == 0 else None)

plt.title('Simulated Paths')
plt.xlabel('Time Step')
plt.ylabel('Price')
plt.legend()
plt.show()
