#!/bin/bash
echo "=== $(date) ===" >> /tmp/cron.log
chmod 000 "/home/space_sea/Caged_Gardenia/data/all/txt/深红之土.txt" >> /tmp/cron.log 2>&1
echo "exit: $?" >> /tmp/cron.log