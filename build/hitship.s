
@{{BLOCK(hitship)

@=======================================================================
@
@	hitship, 16x16@8, 
@	+ palette 256 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 512 + 256 = 768
@
@	Time-stamp: 2020-12-30, 23:50:00
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global hitshipTiles		@ 256 unsigned chars
hitshipTiles:
	.word 0x00000000,0x00000000,0x05050500,0x00050505,0x08080800,0x19000808,0x06060B00,0x0A000505
	.word 0x050B0300,0x1F000200,0x00060600,0x1900001E,0x00050800,0x10190019,0x00050200,0x10190000
	.word 0x00000000,0x00000000,0x05050505,0x00050505,0x08080500,0x00080808,0x05050200,0x000B0606
	.word 0x05020019,0x00030B05,0x02001919,0x00060605,0x001F191A,0x00080502,0x00192110,0x00020502
	.word 0x00050200,0x04011315,0x00050800,0x20101919,0x00060600,0x20120C0F,0x0E000300,0x2010100C
	.word 0x00060B00,0x0B201019,0x00080800,0x0B1C1019,0x00050500,0x0B1D1909,0x00000000,0x00000000
	.word 0x0014161B,0x00020500,0x19191018,0x00080017,0x190D1020,0x00060600,0x1910200B,0x00030B00
	.word 0x1911200B,0x000B0600,0x19101C0B,0x00080800,0x0019070B,0x00050505,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global hitshipPal		@ 512 unsigned chars
hitshipPal:
	.hword 0x0000,0x091A,0x5000,0x7773,0x021D,0x3400,0x7680,0x079F
	.hword 0x7C61,0x56FF,0x1D17,0x7FFF,0x013B,0x09FF,0x2579,0x08FC
	.hword 0x023F,0x0F5F,0x025D,0x1D9C,0x111A,0x10FC,0x021E,0x193A
	.hword 0x0B7F,0x0CFC,0x091B,0x023D,0x0F9F,0x023E,0x111B,0x10DD
	.hword 0x0B9F,0x063D,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(hitship)
