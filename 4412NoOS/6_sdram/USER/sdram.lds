SECTIONS
{
	. = 0x43e00000;
	.text : {
		start.o
		* (.text)
	}

	.bss : {
		* (.bss)
	}
	
	.data : {
		* (.data)
	}
}
