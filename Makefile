# rfm12b-linux: linux kernel driver for the rfm12(b) RF module by HopeRF
# Copyright (C) 2013 Georg Kaindl
# 
# This file is part of rfm12b-linux.
# 
# rfm12b-linux is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
# 
# rfm12b-linux is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with rfm12b-linux.  If not, see <http://www.gnu.org/licenses/>.
#

obj-m := rfm12b.o

SRC       := $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC)

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers .#* *.save *.bak Modules.* modules.order Module.markers *.bin

programs:
	cd examples; make clean; CC=/home/leon/sandbox/sidebranch/happyfeet/build/tmp/sysroots/x86_64-linux/usr/bin/armv5te-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc make && sudo cp bin/rfm12b_* /nfsroot/olinuxino/

driver:
	`find ../temp/run.do_compile* | head -n 1`; sudo cp rfm12b.ko /nfsroot/olinuxino/
