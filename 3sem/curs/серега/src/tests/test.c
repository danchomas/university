#include "test.h"

int main(void) {
  int failed = 0;
  int success = 0;
  Suite *string_test[] = {
      tests_converters(), tests_division(), tests_functions(), tests_mul(),
      tests_other(),      tests_add(),      tests_comparison()

  };

  for (unsigned long i = 0; i < sizeof(string_test) / sizeof(string_test[0]);
       i++) {
    SRunner *sr = srunner_create(string_test[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    success += srunner_ntests_run(sr);
    srunner_free(sr);
  }
  printf("\033[31m========= FAILED : %-3d =========\033[0m\n", failed);
  printf("\033[32m========= SUCCESS : %-3d =========\033[0m\n", success);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}