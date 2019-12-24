#!/bin/bash
sudo echo '
  ______    ______   __    __         ______    ______
 /      \  /      \ /  |  /  |       /      \  /      \
/000000  |/000000  |00 |  00 |      /000000  |/000000  |
00 \__00/ 00 | _00/ 00  \/00/       00 |  00 |00 \__00/
00      \ 00 |/    | 00  00<        00 |  00 |00      \
 000000  |00 |0000 |  0000  \       00 |  00 | 000000  |
/  \__00 |00 \__00 | 00 /00  |      00 \__00 |/  \__00 |
00    00/ 00    00/ 00 |  00 |      00    00/ 00    00/
 000000/   000000/  00/   00/        000000/   000000/

Staring booting with secure-kernel...
'
sleep 5
[[ "$1" != '-' ]] && kernel="$1"
shift
if [[ "$1" == '-' ]]; then
	reuse=--reuse-cmdline
	shift
fi
[[ $# == 0 ]] && reuse=--reuse-cmdline
# shellcheck disable=SC1068
kernel = "${kernel:-$(uname -r)}"
kargs="/tmp/sgx_dir/mnt/vmlinuz-$kernel --initrd=/tmp/sgx_dir/mnt/initrd.img-$kernel"

kexec -l -t bzImage $kargs $reuse --append="$*" && systemctl kexec