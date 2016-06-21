#include <stdio.h>

int main() {
    for (int a = 0; a < 10000; a++) {
        if (!(((a&-a)^a)??!??!!(a<<!(a^a)|a>>~(~(a^a)<<!(a^a))))) {
            printf("%d\n", a);
        }
    }

    return 0;
}
