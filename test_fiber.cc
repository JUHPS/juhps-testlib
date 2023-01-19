#include "../server/src/jujimeizuo.h"

jujimeizuo::Logger::ptr g_logger = JUJIMEIZUO_LOG_ROOT();

void run_in_fiber() {
    JUJIMEIZUO_LOG_INFO(g_logger) << "run_in_fiber begin";
    jujimeizuo::Fiber::GetThis() -> YieldToHold();
    JUJIMEIZUO_LOG_INFO(g_logger) << "run_in_fiber end";
}

int main(int argc, char** argv) {
    jujimeizuo::Fiber::GetThis();
    JUJIMEIZUO_LOG_INFO(g_logger) << "main begin";
    jujimeizuo::Fiber::ptr fiber(new jujimeizuo::Fiber(run_in_fiber));
    fiber -> swapIn();
    JUJIMEIZUO_LOG_INFO(g_logger) << "main after swapIn";
    fiber -> swapIn();
    JUJIMEIZUO_LOG_INFO(g_logger) << "main after end";
}