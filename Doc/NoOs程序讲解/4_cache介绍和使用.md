# cache介绍和使用

## 执行结果

* 不使用icache的时候
  * 将这句话打开#define CONFIG_SYS_ICACHE_OFF
  * 小灯闪烁速度大概是4秒(一灭一亮)
* 使用icache的时候
  * 将这句话注释: // #define CONFIG_SYS_ICACHE_OFF
  * 小灯闪烁速度大概是2秒(一灭一亮)

## 协处理器

* 协处理器是协助主cpu完成一些特定功能（MMU、Cache和TLB等等）的处理器。ARM支持16个协处理器，但其实在s5pv210中只有一个协处理器cp15，前面的cp0--cp14都没有。在协处理器中又有16个寄存器可以用，每个寄存器由编号来区别从c0--c15。
* 读写协处理器中的寄存器需要特殊的指令mcr和mrc（和读写cpsr寄存器指令mrs和msr区分开）。
  * 操作cp15协处理器示例：(rd是arm寄存器如:r0,r1)
  * mrc是读寄存器指令: mrc p15，0，rd，c1，c0，0
  * mcr是写寄存器指令: mcr p15，0，rd，c1，c0，0

* 常用操作协处理器的指令有mrc和mcr {}中表示可选<>表示必选
  * 把数据从协处理寄存器放到普通Rn寄存器中
    * mrc{cond} <coproc>,<opcode_1>,<Rd>,<CRn>,<CRm> {,opcode_2}
  * 把数据从普通Rn寄存器放到协处理寄存器中
    * mcr{cond} <coproc>,<opcode_1>,<Rd>,<CRn>,<CRm> {,opcode_2}
* 指令解析
  * {cond}是条件，满足条件就执行，没有的话无条件执行。
  * <coproc>表示要处理的协处理器编号
  * <opcode_1> 是协处理寄存器的操作码1
  * <Rd>需要操作的普通寄存器d
  * <CRn>需要操作的协处理寄存器n
  * <CRm>需要操作的附加的协处理寄存器m
  * {,opcode_2}协处理器的操作码2可能需要多个
* CP15协处理器是一个统称。CP15包括了16个32bit的寄存器 c0-c15具体每个寄存器功能要查表。比如c0可能对应两个物理寄存器。操作的时候需要通过opcode_2来区分到底是哪一个。
* 因此对于开启icache和dcache就是简单地设置了一个cp15的cr1对应的标志位。目前只了解cache的开启和关闭就行了。但是使用dcache之前开启了mmu,mmu是有必要了解清楚的。

## icache 和 dcache

* 基于程序访问的局限性,在主存和 CPU 通用寄存器之前设置了一类高速的、容量较小的存储器,把正在执行的指令地址附件的一部分指令或数据从主存调入这类存储器,供 CPU 在一段时间内使用,这对提高程序的运行速度有很大的作用。这类介于主存和 CPU 之间的高速小容量存储器称作高速 cache。
* 比较常见的 cache 包括 icache 和 dcache。
  * icache 的使用比较简单,系统刚上电时,icache中的内容是无效的,并且 icache 的功能是关闭的,往 CP15 协处理器中的寄存器 1 的 bit[12]写1 可以启动 icache,写 0 可以停止 icache。icache 关闭时,CPU 每次取指都要读主存,性能非常低。因为 icache 可随时启动,越早开 icache 越好。
  * 与 icache 相似,系统刚上电时, dcache 中的内容是无效的,并且 dcache 的功能是关闭的,往 CP15 协处理器中的寄存器 1 的 bit[2]写 1 可以启动 dcache,写 0 可以停止 dcache。因为 dcache必须在启动mmu 后才能被启动,而对于裸机而言,没必要开 mmu,所以本教程的程序将不会启动dcache。
