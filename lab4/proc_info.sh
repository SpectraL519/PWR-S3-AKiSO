# Lab 4 - exercise 1
# This script dislays info about all processes

#!/bin/sh

cd ~
cd /proc

(echo "PID | PPID | COMM | STATE | TTY | RSS | PGID | SID | Open files"

for pid in *; do
    if [ -d $pid ] && [[ $pid =~ ^[0-9] ]]; then
        # Columns in /proc/PID/stat file
        # 1 - pid: Process ID
        # 4 - ppid: Process parent ID
        # 2 - comm: The executable, which started the process
        # 3 - state: Process state
        # 7 - tty_nr = tty: The controling terminal of the process
        # 24 - rss: Resident Set Size = number of pages the process has open
        # 5 - pgrp = pgid: The process group ID
        # 6 - session = sid: The session ID
        n_files=$(sudo ls -l /proc/$pid/fd | wc -l)
        n_files=$(($n_files-1)) # wc counts lines and there's a line with the total value, which is not a file
        awk -v nf="$n_files" '{OFS = " | "}{print $1, $4, $2, $3, $7, $24, $5, $6, nf}' /proc/$pid/stat
    fi
done) | column -t -s " | "