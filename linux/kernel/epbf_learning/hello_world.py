#!/usr/bin/python3

from bcc import BPF

program = r"""
int hello_world(void *ctx) {

    char command[64];

    bpf_get_current_comm(&command, sizeof(command));

    bpf_trace_printk("Hello World! Current comand %s\n", command);
    return 0;

}
"""

b = BPF(text=program)
syscall = b.get_syscall_fnname("execve")
b.attach_kprobe(event=syscall, fn_name="hello_world");

b.trace_print()