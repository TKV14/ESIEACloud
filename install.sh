#!/bin/bash
/usr/bin/yes | sudo apt-get update
/usr/bin/yes | sudo apt-get install apache2 postgresql libfcgi-dev libpq-dev
sudo a2enmod ssl
sudo rm -Rf /var/www/*
sudo cp -R www/ /var/
sudo cp -R conf_apache/* /etc/apache2/
sudo make -C cgi/
sudo cp cgi/prog.fcgi /usr/lib/cgi-bin/
sudo -u postgres psql < initdb
sudo mkdir /ESIEACloud
sudo chmod 777 /ESIEACloud
sudo service apache2 restart
ADRESS=`ifconfig eth0 | grep "inet addr" | sed 's/.*addr:\([0-9]*\.[0-9]*\.[0-9]*\.[0-9]\).*/\1/'`
eval echo "Site web installe a l\'adresse: \$ADRESS"
