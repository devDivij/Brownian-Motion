# Brownian Motion Simulations

C++ implementations of classical Brownian motion processes and variants for stochastic simulation in finance, physics, and Monte Carlo methods. Includes a Python script for visualizing generated paths.

## Processes Implemented

### 1. **Random Walk (Arithmetic Brownian Motion)**

The random walk provides a simple discrete approximation to a standard Wiener process (Brownian motion), extended here to arithmetic Brownian motion with drift.

**Stochastic Differential Equation (SDE):**

$$ dX(t) = \mu \, dt + \sigma \, dW(t) $$

- $\mu$ (drift): Constant drift term.
- $\sigma$ (diffusion coefficient): Volatility scaling the Wiener increment.
- $W(t)$: Standard Wiener process.

**Simulation Method:**
Direct incremental construction using independent Gaussian increments (Euler discretization of the Wiener process):

$$ W_t = W_{t-1} + \sqrt{\Delta t} \, Z $$

$$ X_t = \mu t + \sigma \, W_t $$

where $Z \sim \mathcal{N}(0,1)$, $\Delta t = 1/n$, and $W_0 = 0$. Results are saved to `plot.csv`.

---

### 2. **Geometric Brownian Motion**

Geometric Brownian motion is the continuous-time limit of a multiplicative random walk, widely used to model asset prices (e.g., stock prices under Black-Scholes).

**Stochastic Differential Equation (SDE):**

$$ dS(t) = \mu S(t) \, dt + \sigma S(t) \, dW(t) $$

**Exact Transition Formula:**
The code implements the closed-form solution over each time step (log-Euler scheme, which is exact for GBM):

$$ S_i = S_{i-1} \exp\left( \left( \mu - \frac{\sigma^2}{2} \right) \Delta t + \sigma \sqrt{\Delta t} \, Z_{i-1} \right) $$

Results are saved to `plot.csv`.

---

### 3. **Brownian Bridge**

A Brownian bridge is a Wiener process conditioned to start and end at fixed points (typically $B(0)=0$ and $B(T)=x$). It is essential for path-dependent option pricing and conditioned simulations.

**Stochastic Differential Equation (SDE):**
Same as standard Brownian motion ($dB(t) = \sigma \, dW(t)$), but subject to boundary conditions $B(0)=0$, $B(T)=x$.

**Implementation Method:**
Dyadic (power-of-2) hierarchical construction for efficient path generation:
- Number of steps = $2^n$ for refined resolution.
- Incremental Gaussian sampling combined with bridge conditioning to enforce the endpoint.
- The construction fills intermediate points recursively while preserving the correct joint distribution.

Results are saved to `plot.csv`.

---

### 4. **Principal Components (Karhunen-Loève) Approximation of Brownian Motion**

This method approximates Brownian motion paths using the first $k$ principal components (eigenfunctions) of the covariance operator — a low-rank representation that reduces dimensionality while retaining accuracy.

**Stochastic Differential Equation (SDE):**

$$ dX(t) = \mu \, dt + \sigma \, dW(t) $$

**Eigen-decomposition (discrete sine basis):**

Eigenvalues:

$$ \lambda_i = \frac{\Delta t}{4 \sin^2 \left( \frac{(2i+1)\pi}{2(2n+1)} \right)} $$

Eigenvectors:

$$ v_{j,i} = \frac{2 \sin \left( \frac{(2i+1)(j+1)\pi}{2n+1} \right)}{\sqrt{2n+1}} $$

**Simulation Formula:**

$$ W_j \approx \sum_{i=0}^{k-1} \sqrt{\lambda_i} \, v_{j,i} \, Z_i $$

$$ X_j = \mu \cdot j \Delta t + \sigma \, W_j $$

where $Z_i \sim \mathcal{N}(0,1)$. This PCA truncation enables fast, low-dimensional Monte Carlo paths. Results are saved to `plot.csv`.

## Usage

1. Compile any `.cpp` file (e.g., `g++ geometric_brownian_motion.cpp -o gbm`).
2. Run the executable to generate `plot.csv`.
3. Run `python plot.py` to visualize the simulated path.