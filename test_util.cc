#include "../server/src/jujimeizuo.h"
#include <assert.h>

jujimeizuo::Logger::ptr g_logger = JUJIMEIZUO_LOG_ROOT();

void test_assert() {
    JUJIMEIZUO_LOG_INFO(g_logger) << jujimeizuo::BacktraceToString(10);
    JUJIMEIZUO_ASSERT_E(0 == 1, "hhhh");
}

int main(int argc, char** argv) {
    test_assert();
    return 0;
}