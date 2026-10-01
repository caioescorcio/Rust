#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "money.h"

Money *five_dollars;
Money *five_dollars_null;

void setup(void)
{
    five_dollars = money_create(5, "USD");
}

void setup_null(void)
{
    five_dollars_null = money_create(-1, "USD");
}

void teardown(void)
{
    money_free(five_dollars);
}

void teardown_null(void)
{
    money_free(five_dollars_null);
}

START_TEST(test_money_create_amount)
{
    ck_assert_double_eq(money_amount(five_dollars), 5);
}
END_TEST

START_TEST(test_money_create_currency)
{
    ck_assert_str_eq(money_currency(five_dollars_null), "USD");
}
END_TEST

Suite *money_suite(void)
{
    Suite *s;
    TCase *tc_core;
    TCase *tc_null;

    s = suite_create("Money");

    tc_core = tcase_create("Core");
    tc_null = tcase_create("Null");

    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_checked_fixture(tc_null, setup_null, teardown_null);
    tcase_add_test(tc_core, test_money_create_amount);
    tcase_add_test(tc_core, test_money_create_currency);
    suite_add_tcase(s, tc_core);
    suite_add_tcase(s, tc_null);
    return s;
}

int main(void)
{
    double number_failed;
    Suite *s;
    SRunner *sr;

    s = money_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
