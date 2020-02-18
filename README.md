# cache-disabler

#### Linux kernel module for disabling cache, that enables cache on its removal.
#### Its purpose is to be used as follows in C
```c
int main() {
    // run with cache on
    cache_enabled_function1();

    //disable cache particularly for cache_disabled_function()
    system("insmod disableCache.ko")
    cache_disabled_function();
    system("rmmod disableCache");

    // run with cache on
    cache_enabled_function2();

    return 0;
}
```

#### To check that `insmod` and `rmmod` work properly, simply do the following
```bash
git clone https://github.com/gobblygobble/cache-disabler.git
cd cache-disabler
make test
```

#### Final goal of cache-disabler is to have it work for both x86 (32-bit) and x86_64 (64-bit) machines.
#### The majority of code and Makefile have been inspired by the following
1. https://www.linuxquestions.org/questions/linux-kernel-70/disabling-cpu-caches-936077/
2. https://stackoverflow.com/questions/48360238/how-can-the-l1-l2-l3-cpu-caches-be-turned-off-on-modern-x86-amd64-chips
3. https://stackoverflow.com/questions/7415515/how-to-access-the-control-registers-cr0-cr2-cr3-from-a-program-getting-segmenta
4. https://stackoverflow.com/questions/21265785/enable-disable-cache-on-intel-64bit-machine-cd-bit-always-set
