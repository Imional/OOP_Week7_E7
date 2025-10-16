#include <iostream>
#include <string>
#include <string_view>

// Task 1: Define an enum class LightColor representing traffic light states: Red, Yellow, Green.
enum class LightColor {
    Red,
    Yellow,
    Green
};

// Task 2: Define a struct TrafficLight with:
// - 'state' with LightColor type (default: Red)
// - 'duration_sec' with double type (default: 60.0)
// - 'pedestrian_mode' with boolean type (default: false)
struct TrafficLight {
    LightColor state = LightColor::Red;
    double duration_sec = 60.0;
    bool pedestrian_mode = false;
};

// Task 3: Define type aliases using the 'using' keyword:
// - LightRef   -> alias for a mutable TrafficLight reference
// - CLightRef  -> alias for a read-only TrafficLight reference
using LightRef = TrafficLight&;
using CLightRef = const TrafficLight&;

// Task 4: Implement constexpr utility functions:
// (1) 'to_string_view' function
constexpr std::string_view to_string_view(LightColor c) {
    switch (c) {
        case LightColor::Red:    return "Red";
        case LightColor::Yellow: return "Yellow";
        case LightColor::Green:  return "Green";
        default:                 return "Unknown";
    }
}

std::string to_string(LightColor c) {
    return std::string{to_string_view(c)};
}

// (2) 'next' function
constexpr LightColor next(LightColor c) {
    if (c == LightColor::Red)    return LightColor::Yellow;
    if (c == LightColor::Yellow) return LightColor::Green;
    return LightColor::Red;
}

// (3) 'is_safe_to_go' function
constexpr bool is_safe_to_go(LightColor c) {
    return (c == LightColor::Green);
}

// (4) 'advance' function
void advance(LightRef tl) {
    tl.state = next(tl.state);
}

// (5) 'describe' function
std::string describe(CLightRef tl) {
    // Answer to question: 'advance' takes a mutable reference to modify the TrafficLight's state,
    // while 'describe' takes a const reference because it only reads the state without modifying it.
    std::string result = "TrafficLight[";
    result += "color=" + std::string(to_string_view(tl.state));
    result += ", duration=" + std::to_string(tl.duration_sec) + "s";
    result += ", pedestrian=" + (tl.pedestrian_mode ? "on" : "off") + "]";
    return result;
}

// (6) 'is_same_state' function
bool is_same_state(CLightRef a, CLightRef b) {
    return a.state == b.state;
}

int main() {
    TrafficLight tl;
    
    CLightRef view = tl;
    std::cout << "Initial: " << describe(view) << "\n";

    LightRef handle = tl;
    advance(handle);
    std::cout << "After advance: " << describe(tl) << "\n";
    std::cout << "Safe to go? " << (is_safe_to_go(tl.state) ? "YES" : "NO") << "\n";

    handle.duration_sec = 45.0;
    std::cout << "Adjusted duration: " << describe(view) << "\n";
}