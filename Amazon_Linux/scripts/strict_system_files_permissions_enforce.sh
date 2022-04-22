#!/bin/bash

sudo chown root:root /boot/grub/grub.cfg
sudo chmod og-rwx /boot/grub/grub.cfg
sudo chown root:root /etc/hosts.allow
sudo chmod 644 /etc/hosts.allow
sudo chown root:root /etc/hosts.deny
sudo chmod 644 /etc/hosts.deny
sudo chmod -R g-wx,o-rwx /var/log/*
sudo usermod -g 0 root
sudo chown root:root /etc/passwd
sudo chmod 644 /etc/passwd
sudo chown root:shadow /etc/shadow
sudo chmod o-rwx,g-wx /etc/shadow
sudo chown root:root /etc/group
sudo chmod 644 /etc/group
sudo chown root:shadow /etc/gshadow
sudo chmod o-rwx,g-rw /etc/gshadow
sudo chown root:root /etc/passwd-
sudo chmod 600 /etc/passwd-
sudo chown root:root /etc/shadow-
sudo chmod 600 /etc/shadow-
sudo chown root:root /etc/group-
sudo chmod 600 /etc/group-
sudo chown root:root /etc/gshadow-
sudo chmod 600 /etc/gshadow-
sudo chown root:root /etc/update-motd.d
sudo chmod 644 /etc/update-motd.d/
sudo chown root:root /etc/issue
sudo chmod 644 /etc/issue
sudo chown root:root /etc/issue.net
sudo chmod 644 /etc/issue.net
sudo chown root:root /etc/aide/aide.conf
sudo chmod 0640 /etc/audit/auditd.conf
sudo chown root:root /etc/audit/auditd.conf
sudo chmod 0640 /etc/audit/audit.rules
sudo chown root:root /etc/audit/audit.rules
sudo chown root:root /etc/bash.bashrc
sudo chmod 0644 /etc/bash.bashrc
sudo chmod 0644 /etc/CIS.conf
sudo chown root:root /etc/CIS.conf
sudo chown root:root /etc/clamav/clamd.conf
sudo chmod 0644 /etc/clamav/clamd.conf
sudo chown clamav:adm /etc/clamav/freshclam.conf
sudo chmod 0444 /etc/clamav/freshclam.conf
sudo chown root:root /var/ossec/etc/ossec-init.conf
sudo chown root:ossec /var/ossec/etc/ossec.conf
sudo chmod 0640 /var/ossec/etc/ossec.conf
sudo chown root:root /etc/rsyslog.conf
sudo chown root:root /etc/ssh/sshd_config
sudo chown root:root /etc/sysctl.conf
sudo chmod -R 755 /etc/update-motd.d/
