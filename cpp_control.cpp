#include <cstdlib>

int main() {
    // Bật đèn
    system("curl -X POST http://localhost:5000/bulb -H "Content-Type: application/json" -d '{"BULB_01": "ON"}'");
    
    // Tắt đèn
    // system("curl -X POST http://localhost:5000/bulb -H \"Content-Type: application/json\" -d '{\"BULB_01\": \"OFF\"}'");

    return 0;
}