import pandas as pd
import matplotlib.pyplot as plt
import os

csv_path = "simulation_output.csv"
df = pd.read_csv(csv_path)

sun_df = df[df["Body"] == "Sun"].reset_index(drop=True)
planet_names = [name for name in df["Body"].unique() if name != "Sun"]

distance_folder = "planet_distance_graphs"
orbit_folder = "planet_orbits"
os.makedirs(distance_folder, exist_ok=True)
os.makedirs(orbit_folder, exist_ok=True)

plt.rcParams.update({
    "font.family": "sans-serif",
    "font.size": 14,
    "axes.titlesize": 16,
    "axes.labelsize": 14,
    "xtick.labelsize": 12,
    "ytick.labelsize": 12
})

for planet in planet_names:
    planet_df = df[df["Body"] == planet].reset_index(drop=True)

    distances = ((planet_df["PosX"] - sun_df["PosX"]) ** 2 +
                 (planet_df["PosY"] - sun_df["PosY"]) ** 2 +
                 (planet_df["PosZ"] - sun_df["PosZ"]) ** 2) ** 0.5

    min_d = distances.min()
    max_d = distances.max()
    padding = (max_d - min_d) * 0.01

    plt.figure(figsize=(12, 6), dpi=300)
    plt.plot(planet_df["Day"], distances, linewidth=2)
    plt.title(f"{planet} - Distance to the Sun Over Time")
    plt.xlabel("Day")
    plt.ylabel("Distance (m)")
    plt.grid(True, linestyle="--", alpha=0.7)
    ax = plt.gca()
    ax.ticklabel_format(style='sci', axis='y', scilimits=(11, 11))
    ax.set_ylim(min_d - padding, max_d + padding)
    plt.tight_layout()
    plt.savefig(f"{distance_folder}/{planet}_distance_to_sun.png", dpi=300)
    plt.close()

    plt.figure(figsize=(8, 8), dpi=300)
    plt.plot(planet_df["PosX"], planet_df["PosY"], label=planet, linewidth=1.5)
    plt.plot(sun_df["PosX"], sun_df["PosY"], 'o', color='orange', label='Sun', markersize=8)
    plt.title(f"{planet} - 2D Orbital Path (XY Plane)")
    plt.xlabel("X Position (m)")
    plt.ylabel("Y Position (m)")
    plt.grid(True, linestyle="--", alpha=0.6)
    plt.legend()
    plt.axis('equal')
    plt.tight_layout()
    plt.savefig(f"{orbit_folder}/{planet}_orbit_xy.png", dpi=300)
    plt.close()

plt.figure(figsize=(10, 10), dpi=300)

for planet in planet_names:
    planet_df = df[df["Body"] == planet]
    plt.plot(planet_df["PosX"], planet_df["PosY"], label=planet, linewidth=1.2)

plt.plot(sun_df["PosX"], sun_df["PosY"], 'o', color='orange', label='Sun', markersize=10)
plt.title("All Bodies - 2D Orbital Paths (XY Plane)")
plt.xlabel("X Position (m)")
plt.ylabel("Y Position (m)")
plt.grid(True, linestyle="--", alpha=0.6)
plt.legend(loc="upper right")
plt.axis('equal')
plt.tight_layout()
plt.savefig(f"{orbit_folder}/all_orbits_xy.png", dpi=300)
plt.close()

print("All graphs saved successfully.")
