#include "gtest/gtest.h"
#include "libnetwork_api_test.h"
#include "libthread_api_test.h"
#include "libhttp_api_test.h"

int main(int argc, char *argv[])
{
    //инициализация framework GTest
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS(); //запуск всех тестов
}
