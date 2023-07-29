import pandas as pd
import matplotlib.pyplot as plt
import glob  # to read multiple files

files = glob.glob('path_*.csv')  # get all path files

for i, file in enumerate(files):
    df = pd.read_csv(file, header=None, names=['Price'])

    # Plot the price series for each path
    plt.plot(df['Price'], label=f'Path {i+1}')

plt.title('Price Paths from Monte Carlo Simulation')
plt.xlabel('Time Step')
plt.ylabel('Price')
plt.show()
