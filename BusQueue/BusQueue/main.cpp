#include <iostream>
#include <string>

using namespace std;

class BusStop {
private:
    int avg_time_between_passengers;
    int avg_time_between_buses;
    bool is_terminal;
    int max_people;
    int simulation_duration;
    int people_on_stop;
    int total_wait_time;
    int passenger_count;
    int current_time;
    int arrival_times[100]; 

public:
    BusStop(int avg_passenger_time, int avg_bus_time, bool terminal, int max_people_on_stop, int duration)
        : avg_time_between_passengers(avg_passenger_time),
        avg_time_between_buses(avg_bus_time),
        is_terminal(terminal),
        max_people(max_people_on_stop),
        simulation_duration(duration),
        people_on_stop(0),
        total_wait_time(0),
        passenger_count(0),
        current_time(0) {}

    void run_simulation() {
        while (current_time < simulation_duration) {
            if (current_time % avg_time_between_passengers == 0 && people_on_stop < max_people) {
                add_passenger();
            }
            if (current_time % avg_time_between_buses == 0 && people_on_stop > 0) {
                bus_arrival();
            }
            if (is_terminal && people_on_stop == 0 && current_time > 0) {
                break;
            }
            current_time++;
        }
        print_average_wait_time();
    }

private:
    void add_passenger() {
        arrival_times[people_on_stop] = current_time; 
        people_on_stop++;
        passenger_count++;
        cout << "Passenger arrived at " << current_time << " min | People on stop: " << people_on_stop << endl;
    }

    void bus_arrival() {
        int seats_in_bus = 3;
        int people_to_board = (people_on_stop < seats_in_bus) ? people_on_stop : seats_in_bus;

        for (int i = 0; i < people_to_board; i++) {
            total_wait_time += (current_time - arrival_times[i]); 
        }

        for (int i = people_to_board; i < people_on_stop; i++) {
            arrival_times[i - people_to_board] = arrival_times[i];
        }

        people_on_stop -= people_to_board;
        cout << "Bus arrived at " << current_time << " min | Passengers boarded: " << people_to_board
            << " | Remaining on stop: " << people_on_stop << endl;
    }

    void print_average_wait_time() const {
        double avg_wait_time = (passenger_count > 0) ? static_cast<double>(total_wait_time) / passenger_count : 0;
        cout << "Average wait time at stop: " << avg_wait_time << " min" << endl;
    }
};

int main() {
    int avg_time_between_passengers = 5;
    int avg_time_between_buses = 15;
    int max_people = 10;
    int simulation_duration = 120;
    bool is_terminal = false;

    BusStop bus_stop(avg_time_between_passengers, avg_time_between_buses, is_terminal, max_people, simulation_duration);
    bus_stop.run_simulation();

}
