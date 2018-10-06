export PATH=/opt/xlinx-qemu/bin:$PATH
qemu-system-aarch64 -M arm-generic-fdt \
-serial mon:stdio -display none \
-device loader,addr=0xfd1a0104,data=0x8000000e,data-len=4 \
-device loader,file=./prebuild/bl31.elf,cpu-num=0 \
-device loader,file=./prebuild/pmufw.elf \
-device loader,file=./u-boot.elf \
-hw-dtb ./prebuild/zcu102-arm.dtb \
-gdb tcp::2333 \
-S