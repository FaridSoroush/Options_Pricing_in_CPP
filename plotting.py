import pandas as pd
import matplotlib.pyplot as plt

# Load the data
df = pd.read_csv('simulation_results.csv', header=None, names=['Final Price'])

# Plot a histogram
plt.hist(df['Final Price'], bins=50, edgecolor='black')
plt.title('Histogram of Final Prices from Monte Carlo Simulation')
plt.xlabel('Final Price')
plt.ylabel('Frequency')
plt.show()
