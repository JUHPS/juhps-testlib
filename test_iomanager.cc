#include "../server/src/jujimeizuo.h"
#include "../server/src/iomanager.h"
#include <sys/types.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

static jujimeizuo::Logger::ptr g_logger = JUJIMEIZUO_LOG_ROOT();

int sock;

void test_fiber() {
    JUJIMEIZUO_LOG_INFO(g_logger) << "test_fiber";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sock, F_SETFL, O_NONBLOCK);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "112.80.248.75", &addr.sin_addr.s_addr);

    if (!connect(sock, (const sockaddr*)&addr, sizeof(addr))) {
    } else if (errno == EINPROGRESS) {
        JUJIMEIZUO_LOG_INFO(g_logger) << "add event errno=" << errno << " " << strerror(errno);
        jujimeizuo::IOManager::GetThis()->addEvent(sock, jujimeizuo::IOManager::READ, [](){
            JUJIMEIZUO_LOG_INFO(g_logger) << "read callback";
        });
        jujimeizuo::IOManager::GetThis()->addEvent(sock, jujimeizuo::IOManager::WRITE, [](){
            JUJIMEIZUO_LOG_INFO(g_logger) << "write callback";
            //close(sock);
            jujimeizuo::IOManager::GetThis()->cancelEvent(sock, jujimeizuo::IOManager::READ);
            close(sock);
        });
    } else {
        JUJIMEIZUO_LOG_INFO(g_logger) << "else " << errno << " " << strerror(errno);
    }
}

void test1() {
    std::cout << "EPOLLIN=" << EPOLLIN
              << " EPOLLOUT=" << EPOLLOUT << std::endl;
    jujimeizuo::IOManager iom(2, false);
    iom.schedule(&test_fiber);
}

int main(int argc, char const *argv[]) {
    test1();
    return 0;
}


