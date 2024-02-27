
#include "greatest.h"
#include "../src/stack_fx.h"

extern SUITE(stackFX);

static void setup_cb(void *data) {
    
    printf("setup callback for each test case\n");
}

static void teardown_cb(void *data) {
    printf("teardown callback for each test case\n");
}

GREATEST_SUITE(stackFX) {

    stack_fx* stck;

    SET_SETUP(setup_cb, stck);
    SET_TEARDOWN(teardown_cb, stck);

    // RUN_TEST(example);

}

