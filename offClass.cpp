#include "offClass.h"

offClass::offClass(float startLat, float startLon)
{
    this->startLat = startLat;
    this->startLon = startLon;
}
std::shared_ptr<System> getSystem(Mavsdk& mavsdk)
{
    std::cout << "Waiting to discover system...\n";
    auto prom = std::promise<std::shared_ptr<System>>{};
    auto fut = prom.get_future();
    mavsdk.subscribe_on_new_system([&mavsdk, &prom]() {
        auto system = mavsdk.systems().back();
        if (system->has_autopilot()) {
            std::cout << "Discovered autopilot\n";
            mavsdk.subscribe_on_new_system(nullptr);
            prom.set_value(system);
        }
    });
    if (fut.wait_for(seconds(3)) == std::future_status::timeout) {
        std::cerr << "No autopilot found.\n";
        return {};
    }
    return fut.get();
}
int offClass::takeoffTest()
{
    Mavsdk mavsdk;
    ConnectionResult connection_result = mavsdk.add_any_connection("udp://");
    if (connection_result != ConnectionResult::Success) {
        std::cerr << "Connection failed: " << connection_result << '\n';
        return 1;
    }
    auto system = getSystem(mavsdk);
    if (!system) {
        return 1;
    }
    auto telemetry = Telemetry{system};
    auto action = Action{system};
    std::cout << "Arming...\n";
    const Action::Result arm_result = action.arm();
    if (arm_result != Action::Result::Success) {
        std::cerr << "Arming failed: " << arm_result << '\n';
        return 1;
    }
    const Action::Result takeoff_result = action.takeoff();
    sleep_for(seconds(10));
    const Action::Result land_result = action.land();
    while (telemetry.in_air()) {
        std::cout << "Vehicle is landing...\n";
        sleep_for(seconds(1));
    }
    std::cout << "Landed!\n";
    sleep_for(seconds(3));
    std::cout << "Finished...\n";
}

float offClass::checkStraight(float x1, float y1, float x2, float y2, float x3, float y3){}
float offClass::toInertialSystem(float angle, float vector, float dist_x, float dist_y, int flag){}
float offClass::fromGeodethic(float llat1, float llon1, float llat2, float llon2, int flag){}
float offClass::pythagoras(float x, float y){}
void offClass::goToPointTest(float lat, float lon){
    cout<<"Going from point " << this->startLat << " "
    << this->startLon << " to "
    << lat << " " << lon;
}

int offClass::offboardTest(){
    cout<<"offboard"<<endl;
    Mavsdk mavsdk;
    ConnectionResult connection_result = mavsdk.add_any_connection("udp://");
    if (connection_result != ConnectionResult::Success) {
        std::cerr << "Connection failed: " << connection_result << '\n';
        return 1;
    }
    auto system = getSystem(mavsdk);
    if (!system) {
        return 1;
    }
    auto telemetry = Telemetry{system};
    auto action = Action{system};
    std::cout << "Arming...\n";
    const Action::Result arm_result = action.arm();

    if (arm_result != Action::Result::Success) {
        std::cerr << "Arming failed: " << arm_result << '\n';
        return 1;
    }
    const Action::Result takeoff_result = action.takeoff();
    sleep_for(seconds(10));
    auto offboard = Offboard{system};
    const Offboard::PositionNedYaw stay{};
    offboard.set_position_ned(stay);
    Offboard::Result offboard_result = offboard.start();
    std::cout << "Go up 2 m/s, turn to face South\n";
    Offboard::PositionNedYaw position{1.0f,1.0f,-3.0f,4.0f};
    offboard.set_position_ned(position);
    sleep_for(seconds(5));
if (offboard_result != Offboard::Result::Success) {
        std::cerr << "Offboard::start() failed: " << offboard_result << '\n';
    }
    //offboard.start();
}

int offboardInit()
{
    cout<<"Offboard Initializing..."<<endl;
    Mavsdk mavsdk;
    ConnectionResult connection_result = mavsdk.add_any_connection("udp://");
    if (connection_result != ConnectionResult::Success) {
        std::cerr << "Connection failed: " << connection_result << '\n';
        return 1;
    }
    auto system = getSystem(mavsdk);
    if (!system) {
        return 1;
    }
    auto telemetry = Telemetry{system};
    auto action = Action{system};
    std::cout << "Arming...\n";
    const Action::Result arm_result = action.arm();

    if (arm_result != Action::Result::Success) {
        std::cerr << "Arming failed: " << arm_result << '\n';
        return 1;
    }
    const Action::Result takeoff_result = action.takeoff();
    sleep_for(seconds(10));
    auto offboard = Offboard{system};
    const Offboard::PositionNedYaw stay{};
    offboard.set_position_ned(stay);
    Offboard::Result offboard_result = offboard.start();
    if (offboard_result != Offboard::Result::Success) {
        std::cerr << "Offboard::start() failed: " << offboard_result << '\n';
    }
}
void offClass::updateOffboardPoint(float lat, float lon){

}
void offClass::putOffboardParameters(float x, float y){

}
int offClass::flyToPoint(Mavsdk mavsdk, std::shared_ptr<System> system){

}
