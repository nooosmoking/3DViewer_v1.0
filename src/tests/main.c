
#include "test.h"

int main(void) {
  SRunner *sr = srunner_create(suite_s21_validate());
  srunner_set_fork_status(sr, CK_NOFORK);
  int nf;
  srunner_run_all(sr, CK_NORMAL);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
