# gpio_sys
## building operations
$ git clone https://github.com/s887432/gpio_sys.git<br>
$ cd gpio_sys<br>
modify cross compiler in CMakeLists.txt<br>
if using ARM9 series, modify in # for Arm9 series<br>
if using SAMA5 or SAMA7 series, modify in # for Cortex series<br>
$ mkdir build<br>
$ cd build<br>
if using ARM9 series<br>
$ cmake .. -DARCH=arm9<br>
if using SAMA5 or SAMA7 series<br>
$ cmake .. -DARCH=cortex<br>
$ make<br><br>
The output will be places at $PROJECT_FOLDER/cortex_bin or $PROJECT_FOLDER/arm9_bin<br>
## command for gpio in SysFs<br>
port number: PB22 = 32&#42;1 + 22 = 54<br>
PA = 32&#42;0<br>
PB = 32&#42;1<br>
PC = 32&#42;2<br>
...<br><br>
// enable gpio pin<br>
&#35;echo <b>PORT_NUMBER</b> > /sys/class/gpio/export<br>
// set for output pin<br>
&#35;echo "out" > /sys/class/gpio/<b>PORT_NAME</b>/direction<br><br>
// set output value<br>
&#35;echo 1 > /sys/class/gpio/<b>PORT_NAME</b>/value<br><br>
// clsen output value<br>
&#35;echo 0 > /sys/class/gpio/<b>PORT_NAME</b>/value<br>
<br>
// disable gpio pin<br>
&#35;echo <b>PORT_NUMBER</b> > /sys/class/gpio/unexport<br>
<br><br>
## Patrick Lin @ Taipei, 2024/08/08

