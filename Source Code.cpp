#include <bits/stdc++.h>
using namespace std;

class Passenger {
public:
    string id;
    string name;
    string email;

    Passenger(string id, string name, string email)
        : id(id), name(name), email(email) {}
};

class Flight {
public:
    string flightNumber;
    string origin;
    string destination;
    string departureDate;
    string departureTime;
    string arrivalDate;
    string arrivalTime;
    string status; // scheduled, cancelled, completed
    vector<Passenger> passengers;

    // Default constructor
    Flight() : flightNumber(""), origin(""), destination(""), departureDate(""), departureTime(""), arrivalDate(""), arrivalTime(""), status("scheduled") {}

    // Parameterized constructor
    Flight(string flightNumber, string origin, string destination,
           string departureDate, string departureTime, string arrivalDate, string arrivalTime, string status)
        : flightNumber(flightNumber), origin(origin), destination(destination),
          departureDate(departureDate), departureTime(departureTime), arrivalDate(arrivalDate), arrivalTime(arrivalTime), status(status) {}

    void addPassenger(const Passenger& passenger) {
        passengers.push_back(passenger);
    }

    void removePassenger(const string& passengerId) {
        passengers.erase(remove_if(passengers.begin(), passengers.end(),
            [&](Passenger& p) { return p.id == passengerId; }), passengers.end());
    }

    void generatePassengerReport() const {
        cout << "Passengers for flight " << flightNumber << ":\n";
        if (passengers.empty()) {
            cout << "No passengers.\n";
        } else {
            for (const Passenger& passenger : passengers) {
                cout << "ID: " << passenger.id << ", Name: " << passenger.name << ", Email: " << passenger.email << "\n";
            }
        }
    }
};

class AirportManagementSystem {
private:
    unordered_map<string, Flight> flights;

public:
    void addFlight(const Flight& flight) {
        if (flights.find(flight.flightNumber) != flights.end()) {
            cout << "Flight with number " << flight.flightNumber << " already exists.\n";
            return;
        }
        flights[flight.flightNumber] = flight;
        cout << "Added flight " << flight.flightNumber << "\n";
    }

    void updateFlight(const string& flightNumber, const Flight& updatedFlight) {
        auto it = flights.find(flightNumber);
        if (it != flights.end()) {
            it->second = updatedFlight;
            cout << "Updated flight " << flightNumber << "\n";
        } else {
            cout << "Flight with number " << flightNumber << " does not exist.\n";
        }
    }

    void deleteFlight(const string& flightNumber) {
        if (flights.erase(flightNumber) == 0) {
            cout << "Flight with number " << flightNumber << " does not exist.\n";
        } else {
            cout << "Deleted flight " << flightNumber << "\n";
        }
    }

    Flight* getFlight(const string& flightNumber) {
        auto it = flights.find(flightNumber);
        if (it != flights.end()) {
            return &it->second;
        } else {
            cout << "Flight with number " << flightNumber << " not found.\n";
            return nullptr;
        }
    }

    vector<Flight> queryFlightsByStatus(const string& status) {
        vector<Flight> result;
        for (const auto& pair : flights) {
            if (pair.second.status == status) {
                result.push_back(pair.second);
            }
        }
        return result;
    }

    vector<Flight> queryFlightsByDate(const string& date, bool isDeparture) {
        vector<Flight> result;
        for (const auto& pair : flights) {
            if ((isDeparture && pair.second.departureDate == date) || (!isDeparture && pair.second.arrivalDate == date)) {
                result.push_back(pair.second);
            }
        }
        return result;
    }

    void generateReportByStatus(const string& status) {
        vector<Flight> flightsByStatus = queryFlightsByStatus(status);
        cout << "Flights with status " << status << ":\n";
        for (const Flight& flight : flightsByStatus) {
            cout << "Flight Number: " << flight.flightNumber
                      << ", Origin: " << flight.origin
                      << ", Destination: " << flight.destination
                      << ", Departure Date: " << flight.departureDate
                      << ", Departure Time: " << flight.departureTime
                      << ", Arrival Date: " << flight.arrivalDate
                      << ", Arrival Time: " << flight.arrivalTime
                      << "\n";
        }
    }

    void generateReportByDate(const string& date, bool isDeparture) {
        vector<Flight> flightsByDate = queryFlightsByDate(date, isDeparture);
        string dateType = isDeparture ? "Departure" : "Arrival";
        cout << "Flights with " << dateType << " Date " << date << ":\n";
        for (const Flight& flight : flightsByDate) {
            cout << "Flight Number: " << flight.flightNumber
                      << ", Origin: " << flight.origin
                      << ", Destination: " << flight.destination
                      << ", Departure Date: " << flight.departureDate
                      << ", Departure Time: " << flight.departureTime
                      << ", Arrival Date: " << flight.arrivalDate
                      << ", Arrival Time: " << flight.arrivalTime
                      << ", Status: " << flight.status
                      << "\n";
        }
    }

    void generatePassengerReport(const string& flightNumber) {
        Flight* flight = getFlight(flightNumber);
        if (flight != nullptr) {
            flight->generatePassengerReport();
        }
    }
};

int main() {
    AirportManagementSystem ams;
    int choice;

    while (true) {
        cout << "\nAirport Management System\n";
        cout << "1. Add Flight\n";
        cout << "2. Update Flight\n";
        cout << "3. Delete Flight\n";
        cout << "4. Add Passenger to Flight\n";
        cout << "5. Generate Report by Status\n";
        cout << "6. Generate Passenger Report\n";
        cout << "7. Generate Report by Departure Date\n";
        cout << "8. Generate Report by Arrival Date\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character after the integer input

        if (choice == 1) {
            string flightNumber, origin, destination, departureDate, departureTime, arrivalDate, arrivalTime, status;
            cout << "Enter flight number: ";
            getline(cin, flightNumber);
            cout << "Enter origin: ";
            getline(cin, origin);
            cout << "Enter destination: ";
            getline(cin, destination);
            cout << "Enter departure date (YYYY-MM-DD): ";
            getline(cin, departureDate);
            cout << "Enter departure time (HH:MM): ";
            getline(cin, departureTime);
            cout << "Enter arrival date (YYYY-MM-DD): ";
            getline(cin, arrivalDate);
            cout << "Enter arrival time (HH:MM): ";
            getline(cin, arrivalTime);
            cout << "Enter status (scheduled, cancelled, completed): ";
            getline(cin, status);

            Flight flight(flightNumber, origin, destination, departureDate, departureTime, arrivalDate, arrivalTime, status);
            ams.addFlight(flight);
        } else if (choice == 2) {
            string flightNumber, origin, destination, departureDate, departureTime, arrivalDate, arrivalTime, status;
            cout << "Enter flight number to update: ";
            getline(cin, flightNumber);
            Flight* flight = ams.getFlight(flightNumber);
            if (flight == nullptr) continue;

            cout << "Enter new origin (current: " << flight->origin << "): ";
            getline(cin, origin);
            cout << "Enter new destination (current: " << flight->destination << "): ";
            getline(cin, destination);
            cout << "Enter new departure date (current: " << flight->departureDate << "): ";
            getline(cin, departureDate);
            cout << "Enter new departure time (current: " << flight->departureTime << "): ";
            getline(cin, departureTime);
            cout << "Enter new arrival date (current: " << flight->arrivalDate << "): ";
            getline(cin, arrivalDate);
            cout << "Enter new arrival time (current: " << flight->arrivalTime << "): ";
            getline(cin, arrivalTime);
            cout << "Enter new status (current: " << flight->status << "): ";
            getline(cin, status);

            Flight updatedFlight(flightNumber, origin, destination, departureDate, departureTime, arrivalDate, arrivalTime, status);
            ams.updateFlight(flightNumber, updatedFlight);
        } else if (choice == 3) {
            string flightNumber;
            cout << "Enter flight number to delete: ";
            getline(cin, flightNumber);
            ams.deleteFlight(flightNumber);
        } else if (choice == 4) {
            string flightNumber, passengerId, passengerName, passengerEmail;
            cout << "Enter flight number: ";
            getline(cin, flightNumber);
            Flight* flight = ams.getFlight(flightNumber);
            if (flight == nullptr) continue;

            cout << "Enter passenger ID: ";
            getline(cin, passengerId);
            cout << "Enter passenger name: ";
            getline(cin, passengerName);
            cout << "Enter passenger email: ";
            getline(cin, passengerEmail);

            Passenger passenger(passengerId, passengerName, passengerEmail);
            flight->addPassenger(passenger);
        } else if (choice == 5) {
            string status;
            cout << "Enter status (scheduled, cancelled, completed): ";
            getline(cin, status);
            ams.generateReportByStatus(status);
        } else if (choice == 6) {
            string flightNumber;
            cout << "Enter flight number: ";
            getline(cin, flightNumber);
            ams.generatePassengerReport(flightNumber);
        } else if (choice == 7) {
            string departureDate;
            cout << "Enter departure date (YYYY-MM-DD): ";
            getline(cin, departureDate);
            ams.generateReportByDate(departureDate, true);
        } else if (choice == 8) {
            string arrivalDate;
            cout << "Enter arrival date (YYYY-MM-DD): ";
            getline(cin, arrivalDate);
            ams.generateReportByDate(arrivalDate, false);
        } else if (choice == 9) {
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
