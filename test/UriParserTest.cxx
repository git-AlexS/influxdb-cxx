// MIT License
//
// Copyright (c) 2020-2022 offa
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "UriParser.h"
#include "InfluxDBException.h"
#include <string>
#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>


namespace influxdb::test
{
    using namespace Catch::Matchers;

    TEST_CASE("Check parser with token", "[ParseHttpUrl]")
    {
        std::string url = "https://localhost:8000?db=test --THIS_TOKEN";
        http::url parsedUrl = http::ParseHttpUrl(url);

        CHECK_THAT(parsedUrl.protocol, Equals("https"));
        CHECK_THAT(parsedUrl.search, Equals("db=test"));
        CHECK_THAT(parsedUrl.authtoken, Equals("THIS_TOKEN"));
        CHECK_THAT(parsedUrl.host, Equals("localhost"));

        CHECK(parsedUrl.user.empty());
    }

    TEST_CASE("Check parser without token", "[ParseHttpUrl]")
    {
        std::string url = "https://localhost:8000?db=test";
        http::url parsedUrl = http::ParseHttpUrl(url);

        CHECK_THAT(parsedUrl.protocol, Equals("https"));
        CHECK_THAT(parsedUrl.search, Equals("db=test"));
        CHECK_THAT(parsedUrl.host, Equals("localhost"));

        CHECK(parsedUrl.user.empty());
        CHECK(parsedUrl.authtoken.empty());
    }

}
