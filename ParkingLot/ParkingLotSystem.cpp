#include <bits/stdc++.h>
using namespace std;

class Vehicle
{
private:
    string type;
    int licenseNumber;

public:
    Vehicle() {}

    Vehicle(int licenseNumber, string type)
    {
        this->licenseNumber = licenseNumber;
        this->type = type;
    }

    string getType()
    {
        return type;
    }

    int getLicenseNumber()
    {
        return licenseNumber;
    }
};

class ParkingSpot
{
private:
    int spotId;
    int floorNumber;
    string type;
    optional<Vehicle> vehicle;

public:
    ParkingSpot() {}

    ParkingSpot(int spotId, int floorNumber, string type)
    {
        this->spotId = spotId;
        this->floorNumber = floorNumber;
        this->type = type;
        this->vehicle = nullopt;
    }

    string getType()
    {
        return type;
    }

    int getSpotId()
    {
        return spotId;
    }

    int getFloorNumber()
    {
        return floorNumber;
    }

    void book(Vehicle vehicle)
    {
        this->vehicle = vehicle;
    }

    void release()
    {
        this->vehicle = nullopt;
    }

    bool isAvailable()
    {
        return !vehicle.has_value();
    }
};

class Floor
{
private:
    vector<ParkingSpot> spots;
    int floorNumber;

public:
    Floor() {}

    Floor(int floorNumber)
    {
        this->floorNumber = floorNumber;
    }

    void addSpot(ParkingSpot parkingSpot)
    {
        spots.push_back(parkingSpot);
    }

    ParkingSpot *findAvailableSpot(Vehicle vehicle)
    {
        for (auto &spot : spots)
        {
            if (spot.getType() == vehicle.getType() &&
                spot.isAvailable())
            {
                return &spot;
            }
        }

        return nullptr;
    }
};

class ParkingToken
{
private:
    ParkingSpot *spot;
    Vehicle vehicle;
    string tokenId;

public:
    ParkingToken() {}
    ParkingToken(ParkingSpot *spot, Vehicle vehicle, string tokenId)
    {
        this->spot = spot;
        this->vehicle = vehicle;
        this->tokenId = tokenId;
    }

    ParkingSpot *getSpot()
    {
        return spot;
    }

    string getTokenId()
    {
        return tokenId;
    }
};

class ParkingStrategy
{
public:
    virtual ParkingSpot *findSpot(
        vector<Floor> &floors,
        Vehicle vehicle) = 0;

    virtual ~ParkingStrategy() = default;
};

class NearestFirst : public ParkingStrategy
{
public:
    ParkingSpot *findSpot(
        vector<Floor> &floors,
        Vehicle vehicle) override
    {
        for (auto &floor : floors)
        {
            ParkingSpot *spot =
                floor.findAvailableSpot(vehicle);

            if (spot != nullptr)
                return spot;
        }

        return nullptr;
    }
};

class GenerateTokenId
{
public:
    static string generateToken()
    {
        static const string chars =
            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        static random_device rd;
        static mt19937 gen(rd());
        static uniform_int_distribution<int> dist(
            0, chars.size() - 1);

        string token;

        for (int i = 0; i < 6; i++)
        {
            token += chars[dist(gen)];
        }

        return token;
    }
};

class ParkingLotSystem
{
private:
    vector<Floor> floors;
    ParkingStrategy *strategy;
    map<string, ParkingToken> tokens;

public:
    ParkingLotSystem()
    {
        strategy = nullptr;
    }

    void addFloor(Floor floor)
    {
        floors.push_back(floor);
    }

    void setStrategy(ParkingStrategy *strategy)
    {
        this->strategy = strategy;
    }

    optional<string> park(Vehicle vehicle)
    {
        ParkingSpot *spot =
            strategy->findSpot(floors, vehicle);

        if (spot == nullptr)
            return nullopt;

        spot->book(vehicle);

        string tokenId =
            GenerateTokenId::generateToken();

        ParkingToken token(
            spot,
            vehicle,
            tokenId);

        tokens[tokenId] = token;

        return tokenId;
    }

    bool release(string token)
    {
        auto it = tokens.find(token);

        if (it == tokens.end())
            return false;

        ParkingSpot *spot = it->second.getSpot();

        spot->release();

        tokens.erase(it);

        return true;
    }
};

int main()
{
    ParkingLotSystem parkingLot;

    // Strategy
    NearestFirst strategy;
    parkingLot.setStrategy(&strategy);

    // -------------------------
    // Floor 1
    // -------------------------
    Floor floor1(1);

    floor1.addSpot(ParkingSpot(1, 1, "CAR"));
    floor1.addSpot(ParkingSpot(2, 1, "CAR"));
    floor1.addSpot(ParkingSpot(3, 1, "BIKE"));
    floor1.addSpot(ParkingSpot(4, 1, "TRUCK"));

    // -------------------------
    // Floor 2
    // -------------------------
    Floor floor2(2);

    floor2.addSpot(ParkingSpot(5, 2, "CAR"));
    floor2.addSpot(ParkingSpot(6, 2, "CAR"));
    floor2.addSpot(ParkingSpot(7, 2, "BIKE"));
    floor2.addSpot(ParkingSpot(8, 2, "TRUCK"));

    parkingLot.addFloor(floor1);
    parkingLot.addFloor(floor2);

    // -------------------------
    // Vehicles
    // -------------------------
    Vehicle car1(101, "CAR");
    Vehicle car2(102, "CAR");
    Vehicle bike1(201, "BIKE");
    Vehicle truck1(301, "TRUCK");

    // -------------------------
    // Park vehicles
    // -------------------------

    auto token1 = parkingLot.park(car1);

    if (token1)
        cout << "Car 101 token: "
             << *token1 << '\n';

    auto token2 = parkingLot.park(car2);

    if (token2)
        cout << "Car 102 token: "
             << *token2 << '\n';

    auto token3 = parkingLot.park(bike1);

    if (token3)
        cout << "Bike 201 token: "
             << *token3 << '\n';

    // auto token4 = parkingLot.park(truck1);

    // if (token4)
    //     cout << "Truck 301 token: "
    //          << *token4 << '\n';

    // // -------------------------
    // // Release car1
    // // -------------------------

    // if (token1)
    // {
    //     bool released =
    //         parkingLot.release(*token1);

    //     cout << "Car 101 released: "
    //          << boolalpha << released << '\n';
    // }

    // // Now another car can use
    // // the released spot.

    // Vehicle car3(103, "CAR");

    // auto token5 = parkingLot.park(car3);

    // if (token5)
    //     cout << "Car 103 token: "
    //          << *token5 << '\n';

    return 0;
}