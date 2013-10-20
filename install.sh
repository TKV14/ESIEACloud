#!/bin/bash
/usr/bin/yes | sudo apt-get update
/usr/bin/yes | sudo apt-get install apache2 postgresql libfcgi-dev
sudo a2enmod ssl
rm -Rf /var/www/*
cp -R www/ /var/
cp -R conf_apache/* /etc/apache2/
make -C cgi/
cp cgi/prog.fcgi /usr/lib/cgi-bin/
