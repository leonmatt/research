#!/usr/bin/python3

from bcc import BPF

from time import sleep

program = r"""
BPF_HASH(counter_table);

int hello_world(void *ctx) {

    u64 uid = bpf_get_current_uid_gid() & 0xFFFFFFFF;
    u64 counter = 0;

    u64 *p = counter_table.lookup(&uid);
    if (p) {
    
        counter = *p;
    
    }

    counter++;

    counter_table.update(&uid, &counter);

    return 0;

}
"""

b = BPF(text=program)
syscall = b.get_syscall_fnname("execve")
b.attach_kprobe(event=syscall, fn_name="hello_world");

while True:
        sleep(2)
        s = ""
        for k,v in b["counter_table"].items():
            s += f"ID {k.value}: {v.value}\n"
        print(s)