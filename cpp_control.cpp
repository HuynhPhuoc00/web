#include <cstdlib>

int main() {
    // turn on the bulb
    system("curl -X POST http://localhost:8080/bulb -H \"Content-Type: application/json\" -d '{\"BULB_01\": \"ON\"}'");
    return 0;
}