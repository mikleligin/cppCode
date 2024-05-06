#include <chrono>
#include <cstdint>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <iostream>
#include <future>
#include <memory>
#include <thread>
#include <mavsdk/plugins/offboard/offboard.h>
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
    float x = 0;
    float y = 0;
    float z = 0;
    float checkStraight(float x1, float y1, float x2, float y2, float x3, float y3);
    float toInertialSystem(float angle, float vector, float dist_x, float dist_y, int flag);
    float fromGeodethic(float llat1, float llon1, float llat2, float llon2, int flag);
    float pythagoras(float x, float y);
    /* data */
public:
    offClass(float startLat, float startLon);
    int takeoffTest();
    int offboardTest();
    void goToPointTest(float lat, float lon);
    int offboardInit();
    void updateOffboardPoint(float lat, float lon);
    void putOffboardParameters(float x, float y);
    int flyToPoint(Mavsdk mavsdk, std::shared_ptr<System> system);
};

