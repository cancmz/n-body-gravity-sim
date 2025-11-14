# N-Body Gravitational Simulator

This project is a general-purpose gravitational N-body simulator written in C++. It models the motion of multiple celestial bodies under mutual gravitational forces using Newtonian mechanics. You can simulate any configuration of stars, planets, moons, asteroids, or other masses by simply adjusting their initial properties.

## Overview

The simulator numerically computes the positions, velocities, and accelerations of all bodies over time, based on their mass and initial state. The simulation evolves using the **Euler integration method**, suitable for studying gravitational interactions, orbital dynamics, and large-scale system evolution.

The results are written to a CSV file and can be visualized using a Python plotting script.

## Scientific Context

This simulation is based on Newton's law of universal gravitation:

**F = G · (m₁ · m₂) / r²**

For each body, the net gravitational force from all other bodies is used to compute acceleration:

- **a = F / m**  
- **v(t + Δt) = v(t) + a · Δt**  
- **x(t + Δt) = x(t) + v · Δt**

To enhance stability, each simulated day is divided into four equal parts (Δt = 6 hours = 21600 seconds). At every step:

- All gravitational accelerations are recalculated.
- Each body’s velocity is updated using its current acceleration and the time step.
- The new velocity is then used to update its position.

This simulation uses the **Euler integration method**, a first-order numerical technique that uses the previous step’s state to iteratively evolve the system. While basic, it provides sufficient accuracy for many educational and conceptual simulations.

## Features

- Simulate any number of bodies (configurable in code)
- Realistic mutual gravitational interactions between all bodies
- Modular class-based C++ structure (`Vector3D`, `CelestialBody`)
- Outputs high-resolution CSV data at every step
- Console prints and CSV export for analysis or plotting
- Cross-platform compatible

## Files

| File                  | Description                                          |
|-----------------------|------------------------------------------------------|
| `main.cpp`            | Main simulation program in C++                       |
| `simulation_output.csv` | Output file logging position, velocity, acceleration |
| `plot_distances.py`   | Optional Python script for plotting distances        |

## Simulation Parameters

| Parameter   | Description                                    | Example Value      |
|-------------|------------------------------------------------|--------------------|
| `dt`        | Time step in seconds (e.g., 24 hours)           | 86400              |
| `days`      | Number of simulated days                       | 365                |
| `bodies`    | Number of celestial bodies                     | 2 or more          |
| `G`         | Gravitational constant                         | 6.67430 × 10⁻¹¹    |

You can configure the number of bodies and their properties (name, mass, position, velocity) directly in the `main()` function.

## How to Run

Make sure you have the required library:

```bash
pip install matplotlib
```

Then execute the simulation:

```bash
python tracker_sim.py
```

This will generate a high-resolution plot in the `planet_distance_graphs/` folder with a timestamped filename.

## Example Output

Each step of the simulation logs detailed information to the file `simulation_output.csv`. The data structure is as follows:

- **Day number**: Simulation time in days (with sub-day precision)
- **Body name**: Identifier of the celestial object
- **Position (x, y, z)**: Current spatial coordinates in meters
- **Velocity (x, y, z)**: Current velocity components in meters per second
- **Acceleration (x, y, z)**: Current acceleration components in meters per second squared

### These outputs can be used to:

- **Plot distance vs. time** for any body relative to a reference (e.g., the origin or another body)
- **Visualize 2D trajectories** of celestial bodies in space
- **Analyze orbital properties** such as period, eccentricity, or stability over time

### Sample CSV Row

```csv
1,Earth,1.49556e+11,2.57299e+09,0,-512.496,29780,0,-0.00593167,0,0
```
## Author

**Ahmet Can Çömez**  
Computer Engineering Student  
