//internal
#include "tcp_server.h"

//internal library
#include "connection_traits.h"
#include "endpoint.h"
#include "endpoint_ipv4.h"

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char** argv)
{
    sigset_t sigset;
    siginfo_t siginfo;
    chdir("/");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    //setup_signal( sigset,siginfo );

    network::endpoint_unique_ptr ep =
            std::make_unique<network::endpoint_ipv4>
            ("127.0.0.1", 8080);
    tcp_server s(ep);
    s.run();

    // wait signal
    sigwaitinfo(&sigset, &siginfo);
    if(siginfo.si_signo == SIGTERM) // если пришел сигнал о завершении программы
    {
        s.stop();
        exit(0);
    }

	return 0;
}
