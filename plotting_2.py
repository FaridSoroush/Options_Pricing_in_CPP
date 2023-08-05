import pandas as pd
import matplotlib.pyplot as plt

# Load the price paths
df = pd.read_csv('path.csv', header=None)

# Plot the price paths with transparency
for i in range(len(df)):
    plt.plot(df.loc[i], label=f'Path {i+1}', alpha=0.4) # 'alpha=0.1' makes the lines semi-transparent

plt.title('Price Paths from Monte Carlo Simulation')
plt.xlabel('Time Step')
plt.ylabel('Price')
plt.show()
