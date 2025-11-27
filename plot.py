import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("plot.csv", header=None, names=["t","W"])

plt.plot(df.t, df.W)
plt.title("Brownian Motion")
plt.xlabel("Time step")
plt.ylabel("W(t)")
plt.show()
