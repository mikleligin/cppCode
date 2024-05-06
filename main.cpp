#include "offClass.h"
using namespace std;

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
    // Get discovered system now.
    return fut.get();
}

int main(int argc, char** argv)
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
    auto offboard = Offboard{system};
    const Offboard::PositionNedYaw stay{};
    offboard.set_position_ned(stay);
    Offboard::Result offboard_result = offboard.start();
    if (offboard_result != Offboard::Result::Success) {
        std::cerr << "Offboard::start() failed: " << offboard_result << '\n';
    }
    offClass a(47.123, 8.321);
    //a.goToPoint(48.333, 9.231);
    a.offboardTest();
    //a.takeoffTest();
    return 0;
}
