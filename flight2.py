import timeit
def flight():

    counter=0
    try:
        from FlightRadar24 import FlightRadar24API
        from FlightRadar24.errors import CloudflareError
        fr_api = FlightRadar24API()

        airline_icao = "KAL"
        asiana_icao = "AAR"
        zone_asia = fr_api.get_zones()["asia"]
        bounds_asia = fr_api.get_bounds(zone_asia)

        allFlights=fr_api.get_flights(bounds = bounds_asia)
        airport = fr_api.get_airport("ICN")
        for flight in allFlights:
            if flight.altitude>0:
                distance = flight.get_distance_from(airport)
                if distance<400:
                    flight_details = fr_api.get_flight_details(flight)
                    flight.set_flight_details(flight_details)
                    if flight_details['airport']['destination']['name'] == 'Seoul Incheon International Airport':
                        counter+=1
                        print(f"APPROACHING ICN - {distance} km: {flight_details['airport']['origin']['name']} -> {flight_details['airport']['destination']['name']} operated by {flight_details['airline']['name']}")

    except CloudflareError as e:
        print(f"Error occurred: {e}")
        if counter==0:
            print("No flight approaching ICN")
            return "0"
        else:
            return "1"

# execution_times = timeit.repeat("flight()", setup="from __main__ import flight", repeat=20, number=1)
# print(execution_times)
# average_time = sum(execution_times) / len(execution_times)
# print(average_time)
flight()