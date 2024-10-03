echo
echo "Setup"
echo
branch=$(git symbolic-ref --short HEAD)
branch_name=$(git rev-parse --abbrev-ref HEAD)
last_commit=$(git rev-parse --verify --short=8 HEAD)
export LOCALVERSION="-Armonia-Kernel-${branch_name}/${last_commit}"
mkdir -p out
export ARCH=arm64
export SUBARCH=arm64
make O=out clean
make O=out mrproper

echo
echo "Issue Build Commands"
echo
export CROSS_COMPILE="$HOME"/Android-dev/toolchains/aosp-clang/aarch64-linux-android-4.9/bin/aarch64-linux-android-

echo
echo "Set DEFCONFIG"
echo 
make O=out gts210velte_full_defconfig

echo
echo "Build The Good Stuff"
echo 
make O=out -j$(nproc --all)
#make O=out -j1

rm ./AnyKernel3/*.zip
rm ./AnyKernel3/Image.gz
cp ./out/arch/arm64/boot/Image.gz ./AnyKernel3
cd ./AnyKernel3
zip -r9 Armonia-Kernel-"$version"-"$branch"-"$last_commit".zip * -x .git README.md *placeholder
cd ..