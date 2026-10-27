- `qemu`  is virtualizer its also an emulator

```bash
#how to emulate...
# installing qemu in linux
sudo apt install qemu-system-arm
#toolchain
tar -xf ./arm-gnu-toolchain.tar.xz
#busybox for rfs
tar -xf ./busybox.tar.bz2
#kernel
tar -xf ./linux-xyz.tar.xz

#configuring it
cd linux-xyz 
make ARCH=arm CROSS_COMPILE=../arm-gnu-toolchain/bin/arm-none-linux-gnueabihf -defconfig #default configuration
 
#build it
make ARCH=arm CROSS_COMPILE=../arm-gnu-toolchain/bin/arm-none-linux-gnueabihf -j12

ls arch/arm/boot #zImage

#busybox building
cd ./busybox
make ARCH=arm CROSS_COMPILE=../arm-gnu-toolchain/bin/arm-none-linux-gnueabihf -menuconfig #menu configuration
# static binary enabled
make ARCH=arm CROSS_COMPILE=../arm-gnu-toolchain/bin/arm-none-linux-gnueabihf -j12 install

# create rootfs
mkdir -p rootfs/{bin,sbin,stc,proc,sys,usr/{bin,sbin}}

ls rootfs

#copying everything in our busybox
cp -av busybox/_install/* rootfs/
cd rootfs

#symbolic link to init
ln -sf bin/busybox init
#inside rootfs 
ls #init func in rootfs
# create device cd to dev folder
sudo mknod -m 660 mem c 1 1
sudo mknod -m 660 tty2 c 4 2
sudo mknod -m 660 tty3 c 4 3
sudo mknod -m 660 tty4 c 4 4
#pack rootfs
 find . -print0 |cpio --null -ov --format=newc |gzip -9 > ../rootfs.cpio.gz 

#to know virtual machines supported
qemu-system-arm  -M help

qemu-system-arm  -M virt -m 256M kernel linux-xyz/arch/arm/boot.zImage -initrd rootfs.cpio.gz -append "root=/dev/mem" -nographic

#it boots
uname -a 

```

[custom device](https://blog.davidv.dev/posts/learning-pcie/ 
)

### [KVM internals](./kvm.md)ˀ