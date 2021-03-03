  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
.global delay
.global time2string
.data
.text

hexasc:
	andi $a0,$a0, 0xf #Checks 4 LSB
	addi $v0,$a0,0x30 
	jr $ra
	nop

delay:
	PUSH $s3
	li $s3, 47000
	li $t6, 0
	li $t7, 0
	j loop
	nop
	loop:
		beq $t7, $a0, end
		nop
		sub $a0, $a0, 1
		j loop2
		nop
		loop2:
			beq $t6, $s3, loop
			nop
			addi $t6, $t6, 1
			j loop2
			nop
	end:
	
	POP $s3
	
 	jr $ra
 	nop
 	
time2string:
	PUSH $s0
	PUSH $s1
	PUSH $ra
	PUSH $a0
	add $s0,$a1,$0 #Saves time info to t0
	add $s1,$a0,$0 #Saves time info address to t1
	
	srl $a0,$s0,12 # Första minut-talet
	jal hexasc
	nop
	sb $v0, 0($s1)
	
	srl $a0,$s0,8 # Andra minut-talet
	jal hexasc
	nop
	sb $v0, 1($s1)
	
	li $t4, 0x3A		#Contains ":"
	nop
	sb $t4, 2($s1) # Lägger till kolon
	
	srl $a0,$s0,4 # första sekund-talet
	jal hexasc
	nop
	sb $v0, 3($s1)
	
	add $a0, $s0, $zero # andra sekund-talet
	jal hexasc
	nop
	sb $v0, 4($s1)
	
	li $t5,0x00
	nop
	sb $t5, 5($s1)
	
	POP $a0
	POP $ra
	POP $s1
	POP $s0
	
	jr $ra
	nop
	
