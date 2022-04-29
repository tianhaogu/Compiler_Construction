	# standard Decaf preamble 
	  .text
	  .align 2
	  .globl main
  _Squash.Grow:
	# BeginFunc 16
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 16	# decrement sp to make space for locals/temps
	# _tmp0 = "But I don't like squash\n"
	  .data			# create string constant marked with label
	  _string1: .asciiz "But I don't like squash\n"
	  .text
	  la $a0, _string1	# load label
	  sw $a0, -8($fp)	# spill _tmp0 from $a0 to $fp-8
	# PushParam _tmp0
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp1 = 10
	  li $a2, 10		# load constant value 10 into $a2
	# _tmp2 = 5
	  li $a1, 5		# load constant value 5 into $a1
	# _tmp3 = _tmp1 * _tmp2
	  mul $a0, $a2, $a1	
	  sw $a0, -20($fp)	# spill _tmp3 from $a0 to $fp-20
	# PushParam _tmp3
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# LCall _PrintInt
	  jal _PrintInt      	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
	# VTable for class Squash
	  .data
	  .align 2
	  Squash:		# label for class Squash vtable
	  .word _Vegetable.Eat
	  .word _Squash.Grow
	  .text
  _Vegetable.Eat:
	# BeginFunc 40
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 40	# decrement sp to make space for locals/temps
	  lw $t2, 4($fp)	# fill this to $t2 from $fp+4
	  lw $t1, 8($fp)	# fill veg to $t1 from $fp+8
	  lw $t0, -8($fp)	# fill s to $t0 from $fp-8
	  lw $a3, -12($fp)	# fill w to $a3 from $fp-12
	# _tmp4 = 5
	  li $a2, 5		# load constant value 5 into $a2
	# _tmp5 = 2
	  li $a1, 2		# load constant value 2 into $a1
	# _tmp6 = _tmp4 % _tmp5
	  rem $a0, $a2, $a1	
	# *(this + 4) = _tmp6
	  sw $a0, 4($t2) 	# store with offset
	# _tmp7 = "Yum! "
	  .data			# create string constant marked with label
	  _string2: .asciiz "Yum! "
	  .text
	  la $a0, _string2	# load label
	  sw $t2, 4($fp)	# spill this from $t2 to $fp+4
	  sw $t1, 8($fp)	# spill veg from $t1 to $fp+8
	  sw $t0, -8($fp)	# spill s from $t0 to $fp-8
	  sw $a3, -12($fp)	# spill w from $a3 to $fp-12
	  sw $a0, -28($fp)	# spill _tmp7 from $a0 to $fp-28
	# PushParam _tmp7
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	  lw $t2, 4($fp)	# fill this to $t2 from $fp+4
	  lw $t1, 8($fp)	# fill veg to $t1 from $fp+8
	  lw $t0, -8($fp)	# fill s to $t0 from $fp-8
	  lw $a3, -12($fp)	# fill w to $a3 from $fp-12
	# _tmp8 = *(this + 4)
	  lw $a0, 4($t2) 	# load with offset
	  sw $t1, 8($fp)	# spill veg from $t1 to $fp+8
	  sw $t0, -8($fp)	# spill s from $t0 to $fp-8
	  sw $a3, -12($fp)	# spill w from $a3 to $fp-12
	  sw $a0, -32($fp)	# spill _tmp8 from $a0 to $fp-32
	# PushParam _tmp8
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# LCall _PrintInt
	  jal _PrintInt      	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	  lw $t1, 8($fp)	# fill veg to $t1 from $fp+8
	  lw $t0, -8($fp)	# fill s to $t0 from $fp-8
	  lw $a3, -12($fp)	# fill w to $a3 from $fp-12
	# _tmp9 = "\n"
	  .data			# create string constant marked with label
	  _string3: .asciiz "\n"
	  .text
	  la $a0, _string3	# load label
	  sw $t1, 8($fp)	# spill veg from $t1 to $fp+8
	  sw $t0, -8($fp)	# spill s from $t0 to $fp-8
	  sw $a3, -12($fp)	# spill w from $a3 to $fp-12
	  sw $a0, -36($fp)	# spill _tmp9 from $a0 to $fp-36
	# PushParam _tmp9
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	  lw $t1, 8($fp)	# fill veg to $t1 from $fp+8
	  lw $t0, -8($fp)	# fill s to $t0 from $fp-8
	  lw $a3, -12($fp)	# fill w to $a3 from $fp-12
	# _tmp10 = *(veg)
	  lw $a0, 0($t1) 	# load with offset
	# _tmp11 = *(_tmp10 + 4)
	  lw $v0, 4($a0) 	# load with offset
	  sw $v0, -44($fp)	# spill _tmp11 from $v0 to $fp-44
	  sw $t1, 8($fp)	# spill veg from $t1 to $fp+8
	  sw $t0, -8($fp)	# spill s from $t0 to $fp-8
	  sw $a3, -12($fp)	# spill w from $a3 to $fp-12
	# PushParam w
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a3, 4($sp)	# copy param value to stack
	# PushParam s
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t0, 4($sp)	# copy param value to stack
	# PushParam veg
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t1, 4($sp)	# copy param value to stack
	# ACall _tmp11
	  lw $v0, -44($fp)	# fill _tmp11 to $v0 from $fp-44
	  jalr $v0            	# jump to function
	# PopParams 12
	  add $sp, $sp, 12	# pop params off stack
	# Return 
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
  _Vegetable.Grow:
	# BeginFunc 12
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 12	# decrement sp to make space for locals/temps
	  lw $t2, 4($fp)	# fill this to $t2 from $fp+4
	# _tmp12 = "Grow, little vegetables, grow!\n"
	  .data			# create string constant marked with label
	  _string4: .asciiz "Grow, little vegetables, grow!\n"
	  .text
	  la $a0, _string4	# load label
	  sw $t2, 4($fp)	# spill this from $t2 to $fp+4
	  sw $a0, -8($fp)	# spill _tmp12 from $a0 to $fp-8
	# PushParam _tmp12
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	  lw $t2, 4($fp)	# fill this to $t2 from $fp+4
	# _tmp13 = *(this)
	  lw $a0, 0($t2) 	# load with offset
	# _tmp14 = *(_tmp13)
	  lw $v0, 0($a0) 	# load with offset
	  sw $v0, -16($fp)	# spill _tmp14 from $v0 to $fp-16
	  sw $t2, 4($fp)	# spill this from $t2 to $fp+4
	# PushParam this
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t2, 4($sp)	# copy param value to stack
	# PushParam this
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t2, 4($sp)	# copy param value to stack
	# ACall _tmp14
	  lw $v0, -16($fp)	# fill _tmp14 to $v0 from $fp-16
	  jalr $v0            	# jump to function
	# PopParams 8
	  add $sp, $sp, 8	# pop params off stack
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
	# VTable for class Vegetable
	  .data
	  .align 2
	  Vegetable:		# label for class Vegetable vtable
	  .word _Vegetable.Eat
	  .word _Vegetable.Grow
	  .text
  _Grow:
	# BeginFunc 4
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 4	# decrement sp to make space for locals/temps
	# _tmp15 = "mmm... veggies!\n"
	  .data			# create string constant marked with label
	  _string5: .asciiz "mmm... veggies!\n"
	  .text
	  la $a0, _string5	# load label
	  sw $a0, -8($fp)	# spill _tmp15 from $a0 to $fp-8
	# PushParam _tmp15
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
	# VTable for class Seeds
	  .data
	  .align 2
	  Seeds:		# label for class Seeds vtable
	  .text
  main:
	# BeginFunc 264
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 264	# decrement sp to make space for locals/temps
	# _tmp16 = 2
	  li $a3, 2		# load constant value 2 into $a3
	# _tmp17 = 1
	  li $a1, 1		# load constant value 1 into $a1
	# _tmp18 = _tmp16 < _tmp17
	  slt $a0, $a3, $a1	
	# IfZ _tmp18 Goto _L0
	  beqz $a0, _L0	# branch if _tmp18 is zero 
	# _tmp19 = "Decaf runtime error: Array size is <= 0\n"
	  .data			# create string constant marked with label
	  _string6: .asciiz "Decaf runtime error: Array size is <= 0\n"
	  .text
	  la $a0, _string6	# load label
	  sw $a3, -12($fp)	# spill _tmp16 from $a3 to $fp-12
	  sw $a0, -24($fp)	# spill _tmp19 from $a0 to $fp-24
	# PushParam _tmp19
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	  lw $a3, -12($fp)	# fill _tmp16 to $a3 from $fp-12
	  sw $a3, -12($fp)	# spill _tmp16 from $a3 to $fp-12
	# LCall _Halt
	  jal _Halt          	# jump to function
	  lw $a3, -12($fp)	# fill _tmp16 to $a3 from $fp-12
  _L0:
	# _tmp20 = 1
	  li $a0, 1		# load constant value 1 into $a0
	# _tmp21 = _tmp20 + _tmp16
	  add $a1, $a0, $a3	
	# _tmp22 = 4
	  li $a2, 4		# load constant value 4 into $a2
	# _tmp23 = _tmp21 * _tmp22
	  mul $a0, $a1, $a2	
	  sw $a3, -12($fp)	# spill _tmp16 from $a3 to $fp-12
	  sw $a2, -36($fp)	# spill _tmp22 from $a2 to $fp-36
	  sw $a0, -40($fp)	# spill _tmp23 from $a0 to $fp-40
	# PushParam _tmp23
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# _tmp24 = LCall _Alloc
	  jal _Alloc         	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	  lw $a3, -12($fp)	# fill _tmp16 to $a3 from $fp-12
	  lw $a2, -36($fp)	# fill _tmp22 to $a2 from $fp-36
	  lw $a1, -44($fp)	# fill _tmp24 to $a1 from $fp-44
	  move $a1, $v0		# copy function return value from $v0
	# *(_tmp24) = _tmp16
	  sw $a3, 0($a1) 	# store with offset
	# _tmp25 = _tmp24 + _tmp22
	  add $a0, $a1, $a2	
	# veggies = _tmp25
	  move $t2, $a0	# copy regs
	# _tmp26 = 0
	  li $t0, 0		# load constant value 0 into $t0
	# _tmp27 = 0
	  li $a3, 0		# load constant value 0 into $a3
	# _tmp28 = _tmp26 < _tmp27
	  slt $a2, $t0, $a3	
	# _tmp29 = *(veggies + -4)
	  lw $a1, -4($t2) 	# load with offset
	# _tmp30 = _tmp26 < _tmp29
	  slt $a0, $t0, $a1	
	# _tmp31 = _tmp30 == _tmp27
	  seq $a1, $a0, $a3	
	# _tmp32 = _tmp28 || _tmp31
	  or $a0, $a2, $a1	
	# IfZ _tmp32 Goto _L1
	  beqz $a0, _L1	# branch if _tmp32 is zero 
	# _tmp33 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string7: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $a0, _string7	# load label
	  sw $t2, -8($fp)	# spill veggies from $t2 to $fp-8
	  sw $t0, -52($fp)	# spill _tmp26 from $t0 to $fp-52
	  sw $a0, -80($fp)	# spill _tmp33 from $a0 to $fp-80
	# PushParam _tmp33
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	  lw $t2, -8($fp)	# fill veggies to $t2 from $fp-8
	  lw $t0, -52($fp)	# fill _tmp26 to $t0 from $fp-52
	  sw $t2, -8($fp)	# spill veggies from $t2 to $fp-8
	  sw $t0, -52($fp)	# spill _tmp26 from $t0 to $fp-52
	# LCall _Halt
	  jal _Halt          	# jump to function
	  lw $t2, -8($fp)	# fill veggies to $t2 from $fp-8
	  lw $t0, -52($fp)	# fill _tmp26 to $t0 from $fp-52
  _L1:
	# _tmp34 = 4
	  li $a1, 4		# load constant value 4 into $a1
	# _tmp35 = _tmp34 * _tmp26
	  mul $a0, $a1, $t0	
	# _tmp36 = veggies + _tmp35
	  add $a2, $t2, $a0	
	# _tmp37 = 12
	  li $a0, 12		# load constant value 12 into $a0
	  sw $t2, -8($fp)	# spill veggies from $t2 to $fp-8
	  sw $a2, -92($fp)	# spill _tmp36 from $a2 to $fp-92
	  sw $a0, -96($fp)	# spill _tmp37 from $a0 to $fp-96
	# PushParam _tmp37
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# _tmp38 = LCall _Alloc
	  jal _Alloc         	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	  lw $t2, -8($fp)	# fill veggies to $t2 from $fp-8
	  lw $a2, -92($fp)	# fill _tmp36 to $a2 from $fp-92
	  lw $a1, -100($fp)	# fill _tmp38 to $a1 from $fp-100
	  move $a1, $v0		# copy function return value from $v0
	# _tmp39 = Squash
	  la $a0, Squash	# load label
	# *(_tmp38) = _tmp39
	  sw $a0, 0($a1) 	# store with offset
	# *(_tmp36) = _tmp38
	  sw $a1, 0($a2) 	# store with offset
	# _tmp40 = 1
	  li $t0, 1		# load constant value 1 into $t0
	# _tmp41 = 0
	  li $a3, 0		# load constant value 0 into $a3
	# _tmp42 = _tmp40 < _tmp41
	  slt $a2, $t0, $a3	
	# _tmp43 = *(veggies + -4)
	  lw $a1, -4($t2) 	# load with offset
	# _tmp44 = _tmp40 < _tmp43
	  slt $a0, $t0, $a1	
	# _tmp45 = _tmp44 == _tmp41
	  seq $a1, $a0, $a3	
	# _tmp46 = _tmp42 || _tmp45
	  or $a0, $a2, $a1	
	# IfZ _tmp46 Goto _L2
	  beqz $a0, _L2	# branch if _tmp46 is zero 
	# _tmp47 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string8: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $a0, _string8	# load label
	  sw $t2, -8($fp)	# spill veggies from $t2 to $fp-8
	  sw $t0, -108($fp)	# spill _tmp40 from $t0 to $fp-108
	  sw $a0, -136($fp)	# spill _tmp47 from $a0 to $fp-136
	# PushParam _tmp47
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	  lw $t2, -8($fp)	# fill veggies to $t2 from $fp-8
	  lw $t0, -108($fp)	# fill _tmp40 to $t0 from $fp-108
	  sw $t2, -8($fp)	# spill veggies from $t2 to $fp-8
	  sw $t0, -108($fp)	# spill _tmp40 from $t0 to $fp-108
	# LCall _Halt
	  jal _Halt          	# jump to function
	  lw $t2, -8($fp)	# fill veggies to $t2 from $fp-8
	  lw $t0, -108($fp)	# fill _tmp40 to $t0 from $fp-108
  _L2:
	# _tmp48 = 4
	  li $a1, 4		# load constant value 4 into $a1
	# _tmp49 = _tmp48 * _tmp40
	  mul $a0, $a1, $t0	
	# _tmp50 = veggies + _tmp49
	  add $a2, $t2, $a0	
	# _tmp51 = 12
	  li $a0, 12		# load constant value 12 into $a0
	  sw $t2, -8($fp)	# spill veggies from $t2 to $fp-8
	  sw $a2, -148($fp)	# spill _tmp50 from $a2 to $fp-148
	  sw $a0, -152($fp)	# spill _tmp51 from $a0 to $fp-152
	# PushParam _tmp51
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# _tmp52 = LCall _Alloc
	  jal _Alloc         	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	  lw $t2, -8($fp)	# fill veggies to $t2 from $fp-8
	  lw $a2, -148($fp)	# fill _tmp50 to $a2 from $fp-148
	  lw $a1, -156($fp)	# fill _tmp52 to $a1 from $fp-156
	  move $a1, $v0		# copy function return value from $v0
	# _tmp53 = Vegetable
	  la $a0, Vegetable	# load label
	# *(_tmp52) = _tmp53
	  sw $a0, 0($a1) 	# store with offset
	# *(_tmp50) = _tmp52
	  sw $a1, 0($a2) 	# store with offset
	# _tmp54 = 10
	  li $a0, 10		# load constant value 10 into $a0
	  sw $t2, -8($fp)	# spill veggies from $t2 to $fp-8
	  sw $a0, -164($fp)	# spill _tmp54 from $a0 to $fp-164
	# PushParam _tmp54
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# LCall _Grow
	  jal _Grow          	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	  lw $t2, -8($fp)	# fill veggies to $t2 from $fp-8
	# _tmp55 = 0
	  li $t0, 0		# load constant value 0 into $t0
	# _tmp56 = 0
	  li $a3, 0		# load constant value 0 into $a3
	# _tmp57 = _tmp55 < _tmp56
	  slt $a2, $t0, $a3	
	# _tmp58 = *(veggies + -4)
	  lw $a1, -4($t2) 	# load with offset
	# _tmp59 = _tmp55 < _tmp58
	  slt $a0, $t0, $a1	
	# _tmp60 = _tmp59 == _tmp56
	  seq $a1, $a0, $a3	
	# _tmp61 = _tmp57 || _tmp60
	  or $a0, $a2, $a1	
	# IfZ _tmp61 Goto _L3
	  beqz $a0, _L3	# branch if _tmp61 is zero 
	# _tmp62 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string9: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $a0, _string9	# load label
	  sw $t2, -8($fp)	# spill veggies from $t2 to $fp-8
	  sw $t0, -168($fp)	# spill _tmp55 from $t0 to $fp-168
	  sw $a0, -196($fp)	# spill _tmp62 from $a0 to $fp-196
	# PushParam _tmp62
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	  lw $t2, -8($fp)	# fill veggies to $t2 from $fp-8
	  lw $t0, -168($fp)	# fill _tmp55 to $t0 from $fp-168
	  sw $t2, -8($fp)	# spill veggies from $t2 to $fp-8
	  sw $t0, -168($fp)	# spill _tmp55 from $t0 to $fp-168
	# LCall _Halt
	  jal _Halt          	# jump to function
	  lw $t2, -8($fp)	# fill veggies to $t2 from $fp-8
	  lw $t0, -168($fp)	# fill _tmp55 to $t0 from $fp-168
  _L3:
	# _tmp63 = 4
	  li $a0, 4		# load constant value 4 into $a0
	# _tmp64 = _tmp63 * _tmp55
	  mul $a1, $a0, $t0	
	# _tmp65 = veggies + _tmp64
	  add $a0, $t2, $a1	
	# _tmp66 = *(_tmp65)
	  lw $t1, 0($a0) 	# load with offset
	# _tmp67 = 1
	  li $t0, 1		# load constant value 1 into $t0
	# _tmp68 = 0
	  li $a3, 0		# load constant value 0 into $a3
	# _tmp69 = _tmp67 < _tmp68
	  slt $a2, $t0, $a3	
	# _tmp70 = *(veggies + -4)
	  lw $a1, -4($t2) 	# load with offset
	# _tmp71 = _tmp67 < _tmp70
	  slt $a0, $t0, $a1	
	# _tmp72 = _tmp71 == _tmp68
	  seq $a1, $a0, $a3	
	# _tmp73 = _tmp69 || _tmp72
	  or $a0, $a2, $a1	
	# IfZ _tmp73 Goto _L4
	  beqz $a0, _L4	# branch if _tmp73 is zero 
	# _tmp74 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string10: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $a0, _string10	# load label
	  sw $t2, -8($fp)	# spill veggies from $t2 to $fp-8
	  sw $t1, -212($fp)	# spill _tmp66 from $t1 to $fp-212
	  sw $t0, -216($fp)	# spill _tmp67 from $t0 to $fp-216
	  sw $a0, -244($fp)	# spill _tmp74 from $a0 to $fp-244
	# PushParam _tmp74
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	  lw $t2, -8($fp)	# fill veggies to $t2 from $fp-8
	  lw $t1, -212($fp)	# fill _tmp66 to $t1 from $fp-212
	  lw $t0, -216($fp)	# fill _tmp67 to $t0 from $fp-216
	  sw $t2, -8($fp)	# spill veggies from $t2 to $fp-8
	  sw $t1, -212($fp)	# spill _tmp66 from $t1 to $fp-212
	  sw $t0, -216($fp)	# spill _tmp67 from $t0 to $fp-216
	# LCall _Halt
	  jal _Halt          	# jump to function
	  lw $t2, -8($fp)	# fill veggies to $t2 from $fp-8
	  lw $t1, -212($fp)	# fill _tmp66 to $t1 from $fp-212
	  lw $t0, -216($fp)	# fill _tmp67 to $t0 from $fp-216
  _L4:
	# _tmp75 = 4
	  li $a0, 4		# load constant value 4 into $a0
	# _tmp76 = _tmp75 * _tmp67
	  mul $a1, $a0, $t0	
	# _tmp77 = veggies + _tmp76
	  add $a0, $t2, $a1	
	# _tmp78 = *(_tmp77)
	  lw $a1, 0($a0) 	# load with offset
	# _tmp79 = *(_tmp78)
	  lw $a0, 0($a1) 	# load with offset
	# _tmp80 = *(_tmp79)
	  lw $v0, 0($a0) 	# load with offset
	  sw $v0, -268($fp)	# spill _tmp80 from $v0 to $fp-268
	  sw $t1, -212($fp)	# spill _tmp66 from $t1 to $fp-212
	  sw $a1, -260($fp)	# spill _tmp78 from $a1 to $fp-260
	# PushParam _tmp66
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t1, 4($sp)	# copy param value to stack
	# PushParam _tmp78
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $a1, 4($sp)	# copy param value to stack
	# ACall _tmp80
	  lw $v0, -268($fp)	# fill _tmp80 to $v0 from $fp-268
	  jalr $v0            	# jump to function
	# PopParams 8
	  add $sp, $sp, 8	# pop params off stack
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
  _PrintInt:
	  subu $sp, $sp, 8	# decrement sp to make space to save ra,fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  lw $a0, 4($fp)	# fill a from $fp+4
	# LCall _PrintInt
	  li $v0, 1
	  syscall
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function

  _ReadInteger:
	  subu $sp, $sp, 8	# decrement sp to make space to save ra,fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  li $v0, 5
	  syscall
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function


  _PrintBool:
	  subu $sp, $sp, 8      # decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)        # save fp
	  sw $ra, 4($sp)        # save ra
	  addiu $fp, $sp, 8     # set up new fp
	  lw $a0, 4($fp)        # fill a from $fp+4
	  li $v0, 4
	  beq $a0, $0, PrintBoolFalse
	  la $a0, _PrintBoolTrueString
	  j PrintBoolEnd
  PrintBoolFalse:
 	  la $a0, _PrintBoolFalseString
  PrintBoolEnd:
	  syscall
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp         # pop callee frame off stack
	  lw $ra, -4($fp)       # restore saved ra
	  lw $fp, 0($fp)        # restore saved fp
	  jr $ra                # return from function

      .data			# create string constant marked with label
      _PrintBoolTrueString: .asciiz "true"
      .text

      .data			# create string constant marked with label
      _PrintBoolFalseString: .asciiz "false"
      .text

  _PrintString:
	  subu $sp, $sp, 8      # decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)        # save fp
	  sw $ra, 4($sp)        # save ra
	  addiu $fp, $sp, 8     # set up new fp
	  lw $a0, 4($fp)        # fill a from $fp+4
	  li $v0, 4
	  syscall
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp         # pop callee frame off stack
	  lw $ra, -4($fp)       # restore saved ra
	  lw $fp, 0($fp)        # restore saved fp
	  jr $ra                # return from function

  _Alloc:
	  subu $sp, $sp, 8      # decrement sp to make space to save ra,fp
	  sw $fp, 8($sp)        # save fp
	  sw $ra, 4($sp)        # save ra
	  addiu $fp, $sp, 8     # set up new fp
	  lw $a0, 4($fp)        # fill a from $fp+4
	  li $v0, 9
	  syscall
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp         # pop callee frame off stack
	  lw $ra, -4($fp)       # restore saved ra
	  lw $fp, 0($fp)        # restore saved fp
	  jr $ra                # return from function

  _Halt:
	  li $v0, 10
	  syscall
	# EndFunc


  _StringEqual:
	  subu $sp, $sp, 8      # decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)        # save fp
	  sw $ra, 4($sp)        # save ra
	  addiu $fp, $sp, 8     # set up new fp
	  lw $a0, 4($fp)        # fill a from $fp+4
	  lw $a1, 8($fp)        # fill a from $fp+8
	  beq $a0,$a1,Lrunt10
  Lrunt12:
	  lbu  $v0,($a0)
	  lbu  $a2,($a1)
	  bne $v0,$a2,Lrunt11
	  addiu $a0,$a0,1
	  addiu $a1,$a1,1
	  bne $v0,$0,Lrunt12
      li  $v0,1
      j Lrunt10
  Lrunt11:
	  li  $v0,0
  Lrunt10:
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp         # pop callee frame off stack
	  lw $ra, -4($fp)       # restore saved ra
	  lw $fp, 0($fp)        # restore saved fp
	  jr $ra                # return from function



  _ReadLine:
	  subu $sp, $sp, 8      # decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)        # save fp
	  sw $ra, 4($sp)        # save ra
	  addiu $fp, $sp, 8     # set up new fp
	  li $a0, 101
	  li $v0, 9
	  syscall
	  addi $a0, $v0, 0
	  li $v0, 8
	  li $a1,101 
	  syscall
	  addiu $v0,$a0,0       # pointer to begin of string
  Lrunt21:
	  lb $a1,($a0)          # load character at pointer
	  addiu $a0,$a0,1       # forward pointer
	  bnez $a1,Lrunt21      # loop until end of string is reached
	  lb $a1,-2($a0)        # load character before end of string
	  li $a2,10             # newline character	  bneq $a1,$a2,Lrunt20  # do not remove last character if not newline
	  sb $0,-2($a0)         # Add the terminating character in its place
  Lrunt20:
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp         # pop callee frame off stack
	  lw $ra, -4($fp)       # restore saved ra
	  lw $fp, 0($fp)        # restore saved fp
	  jr $ra                # return from function
