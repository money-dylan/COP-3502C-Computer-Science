#include <stdio.h>
#include <math.h>

struct Shipment {
    int arrivalTime; // arr time
    int expirationTime; // exp time
    int mass; // mass
};
//====================================================================================================================
double calculateRate(struct Shipment shipments[], int numShipments, int startTime, int endTime) {
    double low = 0.0, high = 1e9, mid;
    while (high - low > 1e-6) {
        mid = (low + high) / 2.0;
        double totalMass = 0.0, remainingMass = 0.0;
        int flag = 1;
        for (int i = 0; i < numShipments; i++) {
            if (shipments[i].arrivalTime <= endTime && shipments[i].expirationTime >= startTime) {
                // Shipment in eating time
                int start_time = shipments[i].arrivalTime > startTime ? shipments[i].arrivalTime : startTime;
                int end_time = shipments[i].expirationTime < endTime ? shipments[i].expirationTime : endTime;
                totalMass += shipments[i].mass * (end_time - start_time);
            }
        }
        if (totalMass * mid <= (endTime - startTime) * remainingMass) {
            // Rate too low, inc
            low = mid;
        } else {
            // Rate too high, dec
            high = mid;
        }
    }
    return low;
}
//====================================================================================================================
int main() {
    int numShipments, startTime, endTime;
    scanf("%d", &numShipments);
    struct Shipment shipments[numShipments];
    for (int i = 0; i < numShipments; i++) {
        scanf("%d %d %d", &shipments[i].arrivalTime, &shipments[i].expirationTime, &shipments[i].mass);
    }
    scanf("%d %d", &startTime, &endTime);
    double rate = calculateRate(shipments, numShipments, startTime, endTime);
    printf("%.10lf", rate);
    return 0;
}
