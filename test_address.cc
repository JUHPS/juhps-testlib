#include "../src/jujimeizuo.h"

jujimeizuo::Logger::ptr g_logger = JUJIMEIZUO_LOG_ROOT();

void test() {
    std::vector<jujimeizuo::Address::ptr> addrs;

    JUJIMEIZUO_LOG_INFO(g_logger) << "begin";
    bool v = jujimeizuo::Address::Lookup(addrs, "www.jujimeizuo.cn");
    JUJIMEIZUO_LOG_INFO(g_logger) << "end";
    if (!v) {
        JUJIMEIZUO_LOG_ERROR(g_logger) << "lookup fail";
        return;
    }
    for (size_t i = 0; i < addrs.size(); ++i) {
        JUJIMEIZUO_LOG_INFO(g_logger) << i << " - " << addrs[i]->toString();
    }
}

void test_iface() {
    std::multimap<std::string, std::pair<jujimeizuo::Address::ptr, uint32_t> > results;

    bool v = jujimeizuo::Address::GetInterfaceAddresses(results);
    if (!v) {
        JUJIMEIZUO_LOG_ERROR(g_logger) << "GetInterfaceAddresses fail";
        return;
    }

    for (auto&i : results) {
        JUJIMEIZUO_LOG_INFO(g_logger) << i.first << " - " << i.second.first->toString() << " - "
            << i.second.second;
    }
}

void test_ipv4() {
    auto addr = jujimeizuo::IPAddress::Create("www.jujimeizuo.cn");
    // auto addr = jujimeizuo::IPAddress::Create("127.0.0.8");
    if (addr) {
        JUJIMEIZUO_LOG_INFO(g_logger) << addr->toString();
    }
}

int main(int argc, char** argv) {
    test_ipv4();
    // test_iface();
    // test();
    return 0;
}