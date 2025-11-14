#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;

class Vector3D {
public:
    double x, y, z;

    void set(double a, double b, double c) {
        x = a;
        y = b;
        z = c;
    }

    double magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }

    Vector3D normalize() {
        double mag = magnitude();
        if (mag == 0) return *this;

        Vector3D result{};
        result.set(x / mag, y / mag, z / mag);
        return result;
    }

    double dotProduct(const Vector3D &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3D sum(const Vector3D &other) const {
        Vector3D result{};
        result.set(x + other.x, y + other.y, z + other.z);
        return result;
    }

    Vector3D subtract(const Vector3D &other) const {
        Vector3D result{};
        result.set(x - other.x, y - other.y, z - other.z);
        return result;
    }

    Vector3D multiply(double scalar) const {
        Vector3D result{};
        result.set(x * scalar, y * scalar, z * scalar);
        return result;
    }

    string toString() const {
        ostringstream oss;
        oss << "(" << x << ", " << y << ", " << z << ")";
        return oss.str();
    }
};

class CelestialBody {
public:
    string name;
    double mass{};
    Vector3D position{};
    Vector3D velocity{};
    Vector3D acceleration{};

    void set(string n, double m, Vector3D p, Vector3D v) {
        name = std::move(n);
        mass = m;
        position = p;
        velocity = v;
        acceleration.set(0, 0, 0);
    }

    string toString() const {
        std::ostringstream oss;
        oss << "Name: " << name << "\n";
        oss << "Mass: " << mass << " kg\n";
        oss << "Position: " << position.toString() << "\n";
        oss << "Velocity: " << velocity.toString() << "\n";
        oss << "Acceleration: " << acceleration.toString() << "\n";
        return oss.str();
    }

    void computeAccelerationFrom(const CelestialBody &other) {
        Vector3D r = other.position.subtract(position);
        Vector3D unit = r.normalize();
        double distance = r.magnitude();
        if (distance == 0) {
            acceleration.set(0, 0, 0);
            return;
        }

        const double G = 6.67430e-11;
        double scalar = G * other.mass / (distance * distance);
        acceleration = unit.multiply(scalar);
    }

    void updateVelocityAndPosition(double dt) {
        velocity = velocity.sum(acceleration.multiply(dt));
        position = position.sum(velocity.multiply(dt));
    }
};

void simulateSystem(vector<CelestialBody> &bodies, double dt, int totalSteps) {
    ofstream outfile("simulation_output.csv");
    outfile << "Day,Body,PosX,PosY,PosZ,VelX,VelY,VelZ,AccX,AccY,AccZ\n";

    for (int step = 0; step < totalSteps; step++) {
        double currentDay = step * dt / 86400.0;

        for (auto &body: bodies) {
            body.acceleration.set(0, 0, 0);
        }
        for (int i = 0; i < bodies.size(); i++) {
            for (int j = 0; j < bodies.size(); j++) {
                if (i == j) continue;
                Vector3D r = bodies[j].position.subtract(bodies[i].position);
                double distance = r.magnitude();
                if (distance == 0) continue;

                Vector3D unit = r.normalize();
                double G = 6.67430e-11;
                double scalar = G * bodies[j].mass / (distance * distance);
                bodies[i].acceleration = bodies[i].acceleration.sum(unit.multiply(scalar));
            }
        }

        for (auto &body: bodies) {
            body.updateVelocityAndPosition(dt);
        }

        cout << "Day " << currentDay + 0.25 << ":\n";
        for (const auto &body: bodies) {
            cout << body.name << ": " << body.position.toString() << "\n";

            outfile << currentDay + 0.25 << "," << body.name << ","
                    << body.position.x << "," << body.position.y << "," << body.position.z << ","
                    << body.velocity.x << "," << body.velocity.y << "," << body.velocity.z << ","
                    << body.acceleration.x << "," << body.acceleration.y << "," << body.acceleration.z
                    << "\n";
        }
    }

    outfile.close();
}


int main() {
    vector<CelestialBody> bodies;

    CelestialBody sun;
    sun.set("Sun", 1.989e30, Vector3D{0, 0, 0}, Vector3D{0, 0, 0});
    bodies.push_back(sun);

    CelestialBody mercury;
    mercury.set("Mercury", 3.285e23, Vector3D{5.79e10, 0, 0}, Vector3D{0, 47870, 0});
    bodies.push_back(mercury);

    CelestialBody venus;
    venus.set("Venus", 4.867e24, Vector3D{1.082e11, 0, 0}, Vector3D{0, 35020, 0});
    bodies.push_back(venus);

    CelestialBody earth;
    earth.set("Earth", 5.972e24, Vector3D{1.496e11, 0, 0}, Vector3D{0, 29780, 0});
    bodies.push_back(earth);

    CelestialBody mars;
    mars.set("Mars", 6.417e23, Vector3D{2.279e11, 0, 0}, Vector3D{0, 24070, 0});
    bodies.push_back(mars);

    CelestialBody jupiter;
    jupiter.set("Jupiter", 1.898e27, Vector3D{7.785e11, 0, 0}, Vector3D{0, 13070, 0});
    bodies.push_back(jupiter);

    CelestialBody saturn;
    saturn.set("Saturn", 5.683e26, Vector3D{1.433e12, 0, 0}, Vector3D{0, 9680, 0});
    bodies.push_back(saturn);

    CelestialBody uranus;
    uranus.set("Uranus", 8.681e25, Vector3D{2.877e12, 0, 0}, Vector3D{0, 6800, 0});
    bodies.push_back(uranus);

    CelestialBody neptune;
    neptune.set("Neptune", 1.024e26, Vector3D{4.503e12, 0, 0}, Vector3D{0, 5430, 0});
    bodies.push_back(neptune);
    int day = 365;
    double dt = 86400.0 / 4;
    int totalSteps = day * 4;
    simulateSystem(bodies, dt, totalSteps);

#ifdef _WIN32
    system("python plot_distances.py");
#else
    system("python3 plot_distances.py > /dev/null 2>&1");
#endif

}
