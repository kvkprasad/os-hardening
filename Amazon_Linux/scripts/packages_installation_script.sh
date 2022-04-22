#!/bin/bash

apt-get update
apt-get upgrade
apt-get dist-upgrade
apt-get install rsyslog
systemctl start rsyslog
systemctl enable rsyslog
apt-get install auditd
systemctl start auditd
systemctl enable auditd
service auditd start
apt-get install audispd-plugins
systemctl start audispd-plugins
systemctl enable audispd-plugins
apt-get install aide
systemctl start aide
systemctl enable aide
apt-get install ntp
systemctl start ntp
systemctl enable ntp
apt-get install tcpd
systemctl start tcpd
systemctl enable tcpd
apt-get install clamav-daemon
systemctl start clamav-daemon
systemctl enable clamav-daemon
wget https://github.com/ossec/ossec-hids/archive/2.9.0.tar.gz
tar -xvf 2.9.0.tar.gz
cd ossec-hids-2.9.0/
sudo ./install.sh
touch /var/ossec/etc/shared/agent.conf
/var/ossec/bin/ossec-control start
systemctl enable ossec
apt-get install acct
systemctl enable acct
systemctl start acct
apt-get install cron
systemctl start cron
systemctl enable cron
chown root:root /etc/crontab
chmod og-rwx /etc/crontab
chown root:root /etc/cron.hourly
chmod og-rwx /etc/cron.hourly
chown root:root /etc/cron.daily
chmod og-rwx /etc/cron.daily
chown root:root /etc/cron.weekly
chmod og-rwx /etc/cron.weekly
chown root:root /etc/cron.monthly
chmod og-rwx /etc/cron.monthly
chown root:root /etc/cron.d
chmod og-rwx /etc/cron.d
rm /etc/cron.deny
rm /etc/at.deny
touch /etc/cron.allow
touch /etc/at.allow
chmod og-rwx /etc/cron.allow
chmod og-rwx /etc/at.allow
chown root:root /etc/cron.allow
chown root:root /etc/at.allow
