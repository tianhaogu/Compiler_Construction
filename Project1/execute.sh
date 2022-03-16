set -x

rm samples/test_*.out

./dcc < samples/badbool.frag > samples/test_badbool.out 2>&1
diff samples/badbool.out samples/test_badbool.out

./dcc < samples/badint.frag > samples/test_badint.out 2>&1
diff samples/badint.out samples/test_badint.out

./dcc < samples/baddouble.frag > samples/test_baddouble.out 2>&1
diff samples/baddouble.out samples/test_baddouble.out

./dcc < samples/badstring.frag > samples/test_badstring.out 2>&1
diff samples/badstring.out samples/test_badstring.out

./dcc < samples/badident.frag > samples/test_badident.out 2>&1
diff samples/badident.out samples/test_badident.out

./dcc < samples/badop.frag > samples/test_badop.out 2>&1
diff samples/badop.out samples/test_badop.out

./dcc < samples/badreserve.frag > samples/test_badreserve.out 2>&1
diff samples/badreserve.out samples/test_badreserve.out

./dcc < samples/string.frag > samples/test_string.out 2>&1
diff samples/string.out samples/test_string.out

./dcc < samples/ident.frag > samples/test_ident.out 2>&1
diff samples/ident.out samples/test_ident.out

./dcc < samples/reserve_op.frag > samples/test_reserve_op.out 2>&1
diff samples/reserve_op.out samples/test_reserve_op.out

./dcc < samples/number.frag > samples/test_number.out 2>&1
diff samples/number.out samples/test_number.out

./dcc < samples/program2.decaf > samples/test_program2.out 2>&1
diff samples/program2.out samples/test_program2.out

./dcc < samples/badpre.frag > samples/test_badpre.out 2>&1
diff samples/badpre.out samples/test_badpre.out

./dcc < samples/comment.frag > samples/test_comment.out 2>&1
diff samples/comment.out samples/test_comment.out

./dcc < samples/define.frag > samples/test_define.out 2>&1
diff samples/define.out samples/test_define.out

./dcc < samples/program3.decaf > samples/test_program3.out 2>&1
diff samples/program3.out samples/test_program3.out