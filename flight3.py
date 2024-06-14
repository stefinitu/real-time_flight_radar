import timeit
def flight():
    try:
        from FlightRadar24 import FlightRadar24API
        from FlightRadar24.errors import CloudflareError
        fr_api = FlightRadar24API()

        asiana_icao = "AAR"

        zone_asia = fr_api.get_zones()["asia"]
        bounds_asia = fr_api.get_bounds(zone_asia)

        asiana_asiaFlights = fr_api.get_flights(
            #aircraft_type = aircraft_type,
            airline = asiana_icao,
            bounds = bounds_asia
        )

        for flight in asiana_asiaFlights:
            flight_details = fr_api.get_flight_details(flight)
            try:
                flight.set_flight_details(flight_details)
                if flight_details['airport']['origin']['name'] is not None and flight_details['airport']['destination']['name'] is not None:
                    print(f"ASIANA AIRLINES FLIGHT: {flight_details['airport']['origin']['name']} -> {flight_details['airport']['destination']['name']}")
            except (AttributeError, TypeError) as e:
                print(f"Error occurred: {e}")
                
    except CloudflareError as e:
        print(f"Error occurred: {e}")
    return fr_api.get_flight_details(asiana_asiaFlights[0])['airport']['origin']['name']

# execution_times = timeit.repeat("flight()", setup="from __main__ import flight", repeat=20, number=1)
# print(execution_times)
# average_time = sum(execution_times) / len(execution_times)
# print(average_time)
flight()