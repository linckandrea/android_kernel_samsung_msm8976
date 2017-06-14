echo
echo "Setup"
echo
export LOCALVERSION="-Armonia-Kernel-${branch_name}/${last_commit}"
mkdir -p out
export ARCH=arm64
export SUBARCH=arm64
make O=out clean
make O=out mrproper

echo
echo "Issue Build Commands"
echo
export CROSS_COMPILE="$HOME"/Android-dev/toolchains/aarch64-elf-gcc/bin/aarch64-elf-

echo
echo "Set DEFCONFIG"
echo 
make O=out gts210velte_defconfig

echo
echo "Build The Good Stuff"
echo 
make O=out -j$(nproc --all)
#make O=out -j1