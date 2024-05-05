#include <chrono>
#include <cstdint>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <iostream>
#include <future>
#include <memory>
#include <thread>
using namespace std;
using namespace mavsdk;
using std::chrono::seconds;
using std::this_thread::sleep_for;
class offClass
{
private:
    int commandCode = 0;
    float startLat = 0;
    float startLon = 0;
    float checkStraight(float x1, float y1, float x2, float y2, float x3, float y3);
    float toInertialSystem(float angle, float vector, float dist_x, float dist_y, int flag);
    float fromGeodethic(float llat1, float llon1, float llat2, float llon2, int flag);
    float pythagoras(float x, float y);
    /* data */
public:
    offClass(float startLat, float startLon);
    int takeoffTest();
    void goToPoint(float lat, float lon);

};

