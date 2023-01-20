#include "../server/src/jujimeizuo.h"


jujimeizuo::Logger::ptr g_logger = JUJIMEIZUO_LOG_ROOT();

void run_in_fiber() {
    JUJIMEIZUO_LOG_INFO(g_logger) << "run_in_fiber begin";
    jujimeizuo::Fiber::GetThis() -> YieldToHold();
    JUJIMEIZUO_LOG_INFO(g_logger) << "run_in_fiber end";
}

void test_fiber() {
    JUJIMEIZUO_LOG_INFO(g_logger) << "main begin -1";
    {
        jujimeizuo::Fiber::GetThis();
        JUJIMEIZUO_LOG_INFO(g_logger) << "main begin";
        jujimeizuo::Fiber::ptr fiber(new jujimeizuo::Fiber(run_in_fiber));
        fiber -> swapIn();
        JUJIMEIZUO_LOG_INFO(g_logger) << "main after swapIn";
        fiber -> swapIn();
        JUJIMEIZUO_LOG_INFO(g_logger) << "main after end";
    }
    JUJIMEIZUO_LOG_INFO(g_logger) << "main after end2";
}

int main(int argc, char** argv) {
    jujimeizuo::Thread::SetName("main");
    std::vector<jujimeizuo::Thread::ptr> thrs;
    for (int i = 0; i < 3; i++) {
        thrs.push_back(jujimeizuo::Thread::ptr(new jujimeizuo::Thread(&test_fiber, "name_" + std::to_string(i))));
    }
    for (auto i : thrs) {
        i -> join();
    }
    return 0;
}