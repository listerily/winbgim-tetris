#include "Client.hpp"

#include <cstdlib>
#include <ctime>

int main(void)
{
    srand(time(0));
	Client().start();
    return 0;
}

