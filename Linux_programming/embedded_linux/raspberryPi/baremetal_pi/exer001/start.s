.global _start

.equ GPIO_BASE, 0xFE200000
.equ GPFSEL2, 0x08

.equ GPIO_21_OUTPUT, 0x8  ;//# 1<<3

.equ GPFSET0, 0x1C
.equ GPFCLR0, 0x28

.equ GPIOVAL, 0x2000000 ;//# 1<<21 bitpos 21


_start:

  #base of our GPIO Structure
  ldr r0, =GPIO_BASE
  
  #set the GPIO 21 function as output
  ldr r1, =GPIO_21_OUTPUT
  str r1,[r0,#GPFSEL2] 

  # set counter
  ldr r2, =0x800000

loop: 
  # turn on the led
  ldr  r1, =GPIOVAL ;//#value to write to set register 
  str  r1, [r0,#GPFSET0] ; // #store in set register

 #wait for some time ,delay
 eor r10,r10,r10
 delay1:
     add r10,r10,#1
     cmp r10,r2
     bne delay1 

 #turn off the led 
 ldr r1, =GPIOVAL ;//#value to write to sest registyer
 str r1,[r0,#GPFCLR0] ;//#store in register


 #wait for some time ,delay
 eor r10,r10,r10
 delay2:
     add r10,r10,#1
     cmp r10,r2
     bne delay2 

 b loop

