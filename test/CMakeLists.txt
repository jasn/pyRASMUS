macro(add_unittest NAME)
  add_executable(ut-${NAME} ${NAME}.cc common.hh)
  target_link_libraries(ut-${NAME} testlib stdlib frontend)
  set(MTESTS ${ARGV})
  list(REMOVE_AT MTESTS 0)
  foreach(TEST ${MTESTS})
    add_test(${NAME}_${TEST} ut-${NAME} ${TEST})
  endforeach(TEST)
endmacro(add_unittest)

add_unittest(stdlib-text construct concat substring)
add_unittest(frontend-lexer base)
add_unittest(types equality subset union intersection)
add_unittest(frontend-parser base)
add_unittest(frontend-integration builtins base integer bool comments relation if text tuple relation_external crash)
add_unittest(stdlib-relation loadAndSave)


add_executable(int-speed-test int-speed-test.cc)
