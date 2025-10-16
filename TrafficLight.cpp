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
    LightColor state {LightColor::Red};
    double duration_sec {60.0};
    bool pedestrian_mode {false};
};


// Task 3: Define type aliases using the 'using' keyword:
// - LightRef   -> alias for a mutable TrafficLight reference
// - CLightRef  -> alias for a read-only TrafficLight reference

using LightRef = TrafficLight&;
using CLightRef = const TrafficLight&;


// Task 4: Implement constexpr utility functions:
// (1) 'to_string_view' function
constexpr std::string_view to_string_view(LightColor c) {
    // TODO: Use a switch statement to return "Red", "Yellow", or "Green".
    
    switch (c) {
        case LightColor::Red: return "Red";
        case LightColor::Yellow: return "Yellow";
        case LightColor::Green: return "Green";
    }

    return "Unknown";
}

std::string to_string(LightColor c) {
    return std::string{to_string_view(c)};
}


// (2) 'next' function
constexpr LightColor next(LightColor c) {
    // TODO: Use a switch statement to implement the following transitions using LightColor:
    //  Red -> Yellow, Yellow -> Green, Green -> Red
    //  Return Yellow if the input is Red, Green if the input is Yellow, and Red if the input is Green.
    
    switch (c) {
        case LightColor::Yellow: return LightColor::Red;
        case LightColor::Green: return LightColor::Yellow;
        case LightColor::Red: return LightColor::Green;
    }
}


// (3) 'is_safe_to_go' function
constexpr bool is_safe_to_go(LightColor c) {
    // TODO: Return a boolean value indicating whether the input is the green light.

    return c == LightColor::Green;
}


// (4) 'advance' function
void advance(LightRef tl) {
    // TODO: change the 'state' of tl by using 'next' function.

    tl.state = next(tl.state);
}



// (5) 'describe' function
std::string describe(CLightRef tl) {
    // TODO: Display the current 'state', 'duration_sec', and 'pedestrianMode' as an std::string.
    // Question: Why does the 'advance' function take a reference, while 'describe' takes a const reference?
    
    std::string s;
    s += "State=" + to_string(tl.state);
    s += ", duration_sec=" + std::to_string(tl.duration_sec);
    s += ", pedestrian_mode=" + std::string(tl.pedestrian_mode ? "true" : "false");
    return s;
}


// (6) 'is_same_state' function
bool is_same_state(CLightRef a, CLightRef b) {
    // TODO: Return a boolean value indicating whether the 'state' of a and b are the same.
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
