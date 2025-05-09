
sylib.o:     file format elf64-loongarch


Disassembly of section .text:

0000000000000000 <getint>:
   0:	02ff8063 	addi.d      	$sp, $sp, -32(0xfe0)
   4:	29c06061 	st.d        	$ra, $sp, 24(0x18)
   8:	29c04076 	st.d        	$fp, $sp, 16(0x10)
   c:	02c08076 	addi.d      	$fp, $sp, 32(0x20)
  10:	1a000004 	pcalau12i   	$a0, 0
  14:	02c00084 	addi.d      	$a0, $a0, 0
  18:	02ffb2c5 	addi.d      	$a1, $fp, -20(0xfec)
  1c:	54000000 	bl          	0	# 1c <getint+0x1c>
  20:	28bfb2c4 	ld.w        	$a0, $fp, -20(0xfec)
  24:	28c04076 	ld.d        	$fp, $sp, 16(0x10)
  28:	28c06061 	ld.d        	$ra, $sp, 24(0x18)
  2c:	02c08063 	addi.d      	$sp, $sp, 32(0x20)
  30:	4c000020 	jirl        	$zero, $ra, 0

0000000000000034 <getch>:
  34:	02ff8063 	addi.d      	$sp, $sp, -32(0xfe0)
  38:	29c06061 	st.d        	$ra, $sp, 24(0x18)
  3c:	29c04076 	st.d        	$fp, $sp, 16(0x10)
  40:	02c08076 	addi.d      	$fp, $sp, 32(0x20)
  44:	1a000004 	pcalau12i   	$a0, 0
  48:	02c00084 	addi.d      	$a0, $a0, 0
  4c:	02ffbec5 	addi.d      	$a1, $fp, -17(0xfef)
  50:	54000000 	bl          	0	# 50 <getch+0x1c>
  54:	283fbec4 	ld.b        	$a0, $fp, -17(0xfef)
  58:	28c04076 	ld.d        	$fp, $sp, 16(0x10)
  5c:	28c06061 	ld.d        	$ra, $sp, 24(0x18)
  60:	02c08063 	addi.d      	$sp, $sp, 32(0x20)
  64:	4c000020 	jirl        	$zero, $ra, 0

0000000000000068 <getfloat>:
  68:	02ff8063 	addi.d      	$sp, $sp, -32(0xfe0)
  6c:	29c06061 	st.d        	$ra, $sp, 24(0x18)
  70:	29c04076 	st.d        	$fp, $sp, 16(0x10)
  74:	02c08076 	addi.d      	$fp, $sp, 32(0x20)
  78:	1a000004 	pcalau12i   	$a0, 0
  7c:	02c00084 	addi.d      	$a0, $a0, 0
  80:	02ffb2c5 	addi.d      	$a1, $fp, -20(0xfec)
  84:	54000000 	bl          	0	# 84 <getfloat+0x1c>
  88:	2b3fb2c0 	fld.s       	$fa0, $fp, -20(0xfec)
  8c:	28c04076 	ld.d        	$fp, $sp, 16(0x10)
  90:	28c06061 	ld.d        	$ra, $sp, 24(0x18)
  94:	02c08063 	addi.d      	$sp, $sp, 32(0x20)
  98:	4c000020 	jirl        	$zero, $ra, 0

000000000000009c <getarray>:
  9c:	02ff8063 	addi.d      	$sp, $sp, -32(0xfe0)
  a0:	29c06061 	st.d        	$ra, $sp, 24(0x18)
  a4:	29c04076 	st.d        	$fp, $sp, 16(0x10)
  a8:	02c08076 	addi.d      	$fp, $sp, 32(0x20)
  ac:	29ffa2c4 	st.d        	$a0, $fp, -24(0xfe8)
  b0:	1a000004 	pcalau12i   	$a0, 0
  b4:	02c00084 	addi.d      	$a0, $a0, 0
  b8:	02ff92c5 	addi.d      	$a1, $fp, -28(0xfe4)
  bc:	54000000 	bl          	0	# bc <getarray+0x20>
  c0:	00150004 	move        	$a0, $zero
  c4:	29bf82c4 	st.w        	$a0, $fp, -32(0xfe0)
  c8:	50000400 	b           	4(0x4)	# cc <getarray+0x30>
  cc:	28bf82c4 	ld.w        	$a0, $fp, -32(0xfe0)
  d0:	28bf92c5 	ld.w        	$a1, $fp, -28(0xfe4)
  d4:	64003485 	bge         	$a0, $a1, 52(0x34)	# 108 <getarray+0x6c>
  d8:	50000400 	b           	4(0x4)	# dc <getarray+0x40>
  dc:	28ffa2c5 	ld.d        	$a1, $fp, -24(0xfe8)
  e0:	28bf82c4 	ld.w        	$a0, $fp, -32(0xfe0)
  e4:	002c9485 	alsl.d      	$a1, $a0, $a1, 0x2
  e8:	1a000004 	pcalau12i   	$a0, 0
  ec:	02c00084 	addi.d      	$a0, $a0, 0
  f0:	54000000 	bl          	0	# f0 <getarray+0x54>
  f4:	50000400 	b           	4(0x4)	# f8 <getarray+0x5c>
  f8:	28bf82c4 	ld.w        	$a0, $fp, -32(0xfe0)
  fc:	02c00484 	addi.d      	$a0, $a0, 1(0x1)
 100:	29bf82c4 	st.w        	$a0, $fp, -32(0xfe0)
 104:	53ffcbff 	b           	-56(0xfffffc8)	# cc <getarray+0x30>
 108:	28bf92c4 	ld.w        	$a0, $fp, -28(0xfe4)
 10c:	28c04076 	ld.d        	$fp, $sp, 16(0x10)
 110:	28c06061 	ld.d        	$ra, $sp, 24(0x18)
 114:	02c08063 	addi.d      	$sp, $sp, 32(0x20)
 118:	4c000020 	jirl        	$zero, $ra, 0

000000000000011c <getfarray>:
 11c:	02ff8063 	addi.d      	$sp, $sp, -32(0xfe0)
 120:	29c06061 	st.d        	$ra, $sp, 24(0x18)
 124:	29c04076 	st.d        	$fp, $sp, 16(0x10)
 128:	02c08076 	addi.d      	$fp, $sp, 32(0x20)
 12c:	29ffa2c4 	st.d        	$a0, $fp, -24(0xfe8)
 130:	1a000004 	pcalau12i   	$a0, 0
 134:	02c00084 	addi.d      	$a0, $a0, 0
 138:	02ff92c5 	addi.d      	$a1, $fp, -28(0xfe4)
 13c:	54000000 	bl          	0	# 13c <getfarray+0x20>
 140:	00150004 	move        	$a0, $zero
 144:	29bf82c4 	st.w        	$a0, $fp, -32(0xfe0)
 148:	50000400 	b           	4(0x4)	# 14c <getfarray+0x30>
 14c:	28bf82c4 	ld.w        	$a0, $fp, -32(0xfe0)
 150:	28bf92c5 	ld.w        	$a1, $fp, -28(0xfe4)
 154:	64003485 	bge         	$a0, $a1, 52(0x34)	# 188 <getfarray+0x6c>
 158:	50000400 	b           	4(0x4)	# 15c <getfarray+0x40>
 15c:	28ffa2c5 	ld.d        	$a1, $fp, -24(0xfe8)
 160:	28bf82c4 	ld.w        	$a0, $fp, -32(0xfe0)
 164:	002c9485 	alsl.d      	$a1, $a0, $a1, 0x2
 168:	1a000004 	pcalau12i   	$a0, 0
 16c:	02c00084 	addi.d      	$a0, $a0, 0
 170:	54000000 	bl          	0	# 170 <getfarray+0x54>
 174:	50000400 	b           	4(0x4)	# 178 <getfarray+0x5c>
 178:	28bf82c4 	ld.w        	$a0, $fp, -32(0xfe0)
 17c:	02c00484 	addi.d      	$a0, $a0, 1(0x1)
 180:	29bf82c4 	st.w        	$a0, $fp, -32(0xfe0)
 184:	53ffcbff 	b           	-56(0xfffffc8)	# 14c <getfarray+0x30>
 188:	28bf92c4 	ld.w        	$a0, $fp, -28(0xfe4)
 18c:	28c04076 	ld.d        	$fp, $sp, 16(0x10)
 190:	28c06061 	ld.d        	$ra, $sp, 24(0x18)
 194:	02c08063 	addi.d      	$sp, $sp, 32(0x20)
 198:	4c000020 	jirl        	$zero, $ra, 0

000000000000019c <putint>:
 19c:	02ff8063 	addi.d      	$sp, $sp, -32(0xfe0)
 1a0:	29c06061 	st.d        	$ra, $sp, 24(0x18)
 1a4:	29c04076 	st.d        	$fp, $sp, 16(0x10)
 1a8:	02c08076 	addi.d      	$fp, $sp, 32(0x20)
 1ac:	29bfb2c4 	st.w        	$a0, $fp, -20(0xfec)
 1b0:	28bfb2c5 	ld.w        	$a1, $fp, -20(0xfec)
 1b4:	1a000004 	pcalau12i   	$a0, 0
 1b8:	02c00084 	addi.d      	$a0, $a0, 0
 1bc:	54000000 	bl          	0	# 1bc <putint+0x20>
 1c0:	28c04076 	ld.d        	$fp, $sp, 16(0x10)
 1c4:	28c06061 	ld.d        	$ra, $sp, 24(0x18)
 1c8:	02c08063 	addi.d      	$sp, $sp, 32(0x20)
 1cc:	4c000020 	jirl        	$zero, $ra, 0

00000000000001d0 <putch>:
 1d0:	02ff8063 	addi.d      	$sp, $sp, -32(0xfe0)
 1d4:	29c06061 	st.d        	$ra, $sp, 24(0x18)
 1d8:	29c04076 	st.d        	$fp, $sp, 16(0x10)
 1dc:	02c08076 	addi.d      	$fp, $sp, 32(0x20)
 1e0:	29bfb2c4 	st.w        	$a0, $fp, -20(0xfec)
 1e4:	28bfb2c5 	ld.w        	$a1, $fp, -20(0xfec)
 1e8:	1a000004 	pcalau12i   	$a0, 0
 1ec:	02c00084 	addi.d      	$a0, $a0, 0
 1f0:	54000000 	bl          	0	# 1f0 <putch+0x20>
 1f4:	28c04076 	ld.d        	$fp, $sp, 16(0x10)
 1f8:	28c06061 	ld.d        	$ra, $sp, 24(0x18)
 1fc:	02c08063 	addi.d      	$sp, $sp, 32(0x20)
 200:	4c000020 	jirl        	$zero, $ra, 0

0000000000000204 <putarray>:
 204:	02ff4063 	addi.d      	$sp, $sp, -48(0xfd0)
 208:	29c0a061 	st.d        	$ra, $sp, 40(0x28)
 20c:	29c08076 	st.d        	$fp, $sp, 32(0x20)
 210:	02c0c076 	addi.d      	$fp, $sp, 48(0x30)
 214:	29bfb2c4 	st.w        	$a0, $fp, -20(0xfec)
 218:	29ff82c5 	st.d        	$a1, $fp, -32(0xfe0)
 21c:	28bfb2c5 	ld.w        	$a1, $fp, -20(0xfec)
 220:	1a000004 	pcalau12i   	$a0, 0
 224:	02c00084 	addi.d      	$a0, $a0, 0
 228:	54000000 	bl          	0	# 228 <putarray+0x24>
 22c:	00150004 	move        	$a0, $zero
 230:	29bf72c4 	st.w        	$a0, $fp, -36(0xfdc)
 234:	50000400 	b           	4(0x4)	# 238 <putarray+0x34>
 238:	28bf72c4 	ld.w        	$a0, $fp, -36(0xfdc)
 23c:	28bfb2c5 	ld.w        	$a1, $fp, -20(0xfec)
 240:	64003885 	bge         	$a0, $a1, 56(0x38)	# 278 <putarray+0x74>
 244:	50000400 	b           	4(0x4)	# 248 <putarray+0x44>
 248:	28ff82c4 	ld.d        	$a0, $fp, -32(0xfe0)
 24c:	28bf72c5 	ld.w        	$a1, $fp, -36(0xfdc)
 250:	004108a5 	slli.d      	$a1, $a1, 0x2
 254:	38081485 	ldx.w       	$a1, $a0, $a1
 258:	1a000004 	pcalau12i   	$a0, 0
 25c:	02c00084 	addi.d      	$a0, $a0, 0
 260:	54000000 	bl          	0	# 260 <putarray+0x5c>
 264:	50000400 	b           	4(0x4)	# 268 <putarray+0x64>
 268:	28bf72c4 	ld.w        	$a0, $fp, -36(0xfdc)
 26c:	02c00484 	addi.d      	$a0, $a0, 1(0x1)
 270:	29bf72c4 	st.w        	$a0, $fp, -36(0xfdc)
 274:	53ffc7ff 	b           	-60(0xfffffc4)	# 238 <putarray+0x34>
 278:	1a000004 	pcalau12i   	$a0, 0
 27c:	02c00084 	addi.d      	$a0, $a0, 0
 280:	54000000 	bl          	0	# 280 <putarray+0x7c>
 284:	28c08076 	ld.d        	$fp, $sp, 32(0x20)
 288:	28c0a061 	ld.d        	$ra, $sp, 40(0x28)
 28c:	02c0c063 	addi.d      	$sp, $sp, 48(0x30)
 290:	4c000020 	jirl        	$zero, $ra, 0

0000000000000294 <putfloat>:
 294:	02ff8063 	addi.d      	$sp, $sp, -32(0xfe0)
 298:	29c06061 	st.d        	$ra, $sp, 24(0x18)
 29c:	29c04076 	st.d        	$fp, $sp, 16(0x10)
 2a0:	02c08076 	addi.d      	$fp, $sp, 32(0x20)
 2a4:	2b7fb2c0 	fst.s       	$fa0, $fp, -20(0xfec)
 2a8:	2b3fb2c0 	fld.s       	$fa0, $fp, -20(0xfec)
 2ac:	01192400 	fcvt.d.s    	$fa0, $fa0
 2b0:	0114b805 	movfr2gr.d  	$a1, $fa0
 2b4:	1a000004 	pcalau12i   	$a0, 0
 2b8:	02c00084 	addi.d      	$a0, $a0, 0
 2bc:	54000000 	bl          	0	# 2bc <putfloat+0x28>
 2c0:	28c04076 	ld.d        	$fp, $sp, 16(0x10)
 2c4:	28c06061 	ld.d        	$ra, $sp, 24(0x18)
 2c8:	02c08063 	addi.d      	$sp, $sp, 32(0x20)
 2cc:	4c000020 	jirl        	$zero, $ra, 0

00000000000002d0 <putfarray>:
 2d0:	02ff4063 	addi.d      	$sp, $sp, -48(0xfd0)
 2d4:	29c0a061 	st.d        	$ra, $sp, 40(0x28)
 2d8:	29c08076 	st.d        	$fp, $sp, 32(0x20)
 2dc:	02c0c076 	addi.d      	$fp, $sp, 48(0x30)
 2e0:	29bfb2c4 	st.w        	$a0, $fp, -20(0xfec)
 2e4:	29ff82c5 	st.d        	$a1, $fp, -32(0xfe0)
 2e8:	28bfb2c5 	ld.w        	$a1, $fp, -20(0xfec)
 2ec:	1a000004 	pcalau12i   	$a0, 0
 2f0:	02c00084 	addi.d      	$a0, $a0, 0
 2f4:	54000000 	bl          	0	# 2f4 <putfarray+0x24>
 2f8:	00150004 	move        	$a0, $zero
 2fc:	29bf72c4 	st.w        	$a0, $fp, -36(0xfdc)
 300:	50000400 	b           	4(0x4)	# 304 <putfarray+0x34>
 304:	28bf72c4 	ld.w        	$a0, $fp, -36(0xfdc)
 308:	28bfb2c5 	ld.w        	$a1, $fp, -20(0xfec)
 30c:	64004085 	bge         	$a0, $a1, 64(0x40)	# 34c <putfarray+0x7c>
 310:	50000400 	b           	4(0x4)	# 314 <putfarray+0x44>
 314:	28ff82c4 	ld.d        	$a0, $fp, -32(0xfe0)
 318:	28bf72c5 	ld.w        	$a1, $fp, -36(0xfdc)
 31c:	004108a5 	slli.d      	$a1, $a1, 0x2
 320:	38301480 	fldx.s      	$fa0, $a0, $a1
 324:	01192400 	fcvt.d.s    	$fa0, $fa0
 328:	0114b805 	movfr2gr.d  	$a1, $fa0
 32c:	1a000004 	pcalau12i   	$a0, 0
 330:	02c00084 	addi.d      	$a0, $a0, 0
 334:	54000000 	bl          	0	# 334 <putfarray+0x64>
 338:	50000400 	b           	4(0x4)	# 33c <putfarray+0x6c>
 33c:	28bf72c4 	ld.w        	$a0, $fp, -36(0xfdc)
 340:	02c00484 	addi.d      	$a0, $a0, 1(0x1)
 344:	29bf72c4 	st.w        	$a0, $fp, -36(0xfdc)
 348:	53ffbfff 	b           	-68(0xfffffbc)	# 304 <putfarray+0x34>
 34c:	1a000004 	pcalau12i   	$a0, 0
 350:	02c00084 	addi.d      	$a0, $a0, 0
 354:	54000000 	bl          	0	# 354 <putfarray+0x84>
 358:	28c08076 	ld.d        	$fp, $sp, 32(0x20)
 35c:	28c0a061 	ld.d        	$ra, $sp, 40(0x28)
 360:	02c0c063 	addi.d      	$sp, $sp, 48(0x30)
 364:	4c000020 	jirl        	$zero, $ra, 0

0000000000000368 <putf>:
 368:	02fe8063 	addi.d      	$sp, $sp, -96(0xfa0)
 36c:	29c06061 	st.d        	$ra, $sp, 24(0x18)
 370:	29c04076 	st.d        	$fp, $sp, 16(0x10)
 374:	02c08076 	addi.d      	$fp, $sp, 32(0x20)
 378:	29c0e2cb 	st.d        	$a7, $fp, 56(0x38)
 37c:	29c0c2ca 	st.d        	$a6, $fp, 48(0x30)
 380:	29c0a2c9 	st.d        	$a5, $fp, 40(0x28)
 384:	29c082c8 	st.d        	$a4, $fp, 32(0x20)
 388:	29c062c7 	st.d        	$a3, $fp, 24(0x18)
 38c:	29c042c6 	st.d        	$a2, $fp, 16(0x10)
 390:	29c022c5 	st.d        	$a1, $fp, 8(0x8)
 394:	29ffa2c4 	st.d        	$a0, $fp, -24(0xfe8)
 398:	02c022c4 	addi.d      	$a0, $fp, 8(0x8)
 39c:	29ff82c4 	st.d        	$a0, $fp, -32(0xfe0)
 3a0:	1a000004 	pcalau12i   	$a0, 0
 3a4:	28c00084 	ld.d        	$a0, $a0, 0
 3a8:	28c00084 	ld.d        	$a0, $a0, 0
 3ac:	28ffa2c5 	ld.d        	$a1, $fp, -24(0xfe8)
 3b0:	28ff82c6 	ld.d        	$a2, $fp, -32(0xfe0)
 3b4:	54000000 	bl          	0	# 3b4 <putf+0x4c>
 3b8:	28c04076 	ld.d        	$fp, $sp, 16(0x10)
 3bc:	28c06061 	ld.d        	$ra, $sp, 24(0x18)
 3c0:	02c18063 	addi.d      	$sp, $sp, 96(0x60)
 3c4:	4c000020 	jirl        	$zero, $ra, 0

00000000000003c8 <before_main>:
 3c8:	02ff8063 	addi.d      	$sp, $sp, -32(0xfe0)
 3cc:	29c06061 	st.d        	$ra, $sp, 24(0x18)
 3d0:	29c04076 	st.d        	$fp, $sp, 16(0x10)
 3d4:	02c08076 	addi.d      	$fp, $sp, 32(0x20)
 3d8:	00150004 	move        	$a0, $zero
 3dc:	29bfb2c4 	st.w        	$a0, $fp, -20(0xfec)
 3e0:	50000400 	b           	4(0x4)	# 3e4 <before_main+0x1c>
 3e4:	28bfb2c5 	ld.w        	$a1, $fp, -20(0xfec)
 3e8:	038ffc04 	ori         	$a0, $zero, 0x3ff
 3ec:	60007085 	blt         	$a0, $a1, 112(0x70)	# 45c <before_main+0x94>
 3f0:	50000400 	b           	4(0x4)	# 3f4 <before_main+0x2c>
 3f4:	28bfb2c4 	ld.w        	$a0, $fp, -20(0xfec)
 3f8:	00410886 	slli.d      	$a2, $a0, 0x2
 3fc:	1a000004 	pcalau12i   	$a0, 0
 400:	02c00085 	addi.d      	$a1, $a0, 0
 404:	00150004 	move        	$a0, $zero
 408:	381818a4 	stx.w       	$a0, $a1, $a2
 40c:	28bfb2c5 	ld.w        	$a1, $fp, -20(0xfec)
 410:	004108a6 	slli.d      	$a2, $a1, 0x2
 414:	1a000005 	pcalau12i   	$a1, 0
 418:	02c000a5 	addi.d      	$a1, $a1, 0
 41c:	381818a4 	stx.w       	$a0, $a1, $a2
 420:	28bfb2c5 	ld.w        	$a1, $fp, -20(0xfec)
 424:	004108a6 	slli.d      	$a2, $a1, 0x2
 428:	1a000005 	pcalau12i   	$a1, 0
 42c:	02c000a5 	addi.d      	$a1, $a1, 0
 430:	381818a4 	stx.w       	$a0, $a1, $a2
 434:	28bfb2c5 	ld.w        	$a1, $fp, -20(0xfec)
 438:	004108a6 	slli.d      	$a2, $a1, 0x2
 43c:	1a000005 	pcalau12i   	$a1, 0
 440:	02c000a5 	addi.d      	$a1, $a1, 0
 444:	381818a4 	stx.w       	$a0, $a1, $a2
 448:	50000400 	b           	4(0x4)	# 44c <before_main+0x84>
 44c:	28bfb2c4 	ld.w        	$a0, $fp, -20(0xfec)
 450:	02c00484 	addi.d      	$a0, $a0, 1(0x1)
 454:	29bfb2c4 	st.w        	$a0, $fp, -20(0xfec)
 458:	53ff8fff 	b           	-116(0xfffff8c)	# 3e4 <before_main+0x1c>
 45c:	1a000004 	pcalau12i   	$a0, 0
 460:	02c00085 	addi.d      	$a1, $a0, 0
 464:	03800404 	ori         	$a0, $zero, 0x1
 468:	298000a4 	st.w        	$a0, $a1, 0
 46c:	28c04076 	ld.d        	$fp, $sp, 16(0x10)
 470:	28c06061 	ld.d        	$ra, $sp, 24(0x18)
 474:	02c08063 	addi.d      	$sp, $sp, 32(0x20)
 478:	4c000020 	jirl        	$zero, $ra, 0

000000000000047c <after_main>:
 47c:	02ff0063 	addi.d      	$sp, $sp, -64(0xfc0)
 480:	29c0e061 	st.d        	$ra, $sp, 56(0x38)
 484:	29c0c076 	st.d        	$fp, $sp, 48(0x30)
 488:	02c10076 	addi.d      	$fp, $sp, 64(0x40)
 48c:	03800404 	ori         	$a0, $zero, 0x1
 490:	29bfb2c4 	st.w        	$a0, $fp, -20(0xfec)
 494:	50000400 	b           	4(0x4)	# 498 <after_main+0x1c>
 498:	28bfb2c4 	ld.w        	$a0, $fp, -20(0xfec)
 49c:	1a000005 	pcalau12i   	$a1, 0
 4a0:	02c000a5 	addi.d      	$a1, $a1, 0
 4a4:	288000a5 	ld.w        	$a1, $a1, 0
 4a8:	64019c85 	bge         	$a0, $a1, 412(0x19c)	# 644 <after_main+0x1c8>
 4ac:	50000400 	b           	4(0x4)	# 4b0 <after_main+0x34>
 4b0:	1a000004 	pcalau12i   	$a0, 0
 4b4:	28c00084 	ld.d        	$a0, $a0, 0
 4b8:	28c00084 	ld.d        	$a0, $a0, 0
 4bc:	28bfb2c5 	ld.w        	$a1, $fp, -20(0xfec)
 4c0:	004108ab 	slli.d      	$a7, $a1, 0x2
 4c4:	1a000005 	pcalau12i   	$a1, 0
 4c8:	02c000a5 	addi.d      	$a1, $a1, 0
 4cc:	38082ca6 	ldx.w       	$a2, $a1, $a7
 4d0:	1a000005 	pcalau12i   	$a1, 0
 4d4:	02c000a5 	addi.d      	$a1, $a1, 0
 4d8:	38082ca7 	ldx.w       	$a3, $a1, $a7
 4dc:	1a000005 	pcalau12i   	$a1, 0
 4e0:	02c000a5 	addi.d      	$a1, $a1, 0
 4e4:	29ff62c5 	st.d        	$a1, $fp, -40(0xfd8)
 4e8:	38082ca8 	ldx.w       	$a4, $a1, $a7
 4ec:	1a000005 	pcalau12i   	$a1, 0
 4f0:	02c000a5 	addi.d      	$a1, $a1, 0
 4f4:	29ff82c5 	st.d        	$a1, $fp, -32(0xfe0)
 4f8:	38082ca9 	ldx.w       	$a5, $a1, $a7
 4fc:	1a000005 	pcalau12i   	$a1, 0
 500:	02c000a5 	addi.d      	$a1, $a1, 0
 504:	29ff42c5 	st.d        	$a1, $fp, -48(0xfd0)
 508:	38082caa 	ldx.w       	$a6, $a1, $a7
 50c:	1a000005 	pcalau12i   	$a1, 0
 510:	02c000a5 	addi.d      	$a1, $a1, 0
 514:	29ff22c5 	st.d        	$a1, $fp, -56(0xfc8)
 518:	38082cab 	ldx.w       	$a7, $a1, $a7
 51c:	1a000005 	pcalau12i   	$a1, 0
 520:	02c000a5 	addi.d      	$a1, $a1, 0
 524:	54000000 	bl          	0	# 524 <after_main+0xa8>
 528:	28ff22c6 	ld.d        	$a2, $fp, -56(0xfc8)
 52c:	28ff42c9 	ld.d        	$a5, $fp, -48(0xfd0)
 530:	28ff62c8 	ld.d        	$a4, $fp, -40(0xfd8)
 534:	28ff82c5 	ld.d        	$a1, $fp, -32(0xfe0)
 538:	28bfb2c4 	ld.w        	$a0, $fp, -20(0xfec)
 53c:	00410884 	slli.d      	$a0, $a0, 0x2
 540:	380810c7 	ldx.w       	$a3, $a2, $a0
 544:	288000c4 	ld.w        	$a0, $a2, 0
 548:	00109c84 	add.d       	$a0, $a0, $a3
 54c:	298000c4 	st.w        	$a0, $a2, 0
 550:	28bfb2c4 	ld.w        	$a0, $fp, -20(0xfec)
 554:	00410884 	slli.d      	$a0, $a0, 0x2
 558:	38081127 	ldx.w       	$a3, $a5, $a0
 55c:	28800124 	ld.w        	$a0, $a5, 0
 560:	00109c84 	add.d       	$a0, $a0, $a3
 564:	29800124 	st.w        	$a0, $a5, 0
 568:	288000c4 	ld.w        	$a0, $a2, 0
 56c:	148637a7 	lu12i.w     	$a3, 274877(0x431bd)
 570:	03ba0ce7 	ori         	$a3, $a3, 0xe83
 574:	001d9c87 	mul.d       	$a3, $a0, $a3
 578:	0045fcea 	srli.d      	$a6, $a3, 0x3f
 57c:	004980e7 	srai.d      	$a3, $a3, 0x20
 580:	004548e7 	srli.d      	$a3, $a3, 0x12
 584:	0010a8e7 	add.d       	$a3, $a3, $a6
 588:	14001e8a 	lu12i.w     	$a6, 244(0xf4)
 58c:	0389014a 	ori         	$a6, $a6, 0x240
 590:	001da8e7 	mul.d       	$a3, $a3, $a6
 594:	00119c84 	sub.d       	$a0, $a0, $a3
 598:	298000c4 	st.w        	$a0, $a2, 0
 59c:	28bfb2c4 	ld.w        	$a0, $fp, -20(0xfec)
 5a0:	00410884 	slli.d      	$a0, $a0, 0x2
 5a4:	380810a6 	ldx.w       	$a2, $a1, $a0
 5a8:	288000a4 	ld.w        	$a0, $a1, 0
 5ac:	00109884 	add.d       	$a0, $a0, $a2
 5b0:	298000a4 	st.w        	$a0, $a1, 0
 5b4:	28800124 	ld.w        	$a0, $a5, 0
 5b8:	15111106 	lu12i.w     	$a2, -489336(0x88888)
 5bc:	03a224c6 	ori         	$a2, $a2, 0x889
 5c0:	001d9887 	mul.d       	$a3, $a0, $a2
 5c4:	004580e7 	srli.d      	$a3, $a3, 0x20
 5c8:	001090ea 	add.d       	$a6, $a3, $a0
 5cc:	00df7d4a 	bstrpick.d  	$a6, $a6, 0x1f, 0x1f
 5d0:	001010e7 	add.w       	$a3, $a3, $a0
 5d4:	004514e7 	srli.d      	$a3, $a3, 0x5
 5d8:	0010a8ea 	add.d       	$a6, $a3, $a6
 5dc:	0380f007 	ori         	$a3, $zero, 0x3c
 5e0:	001d9d4a 	mul.d       	$a6, $a6, $a3
 5e4:	0011a884 	sub.d       	$a0, $a0, $a6
 5e8:	29800124 	st.w        	$a0, $a5, 0
 5ec:	28bfb2c4 	ld.w        	$a0, $fp, -20(0xfec)
 5f0:	00410884 	slli.d      	$a0, $a0, 0x2
 5f4:	38081109 	ldx.w       	$a5, $a4, $a0
 5f8:	28800104 	ld.w        	$a0, $a4, 0
 5fc:	0010a484 	add.d       	$a0, $a0, $a5
 600:	29800104 	st.w        	$a0, $a4, 0
 604:	288000a4 	ld.w        	$a0, $a1, 0
 608:	001d9886 	mul.d       	$a2, $a0, $a2
 60c:	004580c6 	srli.d      	$a2, $a2, 0x20
 610:	001090c8 	add.d       	$a4, $a2, $a0
 614:	00df7d08 	bstrpick.d  	$a4, $a4, 0x1f, 0x1f
 618:	001010c6 	add.w       	$a2, $a2, $a0
 61c:	004514c6 	srli.d      	$a2, $a2, 0x5
 620:	0010a0c6 	add.d       	$a2, $a2, $a4
 624:	001d9cc6 	mul.d       	$a2, $a2, $a3
 628:	00119884 	sub.d       	$a0, $a0, $a2
 62c:	298000a4 	st.w        	$a0, $a1, 0
 630:	50000400 	b           	4(0x4)	# 634 <after_main+0x1b8>
 634:	28bfb2c4 	ld.w        	$a0, $fp, -20(0xfec)
 638:	02c00484 	addi.d      	$a0, $a0, 1(0x1)
 63c:	29bfb2c4 	st.w        	$a0, $fp, -20(0xfec)
 640:	53fe5bff 	b           	-424(0xffffe58)	# 498 <after_main+0x1c>
 644:	1a000004 	pcalau12i   	$a0, 0
 648:	28c00084 	ld.d        	$a0, $a0, 0
 64c:	28c00084 	ld.d        	$a0, $a0, 0
 650:	1a000005 	pcalau12i   	$a1, 0
 654:	02c000a5 	addi.d      	$a1, $a1, 0
 658:	288000a6 	ld.w        	$a2, $a1, 0
 65c:	1a000005 	pcalau12i   	$a1, 0
 660:	02c000a5 	addi.d      	$a1, $a1, 0
 664:	288000a7 	ld.w        	$a3, $a1, 0
 668:	1a000005 	pcalau12i   	$a1, 0
 66c:	02c000a5 	addi.d      	$a1, $a1, 0
 670:	288000a8 	ld.w        	$a4, $a1, 0
 674:	1a000005 	pcalau12i   	$a1, 0
 678:	02c000a5 	addi.d      	$a1, $a1, 0
 67c:	288000a9 	ld.w        	$a5, $a1, 0
 680:	1a000005 	pcalau12i   	$a1, 0
 684:	02c000a5 	addi.d      	$a1, $a1, 0
 688:	54000000 	bl          	0	# 688 <after_main+0x20c>
 68c:	28c0c076 	ld.d        	$fp, $sp, 48(0x30)
 690:	28c0e061 	ld.d        	$ra, $sp, 56(0x38)
 694:	02c10063 	addi.d      	$sp, $sp, 64(0x40)
 698:	4c000020 	jirl        	$zero, $ra, 0

000000000000069c <_sysy_starttime>:
 69c:	02ff8063 	addi.d      	$sp, $sp, -32(0xfe0)
 6a0:	29c06061 	st.d        	$ra, $sp, 24(0x18)
 6a4:	29c04076 	st.d        	$fp, $sp, 16(0x10)
 6a8:	02c08076 	addi.d      	$fp, $sp, 32(0x20)
 6ac:	29bfb2c4 	st.w        	$a0, $fp, -20(0xfec)
 6b0:	28bfb2c4 	ld.w        	$a0, $fp, -20(0xfec)
 6b4:	1a000005 	pcalau12i   	$a1, 0
 6b8:	02c000a5 	addi.d      	$a1, $a1, 0
 6bc:	288000a5 	ld.w        	$a1, $a1, 0
 6c0:	004108a6 	slli.d      	$a2, $a1, 0x2
 6c4:	1a000005 	pcalau12i   	$a1, 0
 6c8:	02c000a5 	addi.d      	$a1, $a1, 0
 6cc:	381818a4 	stx.w       	$a0, $a1, $a2
 6d0:	1a000004 	pcalau12i   	$a0, 0
 6d4:	02c00084 	addi.d      	$a0, $a0, 0
 6d8:	00150005 	move        	$a1, $zero
 6dc:	54000000 	bl          	0	# 6dc <_sysy_starttime+0x40>
 6e0:	28c04076 	ld.d        	$fp, $sp, 16(0x10)
 6e4:	28c06061 	ld.d        	$ra, $sp, 24(0x18)
 6e8:	02c08063 	addi.d      	$sp, $sp, 32(0x20)
 6ec:	4c000020 	jirl        	$zero, $ra, 0

00000000000006f0 <_sysy_stoptime>:
 6f0:	02ff8063 	addi.d      	$sp, $sp, -32(0xfe0)
 6f4:	29c06061 	st.d        	$ra, $sp, 24(0x18)
 6f8:	29c04076 	st.d        	$fp, $sp, 16(0x10)
 6fc:	02c08076 	addi.d      	$fp, $sp, 32(0x20)
 700:	29bfb2c4 	st.w        	$a0, $fp, -20(0xfec)
 704:	1a000004 	pcalau12i   	$a0, 0
 708:	02c00084 	addi.d      	$a0, $a0, 0
 70c:	29ff82c4 	st.d        	$a0, $fp, -32(0xfe0)
 710:	00150005 	move        	$a1, $zero
 714:	54000000 	bl          	0	# 714 <_sysy_stoptime+0x24>
 718:	28ff82c7 	ld.d        	$a3, $fp, -32(0xfe0)
 71c:	28bfb2c4 	ld.w        	$a0, $fp, -20(0xfec)
 720:	1a000005 	pcalau12i   	$a1, 0
 724:	02c000a5 	addi.d      	$a1, $a1, 0
 728:	288000a6 	ld.w        	$a2, $a1, 0
 72c:	004108c8 	slli.d      	$a4, $a2, 0x2
 730:	1a000006 	pcalau12i   	$a2, 0
 734:	02c000c6 	addi.d      	$a2, $a2, 0
 738:	381820c4 	stx.w       	$a0, $a2, $a4
 73c:	28c000e4 	ld.d        	$a0, $a3, 0
 740:	1a000006 	pcalau12i   	$a2, 0
 744:	02c000c6 	addi.d      	$a2, $a2, 0
 748:	28c000c8 	ld.d        	$a4, $a2, 0
 74c:	0011a084 	sub.d       	$a0, $a0, $a4
 750:	14001e88 	lu12i.w     	$a4, 244(0xf4)
 754:	0389010a 	ori         	$a6, $a4, 0x240
 758:	001da884 	mul.d       	$a0, $a0, $a6
 75c:	28c020e7 	ld.d        	$a3, $a3, 8(0x8)
 760:	00109c84 	add.d       	$a0, $a0, $a3
 764:	28c020c6 	ld.d        	$a2, $a2, 8(0x8)
 768:	00119888 	sub.d       	$a4, $a0, $a2
 76c:	288000a4 	ld.w        	$a0, $a1, 0
 770:	00410887 	slli.d      	$a3, $a0, 0x2
 774:	1a000004 	pcalau12i   	$a0, 0
 778:	02c00086 	addi.d      	$a2, $a0, 0
 77c:	38081cc4 	ldx.w       	$a0, $a2, $a3
 780:	0010a084 	add.d       	$a0, $a0, $a4
 784:	38181cc4 	stx.w       	$a0, $a2, $a3
 788:	288000a4 	ld.w        	$a0, $a1, 0
 78c:	00410888 	slli.d      	$a4, $a0, 0x2
 790:	380820c4 	ldx.w       	$a0, $a2, $a4
 794:	148637a7 	lu12i.w     	$a3, 274877(0x431bd)
 798:	03ba0ce9 	ori         	$a5, $a3, 0xe83
 79c:	001da484 	mul.d       	$a0, $a0, $a5
 7a0:	0045fc87 	srli.d      	$a3, $a0, 0x3f
 7a4:	00498084 	srai.d      	$a0, $a0, 0x20
 7a8:	00454884 	srli.d      	$a0, $a0, 0x12
 7ac:	00109c8b 	add.d       	$a7, $a0, $a3
 7b0:	1a000004 	pcalau12i   	$a0, 0
 7b4:	02c00087 	addi.d      	$a3, $a0, 0
 7b8:	380820e4 	ldx.w       	$a0, $a3, $a4
 7bc:	0010ac84 	add.d       	$a0, $a0, $a7
 7c0:	381820e4 	stx.w       	$a0, $a3, $a4
 7c4:	288000a4 	ld.w        	$a0, $a1, 0
 7c8:	00410888 	slli.d      	$a4, $a0, 0x2
 7cc:	380820c4 	ldx.w       	$a0, $a2, $a4
 7d0:	001da489 	mul.d       	$a5, $a0, $a5
 7d4:	0045fd2b 	srli.d      	$a7, $a5, 0x3f
 7d8:	00498129 	srai.d      	$a5, $a5, 0x20
 7dc:	00454929 	srli.d      	$a5, $a5, 0x12
 7e0:	0010ad29 	add.d       	$a5, $a5, $a7
 7e4:	001da929 	mul.d       	$a5, $a5, $a6
 7e8:	0011a484 	sub.d       	$a0, $a0, $a5
 7ec:	381820c4 	stx.w       	$a0, $a2, $a4
 7f0:	288000a4 	ld.w        	$a0, $a1, 0
 7f4:	00410889 	slli.d      	$a5, $a0, 0x2
 7f8:	380824ea 	ldx.w       	$a6, $a3, $a5
 7fc:	15111104 	lu12i.w     	$a0, -489336(0x88888)
 800:	03a22488 	ori         	$a4, $a0, 0x889
 804:	001da144 	mul.d       	$a0, $a6, $a4
 808:	00458084 	srli.d      	$a0, $a0, 0x20
 80c:	0010a886 	add.d       	$a2, $a0, $a6
 810:	00df7cc6 	bstrpick.d  	$a2, $a2, 0x1f, 0x1f
 814:	00102884 	add.w       	$a0, $a0, $a6
 818:	00451484 	srli.d      	$a0, $a0, 0x5
 81c:	0010988a 	add.d       	$a6, $a0, $a2
 820:	1a000004 	pcalau12i   	$a0, 0
 824:	02c00086 	addi.d      	$a2, $a0, 0
 828:	380824c4 	ldx.w       	$a0, $a2, $a5
 82c:	0010a884 	add.d       	$a0, $a0, $a6
 830:	381824c4 	stx.w       	$a0, $a2, $a5
 834:	288000a4 	ld.w        	$a0, $a1, 0
 838:	0041088a 	slli.d      	$a6, $a0, 0x2
 83c:	380828e4 	ldx.w       	$a0, $a3, $a6
 840:	001da089 	mul.d       	$a5, $a0, $a4
 844:	00458129 	srli.d      	$a5, $a5, 0x20
 848:	0010912b 	add.d       	$a7, $a5, $a0
 84c:	00df7d6b 	bstrpick.d  	$a7, $a7, 0x1f, 0x1f
 850:	00101129 	add.w       	$a5, $a5, $a0
 854:	00451529 	srli.d      	$a5, $a5, 0x5
 858:	0010ad2b 	add.d       	$a7, $a5, $a7
 85c:	0380f009 	ori         	$a5, $zero, 0x3c
 860:	001da56b 	mul.d       	$a7, $a7, $a5
 864:	0011ac84 	sub.d       	$a0, $a0, $a7
 868:	381828e4 	stx.w       	$a0, $a3, $a6
 86c:	288000a4 	ld.w        	$a0, $a1, 0
 870:	0041088a 	slli.d      	$a6, $a0, 0x2
 874:	380828cb 	ldx.w       	$a7, $a2, $a6
 878:	001da164 	mul.d       	$a0, $a7, $a4
 87c:	00458084 	srli.d      	$a0, $a0, 0x20
 880:	0010ac87 	add.d       	$a3, $a0, $a7
 884:	00df7ce7 	bstrpick.d  	$a3, $a3, 0x1f, 0x1f
 888:	00102c84 	add.w       	$a0, $a0, $a7
 88c:	00451484 	srli.d      	$a0, $a0, 0x5
 890:	00109c8b 	add.d       	$a7, $a0, $a3
 894:	1a000004 	pcalau12i   	$a0, 0
 898:	02c00087 	addi.d      	$a3, $a0, 0
 89c:	380828e4 	ldx.w       	$a0, $a3, $a6
 8a0:	0010ac84 	add.d       	$a0, $a0, $a7
 8a4:	381828e4 	stx.w       	$a0, $a3, $a6
 8a8:	288000a4 	ld.w        	$a0, $a1, 0
 8ac:	00410887 	slli.d      	$a3, $a0, 0x2
 8b0:	38081cc4 	ldx.w       	$a0, $a2, $a3
 8b4:	001da088 	mul.d       	$a4, $a0, $a4
 8b8:	00458108 	srli.d      	$a4, $a4, 0x20
 8bc:	0010910a 	add.d       	$a6, $a4, $a0
 8c0:	00df7d4a 	bstrpick.d  	$a6, $a6, 0x1f, 0x1f
 8c4:	00101108 	add.w       	$a4, $a4, $a0
 8c8:	00451508 	srli.d      	$a4, $a4, 0x5
 8cc:	0010a908 	add.d       	$a4, $a4, $a6
 8d0:	001da508 	mul.d       	$a4, $a4, $a5
 8d4:	0011a084 	sub.d       	$a0, $a0, $a4
 8d8:	38181cc4 	stx.w       	$a0, $a2, $a3
 8dc:	288000a4 	ld.w        	$a0, $a1, 0
 8e0:	02c00484 	addi.d      	$a0, $a0, 1(0x1)
 8e4:	298000a4 	st.w        	$a0, $a1, 0
 8e8:	28c04076 	ld.d        	$fp, $sp, 16(0x10)
 8ec:	28c06061 	ld.d        	$ra, $sp, 24(0x18)
 8f0:	02c08063 	addi.d      	$sp, $sp, 32(0x20)
 8f4:	4c000020 	jirl        	$zero, $ra, 0
