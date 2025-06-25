#pragma once
#include<bits/stdc++.h> 
using namespace std;

class Location{
    const double PI = 3.14159265358979323846;
    const double R = 6371.0;
    double latitude, longitude;
    double to_radians(double degree){
        return degree*(PI/180.0);
    }
public:
    Location(double latitude, double longitude): latitude(latitude), longitude(longitude){}

    double get_latitude(){
        return latitude;
    }

    double get_longitude(){
        return longitude;
    }

    double distance_in_km(Location* loc){
        double lat1 = to_radians(latitude);
        double lat2 = to_radians(loc->get_latitude());

        double lat_diff = lat1- lat2;

        double lon1 = to_radians(longitude);
        double lon2 = to_radians(loc->get_longitude());

        double lon_diff = lon1-lon2;

        double a = sin(lat_diff/2) * sin(lat_diff/2) + 
                   cos(lat1) * cos(lat2) *
                   sin(lon_diff/2) * sin(lon_diff/2);

        double c = 2 * atan2(sqrt(a), sqrt(1-a));

        return R*c;
    }
};