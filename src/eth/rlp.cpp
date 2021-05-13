#include <vector>

using std::vector;

enum minth_t_tag { MINTH_T_VECTOR_LIST, MINTH_T_BYTE_ARR };

struct T {
    union {
        vector<struct T> list;
        vector<unsigned char> byte_array;
    } value;
    enum minth_t_tag tag;
};

int main() {

}
