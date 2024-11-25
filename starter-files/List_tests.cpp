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
    list.push_front(5);
    list.push_front(10);
    list.push_front(15);
    ASSERT_EQUAL(list.size(), 3);

    list.pop_front();
    ASSERT_EQUAL(list.size(), 2);

    list.pop_back();
    ASSERT_EQUAL(list.size(), 1);

    list.pop_back();
    ASSERT_EQUAL(list.size(), 0);
}

TEST(copy_constructor) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int> copy(list);

    ASSERT_EQUAL(copy.size(), 3);
    ASSERT_EQUAL(*list.begin(), *copy.begin());
    
    list.push_back(4);
    ASSERT_EQUAL(copy.size(), 3);
    ASSERT_EQUAL(list.size(), 4);

    copy.push_back(5);
    copy.push_back(6);
    ASSERT_EQUAL(copy.size(), 5);
    ASSERT_EQUAL(list.size(), 4);
}

TEST(assignment_operator) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    List<int> list2;
    list2.push_back(5);
    list2 = list1;

    ASSERT_EQUAL(list2.size(), 3);
    ASSERT_EQUAL(*list2.begin(), 1);

    list1.push_back(5);
    list1.push_back(6);
    ASSERT_EQUAL(list2.size(), 3);
}

TEST(postfix_operator_test) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    List<int>::Iterator it = list.begin();

    List<int>::Iterator postfix_increment = it++;
    ASSERT_EQUAL(postfix_increment, list.begin());
    ASSERT_EQUAL(*it, 2);

    it = list.end();
    List<int>::Iterator postfix_decrement = it--;
    ASSERT_EQUAL(postfix_decrement, list.end());
    ASSERT_EQUAL(*it, 4);
}


TEST(iterator_forward_traversal) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    int j = 0;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it, ++j) {
        ASSERT_EQUAL(*it, j);
    }
    ASSERT_EQUAL(j, list.size());
}

TEST(iterator_backward_traversal) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    int j = list.size();
    List<int>::Iterator it = list.end();
    do {
        --it;
        --j;
        ASSERT_EQUAL(*it, j);
    }
    while(it != list.begin());
    ASSERT_EQUAL(j, 0);
}

TEST(iterator_equality) {
    List<int> list;
    list.push_back(5);
    list.push_back(6);
    list.push_back(6);
    list.push_back(6);
    list.push_back(6);
    list.push_back(6);


    List<int>::Iterator it1 = list.begin();
    List<int>::Iterator it2 = list.begin();
    ASSERT_TRUE(it1==it2);

    ++it1;
    ++it2;

    ASSERT_TRUE(it1==it2);

    ++it1;
    ASSERT_TRUE(it1!=it2);
}

TEST(pointer_and_deference) {
    List<int> list;
    list.push_back(5);
    list.push_back(5);
    list.push_back(5);

    List<int>::Iterator it1 = list.begin();
    List<int>::Iterator it2 = list.begin();
    ASSERT_EQUAL(*it1, *it2);

    ++it1;
    ++it2;
    ASSERT_EQUAL(*it1, *it2);
}

TEST(erase_first) {
    List<int> list;
    list.push_back(5);
    list.push_back(10);
    list.push_back(15);

    List<int>::Iterator it = list.begin();

    // remove first node
    List<int>::Iterator it2 = list.erase(it);
    ASSERT_EQUAL(*it2, 10);
    ASSERT_EQUAL(list.size(), 2);
    ++it2;

    // erase last node
    List<int>::Iterator it3 = list.erase(it2);
    ASSERT_EQUAL(it3, list.end());

    // removing only node
    it = list.begin();
    list.erase(it);
    ASSERT_EQUAL(list.size(), 0);

}

TEST(erasing_middle_node) {
    List<int> list;
    list.push_back(5);
    list.push_back(10);
    list.push_back(15);

    List<int>::Iterator it = list.begin();
    ++it;
    List<int>::Iterator it2 = list.erase(it);
    ASSERT_EQUAL(list.size(), 2);
    ASSERT_EQUAL(*it2, 15);
}

TEST(test_insert_empty) {
    List<int> list;

    // Inserting into empty list
    List<int>::Iterator it = list.begin();
    it = list.insert(it, 5);
    ASSERT_EQUAL(*it, 5);
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(*list.begin(), 5);
    ASSERT_EQUAL(*(--list.end()), 5);
}

TEST(test_insert_back) {
    List<int> list;
    List<int>::Iterator it = list.begin();
    list.push_back(5);
    list.push_back(10);

    it = list.end();
    it = list.insert(it, 10);
    ASSERT_EQUAL(*it, 10);
    ASSERT_EQUAL(list.size(), 3);
    ASSERT_EQUAL(*(--list.end()), 10);
}

TEST(test_insert_front) {
    List<int> list;
    List<int>::Iterator it = list.begin();
    list.push_back(5);
    list.push_back(10);

    it = list.begin();
    it = list.insert(it, 0);
    ASSERT_EQUAL(*it, 0);
    ASSERT_EQUAL(list.size(), 3);
    ASSERT_EQUAL(*list.begin(), 0);
}

TEST(test_insert_middle) {
    List<int> list;
    list.push_back(5);
    list.push_back(10);
    list.push_back(15);
    List<int>::Iterator it = list.begin();

    ++it;
    cout << *it << endl;

    it = list.insert(it, 7);
    ASSERT_EQUAL(*it, 7);
    ASSERT_EQUAL(list.size(), 4);
}

TEST_MAIN()
