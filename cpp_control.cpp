#include <cstdlib>

int main() {
    // turn on the bulb
    system("curl -X POST http://localhost:5000/bulb -H \"Content-Type: application/json\" -d '{\"BULB_01\": \"ON\"}'");


    return 0;
}