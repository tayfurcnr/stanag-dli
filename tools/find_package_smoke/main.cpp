#include <dli/protocol/DliHeader.hpp>

int main() {
    dli::DliHeader header;
    header.message_type = 16002;
    return header.message_type == 16002 ? 0 : 1;
}
