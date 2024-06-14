import timeit


def flight():
    try:
        from FlightRadar24 import FlightRadar24API
        from FlightRadar24.errors import CloudflareError
        fr_api = FlightRadar24API()

        airline_icao = "KAL"
        asiana_icao = "AAR"

        zone_asia = fr_api.get_zones()["asia"]
        bounds_asia = fr_api.get_bounds(zone_asia)

        koreanair_asiaFlights = fr_api.get_flights(
            #aircraft_type = aircraft_type,
            airline = airline_icao,
            bounds = bounds_asia
        )

        for flight in koreanair_asiaFlights:
            flight_details = fr_api.get_flight_details(flight)
            try:
                if flight_details is not None and 'airport' in flight_details:
                    origin_name = flight_details['airport']['origin']['name'] if 'origin' in flight_details['airport'] and 'name' in flight_details['airport']['origin'] else 'Unknown'
                    destination_name = flight_details['airport']['destination']['name'] if 'destination' in flight_details['airport'] and 'name' in flight_details['airport']['destination'] else 'Unknown'

                    print(f"KOREAN AIR FLIGHT: {origin_name} -> {destination_name}")
                else:
                    print("Flight details not available.")
            except (AttributeError, TypeError) as e:
                print(f"Error occurred: {e}")

    except CloudflareError as e:
        print(f"Error occurred: {e}")

    return 'Korean Air'

# execution_times = timeit.repeat("flight()", setup="from __main__ import flight", repeat=20, number=1)
# print(execution_times)
# average_time = sum(execution_times) / len(execution_times)
# print(average_time)
flight()