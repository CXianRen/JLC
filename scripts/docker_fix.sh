#
set -x
username=$(whoami)
if [ "$username" == "user" ]; then
    echo "running in docker will fix the dependencies by creating soft links"
    ln -s /usr/lib/x86_64-linux-gnu/libncurses.so.5.9 $1/libncurses.so
    ln -s /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3 $1/libtinfo.so
    ln -s /usr/lib/x86_64-linux-gnu/libxml2.so.2.9.13 $1/libxml2.so
    ln -s /usr/lib/x86_64-linux-gnu/libz.so.1.2.11 $1/libz.so
    ln -s /usr/lib/x86_64-linux-gnu/libzstd.so.1.4.8 $1/libzstd.so
    exit
fi

