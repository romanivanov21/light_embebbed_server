/**
 *  @file libhttp_api_test.h
 *
 *  @brief unit tests for the library libhttp_api
 */

#ifndef _LIBHTTP_API_TEST_H_
#define _LIBHTTP_API_TEST_H_

#include "http_request_parser.h"
#include "http_request.h"

//std
#include <string>

//gtest
#include <gtest/gtest.h>

TEST(request001, httpparsertest)
{
    const std::string request = "GET /web_server.ru HTTP/1.1\r\n"
      "User-Agent: Mozilla/5.0\r\n"
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
      "Host: web_server.ru\r\n"
      "Connection: Keep-Alive\r\n"
      "\r\n";
    http_request parse_request;
    http_request_parser parser;
    http_request_parser::request_parse_result  result = parser.parse(request, parse_request );
    ASSERT_EQ(result, http_request_parser::request_parse_result::COMPLETE);
    ASSERT_EQ(parse_request.method_, "GET");
    ASSERT_EQ(parse_request.headers_["User-Agent"], "Mozilla/5.0");
    ASSERT_EQ(parse_request.headers_["Accept"], "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    ASSERT_EQ(parse_request.headers_["Host"], "web_server.ru");
    ASSERT_EQ(parse_request.keep_alive_, true);
}

TEST(request002, http_version_test)
{
    const std::string request1 = "GET /web_server.ru HTTP/1.1\r\n";
    http_request parse_request;
    http_request_parser parser;
    http_request_parser::request_parse_result result1 = parser.parse(request1, parse_request);
    ASSERT_EQ(parse_request.version_major_, 1);
    ASSERT_EQ(parse_request.version_minor_, 1);
    ASSERT_EQ(parse_request.keep_alive_, true);

    const std::string request2 = "GET /web_server.ru HTsdf/213.121";
    http_request_parser::request_parse_result result2 = parser.parse(request2, parse_request);
    ASSERT_EQ(result2 ,http_request_parser::request_parse_result::ERROR);
}

#endif //_LIBHTTP_API_TEST_H_
