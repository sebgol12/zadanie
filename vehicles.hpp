#ifndef VEHICLES_HPP
#include <string>
#include <vector>
#include <functional>

class Vehicle {
public:
    Vehicle(const std::string& id, const std::string& brand): _id(id), _brand(brand) {}
    std::string getId() const {
        return _id;
    }
    std::string getBrand() const {
        return _brand;
    }
    virtual double getMaxSpeed() const = 0;
    virtual ~Vehicle() = default;


private:
    std::string _id;
    std::string _brand;
};

class Car: public Vehicle {
public:
    Car(const std::string& id, const std::string& brand, double engineHP): Vehicle(id, brand), _engineHP(engineHP) {}
    double getMaxSpeed() const override {
        return _engineHP;
    }

private:
    double _engineHP;
};

class Bicycle: public Vehicle {
public:
    Bicycle(const std::string& id, const std::string& brand, int nGears): Vehicle(id, brand), _nGears(nGears) {}
    double getMaxSpeed() const override {
        return 3 * _nGears;
    }
private:
    int _nGears;
};

std::string to_string(const Vehicle& v);
double compute_min_travel_duration(double distance, const Vehicle& vehicle);
std::string compute_min_travel_duration_as_string(double distance, const Vehicle& vehicle);
std::vector<Vehicle*> filter_vehicles(
        std::vector<Vehicle*>::const_iterator vehicles_begin,
        std::vector<Vehicle*>::const_iterator vehicles_end,
        std::function<bool (const Vehicle&)> predicate);


#endif
