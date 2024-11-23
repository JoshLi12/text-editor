#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_push_1) {
    List<int> list;
    list.push_front(2);
    ASSERT_EQUAL(list.front(), 2);
    ASSERT_EQUAL(list.back(), 2);

    list.push_front(5);
    ASSERT_EQUAL(list.front(), 5);
    ASSERT_EQUAL(list.back(), 2);

    list.clear();

    list.push_back(10);
    ASSERT_EQUAL(list.front(), 10);
    ASSERT_EQUAL(list.back(), 10);
    list.push_back(15);
    ASSERT_EQUAL(list.back(), 15);
}

TEST(test_pop_1) {
    List<int> list;
    // list.push_front(5);
    // list.push_front(10);
    // list.push_front(15);
    // ASSERT_EQUAL(list.size(), 3);

    // list.pop_front();
    // ASSERT_EQUAL(list.size(), 2);

    // list.pop_back();
    // ASSERT_EQUAL(list.size(), 1);



}

// TEST(test_pop_1) {
//     List<int> list;
//     list.push_front(5);
//     list.push_back(10);
//     list.push_front(2);
//     ASSERT_EQUAL(list.size(), 3);
// }


TEST_MAIN()
